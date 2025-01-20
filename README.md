# M5Paper Home Assistant Controller

An M5Paper Home Assistant controller to manage your Home Assistant automation using MQTT messages

![M5Paper controller to use with Home Assistant](/m5paper_home_assistant/aux/media/m5paper-featured-image.jpg)


## Hardware & Software need it

* [M5Paper from M5Stack](https://shop.m5stack.com/products/m5paper-esp32-development-kit-v1-1-960x540-4-7-eink-display-235-ppi)
* USB Type-C cable to program the M5Paper
* [Home Assistant](https://www.home-assistant.io/)

### Arduino Setup

1. Download the Arduino project present in the folder "m5paper_home_assistant" of this repository. The project must contain the files:
    * m5paper_home_assistant.ino
    * config.h
2. Create a new file called **arduino_secrets.h** inside the projects folders. You must fill the file with your Wi-Fi credentials like the following example:

    ``` arduino
    const char* ssid = "the_name_of_your_wifi";
    const char* password = "wifi_password";
    ```

    **Remember to replace the _ssid_ and _password_ variables strings with the name of your Wi-Fi network and password.**

3. Inside **m5paper_home_assistant.ino** file make sure to put **the IP address of your home assistant server** and a port like for example the **1883** in the following lines:

    ``` arduino
    const char* mqtt_server = "192.168.1.33"; // Home Assistant IP address
    const int mqtt_port = 1883;
    ```

4. Make sure you have the M5Stack related firmware and libraries installed in your Arduino IDE following [https://docs.m5stack.com/en/arduino/arduino_board](https://docs.m5stack.com/en/arduino/arduino_board) and [https://docs.m5stack.com/en/arduino/m5paper/program](https://docs.m5stack.com/en/arduino/m5paper/program) tutorials.

### Home Assistant Setup

There are multiple ways to connect your controller to Home Assistant and create your customs automations, possibilities are endless! Here you can find how it was implemented in the case of this project:

1. Enter your Home Assistant server. Go to Settings -> Devices & services -> Add Integration and install an MQTT integration server like the MQTT Home Assistant official one. Check its [official documentation](https://www.home-assistant.io/integrations/mqtt) in case you need more help.

2. Click on "Create Automation" and choose the "Create new automation" option.

3. Click on "Add Trigger" and look for the MQTT trigger

    ![MQTT Trigger inside Home Assistant](/m5paper_home_assistant/aux/media/ha-mqtt-automation.png)

4. As topic add **home/m5paper/status** . Every time a new message is sent from the M5Paper controller to that topic the Home Assistant Integration will trigger.

5. From here different automations can be done. I recommend the action "choose between" with the value template as it can be seen in the following image:

    ![Topic and Choose between options action](/m5paper_home_assistant/aux/media/ha-mqtt-automation-2.png)

    **Each button send and unique MQTT message in the format: **BUTTON_X** where **X** is the number of the button, starting from **0**.**

**To save time you can use the [m5paper-controller.yaml](/m5paper_home_assistant/aux/home_assistant_template/m5paper-controller.yaml) template inside this repository.**

## Using the M5Paper controller

Once everything is ready you can customize your M5Paper Controller to fit your needs.

Inside the Arduino IDE, open the file of the project **config.h**, there you will find the function:

``` arduino
const String buttons_names[9][3] = { // Max 6 CAP letters with a font size of 4
  {"LIGHTS", "CAMERA", "TELE"}, // 0 1 2
  {"AMBI", "MOV", "PLAY"}, // 3 4 5
  {"HALL", "PORTAL", "PAUSE"}, // 6 7 8
  {"SALON", "TEMP", "MUTE"}, // 9 10 11
  {"LAMP", "THERM", "TIKTOK"}, // 12 13 14
  {"XBOX", "SPOTIFY", "DISNEY"}, // 15 16 17
  {"SWITCH", "LIVE TV", "YOUTUBE"}, // 18 19 20
  {"NEWS", "MAX", "PRIME"}, // 21 22 23
  {"KITCHEN", "DEBUG", "NETFLIX"} // 24 25 26
};
```

You can change the name of each button to fix your needs. From left to right, top to bottom the buttons index, which will be need to get the proper values inside home assistant, start by 0 and ends in 26.

### Central button and Block Mode

Press the central button of the M5Paper controller to block the controller to avoid accidental touches. Press it again to unblock it.

### Up and Down buttons

Up and down buttons sends the MQTTT message _UP_ and _DOWN_ respectively. You can use those buttons to whatever you want, like controlling the TV volume.