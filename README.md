# Smartplug
## Description
Turn your lights on/off via WiFi! In this project we will make a smartplug using the ESP8266 microcontroller and communicate with it using MQTT.

The project is divided in two parts:
1. Programming the microcontroller (MCU).
2. Designing a PCB for the smartplug.

The current version of the prototype is about 6mm x 8mm, it has a fuse socket, and allows you to control the smartplug either via WiFi or manually (i.e. a normal light switch).

I decided to use MQTT protocol mainly because of its simplicity and because it's very lightweight. 

> Note: MQTT communication requires of a central node, called broker. This tutorial doesn't (yet) implements such node.

If you want to test your MQTT communication, you can download the mosquitto client [here](https://mosquitto.org/download/) (some linux distributions may already have it installed), and publish/subscribe to an example server like ``iot.eclipse.org``.

## External libraries list
To compile the codes, or open the Eagle schematic, you'll need to download the following libraries. You can check [this document](./LIBRARIES_GUIDE.md) for a step-by-step guide on how to download and install them.

1. [ESP8266WiFi arduino library](https://github.com/esp8266/Arduino) by ESP8266 Community: for WiFi setup
2. [PubSubClient arduino library](https://github.com/knolleary/pubsubclient) by Nick O'Leary: for MQTT communication
3. [Adafruit Eagle library](https://github.com/adafruit/Adafruit-Eagle-Library) by Adafruit
4. [esp8266modules](https://github.com/wvanvlaenderen/ESP8266-Eagle_Library) (Eagle library) by Wouter Van Vlaenderen
5. [HLK-PM01](https://github.com/AhmedSaid/EAGLELibraries) (Eagle library) by Ahmed Said

Additionally, I have created my own Eagle library based on the ones presented above. This library (available [here](./PCB/smartplug-components.lbr)) contains all the components used in this project, so you don't have to install the other Eagle libraries. I have also enlarged the pads of every component, for those of you who that can't solder well (including me).

## Material list
* Wemos D1 mini
* HLK-PM01 power supply
* Relay
* LEDs
* Rectifier diode
* Resistors
* AK300 connectors

## Next steps
* Add current sensor.
* Use SMD components and make PCB smaller.
* Add API to improve communication.
* Add local broker using a Raspberry Pi.
* Add 3D model for a box.