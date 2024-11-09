#include <WiFi.h>
#include <PubSubClient.h>
#include <M5EPD.h>
#include <SD.h>
#include <FS.h>

// Configuration file
#include "config.h"
#include "arduino_secrets.h" // You need to create this file by yourself with const char* ssid const char* password

// Task lists
// TODO UPLOAD CODE ONCE IS CREDENTIALS SAFE
// TODO Add Battery Status
// TODO Add block mode
// End of task lists

const char* mqtt_server = "192.168.1.33"; // Home Assistant IP address
const int mqtt_port = 1883;

#define MQTT_WAIT_TIME 1500

WiFiClient espClient;
PubSubClient client(espClient);

// Initialize M5Paper
M5EPD_Canvas canvas(&M5.EPD);

int point[2][2];

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


  // // Buttons coordinates definition matrix // FIXME lot of problems
  // define_buttons_matrix();

  // for (int i=0; i<3; i++){
  //   for (int j=0; i<4; j++){
  //     Serial.println(buttons_matrix_coordinates[i][j]);
  //   }
  // }

  // Background image
  canvas.drawPngFile(SD, "/home-assistant.png",0,0); // the / is CRUTIAL
  canvas.setTextSize(5);
  canvas.drawString("Home Control", 20, 10); // Tittle
  

  // Autobutton text fill
  canvas.setTextSize(4);
  for (int row=0; row<9; row++){
    for (int col=0; col<3; col++){
      canvas.drawString(buttons_names[row][col], 1+col*button_width+((button_width-(buttons_names[row][col].length()*24))/2), row*95+95); // 6 letter at size 4 are the max
    }
  }


  // // Button lights
  // // canvas.drawRect(100, 100, 350, 150, 0xFFFF);
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[0][0], 25, 95);
  
  // // Button camera
  // // canvas.drawRect(100, 350, 350, 150, 0xFFFF);
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[0][1], 1+1*button_width+((button_width-(buttons_names[0][1].length()*24))/2), 1*95); // 6 letter at size 4 are the max, with 20 as margin is side, 180-20
  
  // // Button TV
  // // canvas.drawRect(100, 600, 350, 150, 0xFFFF);
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[0][2], 400, 95);

  // // Button Ambilight TV
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[1][0], 45, 190);

  // // Button TV Play
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[1][2], 400, 190);

  // // Button TV Pause
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[2][2], 390, 285);

  // // Button Light Kitchen
  // canvas.setTextSize(4);
  // canvas.drawString(buttons_names[8][0], 10, 95*9);

  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Set up MQTT
  client.setServer(mqtt_server, mqtt_port);
  reconnect();

  // Publish a message to Home Assistant
  publishMessage("Hello from M5Paper!");
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

  if (M5.BtnL.wasPressed()){
      // Publish a message to Home Assistant
      publishMessage("ON");
  }
  if (M5.BtnP.wasPressed()){
      // Publish a message to Home Assistant
      publishMessage("ON-CAMERA");
  }
  if (M5.BtnR.wasPressed()){
      // Publish a message to Home Assistant
      publishMessage("TOGGLE-TV");
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
                    canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100,
                                    100, 15);
                    Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n",
                                  FingerItem.id, FingerItem.x, FingerItem.y,
                                  FingerItem.size);
                    
                    for (int j = 0; j <= 26; j++) {
                      // Serial.println(j); // Debug
                      if ((point[i][0] >buttons_matrix_coordinates[j][0] && point[i][0] <buttons_matrix_coordinates[j][1]) && (point[i][1] >buttons_matrix_coordinates[j][2] && point[i][1] <buttons_matrix_coordinates[j][3])){ // Button lights
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
    // end test
  M5.BtnL.lastChange();
  M5.update();
  delay(100);
  }

