# M5Paper Home Assistant Controller

An M5Paper Home Assistant controller to manage your Home Assistant automation using MQTT messages

![M5Paper controller to use with Home Assistant](/m5paper_home_assistant/aux/media/m5paper-featured-image.jpg)


## Hardware & Software need it

* [M5Paper from M5Stack](https://shop.m5stack.com/products/m5paper-esp32-development-kit-v1-1-960x540-4-7-eink-display-235-ppi)
* USB Type-C cable to program the M5Paper
* [Home Assistant](https://www.home-assistant.io/)

### Arduino Setup

1. Download the arduino project present in the folder "m5paper_home_assistant" of this repository. The project must contain the files:
    * m5paper_home_assistant.ino
    * config.h
2. Create a new file called **arduino_secrets.h** inside the projects folders. You must fill the file with your wifi credentials like the following example:

    ``` arduino
    const char* ssid = "the_name_of_your_wifi";
    const char* password = "wifi_password";
    ```

    **Remember to replace the ssid and password variables strings with the name of your wifi network and password.**

3. Inside "m5paper_home_assistant.ino" file make sure to put **the IP address of your home assistant server** and a port like for example the 1883 in the following lines:

    ``` arduino
    const char* mqtt_server = "192.168.1.33"; // Home Assistant IP address
    const int mqtt_port = 1883;
    ```

4. Make sure you have the M5Stack related firmware and libraries installed in your Arduino IDE following [https://docs.m5stack.com/en/arduino/arduino_board](https://docs.m5stack.com/en/arduino/arduino_board) and [https://docs.m5stack.com/en/arduino/m5paper/program](https://docs.m5stack.com/en/arduino/m5paper/program) tutorials.

### Home Assistant Setup

**TODO**

There are multiple ways to connect your controller to Home Assistant and create your customs automations, possibilities are endles, here you can find how it was implemented in the case of this project:

1. Enter your Home Assistant server. Go to Settings -> Devices & services -> Add Integration and install an MQTT integration server like the MQTT Home Assistant official one. Check its [official documentation](https://www.home-assistant.io/integrations/mqtt) in case you need more help.

2. TODO
