#include <WiFi.h>
#include <PubSubClient.h>
#include <M5EPD.h>

// Configuration file
#include "config.h"
#include "arduino_secrets.h" // You need to create this file by yourself with const char* ssid const char* password

// Task lists
// TODO Add Battery Status
// TODO Add lock mode
// End of task lists

const char* mqtt_server = "192.168.1.33"; // Home Assistant IP address
const int mqtt_port = 1883;

#define MQTT_WAIT_TIME 1500

WiFiClient espClient;
PubSubClient client(espClient);

// Initialize M5Paper
M5EPD_Canvas canvas(&M5.EPD);

int point[2][2]; // Touch point matrix

bool block_mode = false;

void setup() {

  Serial.begin(115200);

  // Initialize M5Paper
  M5.begin();
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  M5.RTC.begin();

  if (!SD.begin()) {
    Serial.println("SD Card initialization failed!");
    return;
  }

  canvas.createCanvas(540, 960);

  // Background image
  canvas.drawPngFile(SD, "/v2_home-assistant.png",0,0); // the / is CRUTIAL
  canvas.setTextSize(5);
  canvas.drawString("Home Control", 20, 10); // Tittle
  
  // Button text autofill. Go to config.h to change the button names inside "button_names"
  canvas.setTextSize(4);
  for (int row=0; row<9; row++){
    for (int col=0; col<3; col++){
      canvas.drawString(buttons_names[row][col], 1+col*button_width+((button_width-(buttons_names[row][col].length()*24))/2), row*95+95); // 6 letter at size 4 are the max
    }
  }

  // canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16); // Use this mode only for a high quality brachground

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Set up MQTT
  client.setServer(mqtt_server, mqtt_port);
  reconnect();

  // Publish a message to Home Assistant
  publishMessage("M5Paper available");
}


void draw_menu(){
  
  if (block_mode == false){

    canvas.setTextSize(5);
    canvas.createCanvas(170, 85);
    canvas.drawString("<-UNBLOCKING", 170, 485); // Block
    canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);

    // Background image
    canvas.drawPngFile(SD, "/v2_home-assistant.png",0,0); // the / is CRUTIAL
    canvas.setTextSize(5);
    canvas.drawString("Home Control", 20, 10); // Tittle
    // Button text autofill. Go to config.h to change the button names inside "button_names"
    canvas.setTextSize(4);
    for (int row=0; row<9; row++){
      for (int col=0; col<3; col++){
        canvas.drawString(buttons_names[row][col], 1+col*button_width+((button_width-(buttons_names[row][col].length()*24))/2), row*95+95); // 6 letter at size 4 are the max // FIXME, SO SLOW TO DRAW?
      }
    }
    canvas.pushCanvas(0, 0, UPDATE_MODE_GC16); // // UPDATE_MODE_DU // UPDATE_MODE_GC16 - Use this mode only for a high quality brachground // UPDATE_MODE_GL16
  }
  else{
    canvas.setTextSize(5);
    canvas.createCanvas(170, 85);
    canvas.drawString("BLOCKED->", 250, 485); // Block
    // canvas.UpdateArea(buttons_matrix_coordinates[14][0], buttons_matrix_coordinates[14][2], buttons_matrix_coordinates[14][1], buttons_matrix_coordinates[14][3], UPDATE_MODE_DU4)
    canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);
    // canvas.pushCanvas(buttons_matrix_coordinates[14][0], buttons_matrix_coordinates[14][2],UPDATE_MODE_GC16);
    // canvas.pushCanvas()
  }
}

void reconnect() {
  // Reconnect to MQTT broker
  while (!client.connected()) {
    if (client.connect("M5PaperClient")) {
      // Successfully connected
    } else {
      delay(5000);
    }
  }
}

void publishMessage(String message) {
  if (client.connected()) {
    client.publish("home/m5paper/status", message.c_str());
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Physical buttons control
  if (M5.BtnL.wasPressed()){
      publishMessage("UP");
  }
  if (M5.BtnP.wasPressed()){ // Block Mode
      // publishMessage("CENTER");
      if (block_mode == false){
        block_mode = true;
        draw_menu();
      }
      else{
        block_mode = false;
        draw_menu();
      }

  }
  if (M5.BtnR.wasPressed()){
      publishMessage("DOWN");
  }

  // General control
    if (M5.TP.available()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            canvas.fillCanvas(0);
            bool is_update = false;
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                if ((point[i][0] != FingerItem.x) ||
                    (point[i][1] != FingerItem.y)) {
                    is_update   = true;
                    point[i][0] = FingerItem.x;
                    point[i][1] = FingerItem.y;
                    // canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100, 100, 15);
                    Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n",
                                  FingerItem.id, FingerItem.x, FingerItem.y,
                                  FingerItem.size);
                    
                    for (int j = 0; j <= 26; j++) {
                      // Serial.println(j); // Debug
                      if (block_mode == false && (point[i][0] >buttons_matrix_coordinates[j][0] && point[i][0] <buttons_matrix_coordinates[j][1]) && (point[i][1] >buttons_matrix_coordinates[j][2] && point[i][1] <buttons_matrix_coordinates[j][3])){ // Button lights
                        String message = "BUTTON_";
                        message.concat(j);
                        publishMessage(message);
                        Serial.println(j); // Debug
                        delay(MQTT_WAIT_TIME);
                      }
                    }

                }
            }
            if (is_update) {
                // canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
                delay(100);
            }
        }
    }

  M5.BtnL.lastChange();
  M5.BtnP.lastChange();
  M5.BtnR.lastChange();
  M5.update();
  delay(100);
  }

