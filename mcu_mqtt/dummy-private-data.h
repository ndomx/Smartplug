/*
 * Header file that contains all private data of the communication
 * including WiFi SSID & password, and MQQT Broker address and
 * device topic.
 * REMEMBER TO RENAME THIS FILE TO privte-data.h
 */
const char *ssid = "WIFI SSID";
const char *password = "WIFI PASSWORD";

const char *mqtt_server = "MQTT BROKER ADDRESS";
const char *topic = "MQTT TOPIC";
/*
 * Each device should have its own topic, i.e.:
 * home/light1
 * kitchen/microwave
 * 
 * Unless you wish to control more than one plug at
 * the same time, i.e.: home/all-lights
 */