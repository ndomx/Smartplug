# LIBRARIES GUIDE

## 1. ESP8266 Arduino library
1. Open the Arduino IDE
2. Go to _File_ > _Preferences_ and complete the field _Additional Boards Manager URLs_ with the following link ``http://arduino.esp8266.com/stable/package_esp8266com_index.json``
3. Go to _Tools_ > _Board_ > _Boards Manager..._
4. Search for ``esp8266`` and install the library **esp8266** by **ESP8266 Community**.
   
## 2. PubSubClient Arduino library
1. Open the Arduino IDE.
2. Go to _Sketch_ > _Include Library_ > _Manage Libraries..._
3. Search for ``PubSubClient`` and install the library **PubSubClient** by **Nick O'Leary**

## 3. Adafruit Eagle library
Please follow the installation guide provided by the authors [here](https://github.com/adafruit/Adafruit-Eagle-Library). You'll need a external libraries directory for the other libraries.

## 4. esp8266_with_adapter Eagle library
Download the library from [here](https://github.com/wvanvlaenderen/ESP8266-Eagle_Library) and save it in the external libraries directory created in the previous section.

## 5. HLK-PM01 Eagle library
Download the library from [here](https://github.com/AhmedSaid/EAGLELibraries) and save it in the external libraries directory created in section 3.

## 6. smartplug-components Eagle library
My customized library (based on the 3 libraries above) is available in this repo at [/PCB/smartplug-components.lbr](/PCB/smartplug-components.lbr). To use it, just save the file in the external libraries directory created in section 3.