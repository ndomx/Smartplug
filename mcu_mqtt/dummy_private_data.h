/*
 * Header file that contains all private data of the communication
 * including WiFi SSID & password, and MQQT Broker address and
 * device topics.
 * 
 * REMEMBER TO RENAME THIS FILE TO private_data.h
 */

#ifndef PRIVATE_DATA_H
#define PRIVATE_DATA_H

const char *ssid = "WIFI SSID";
const char *password = "WIFI PASSWORD";

const char *mqtt_server = "MQTT BROKER ADDRESS";
const char *topic_power = "MQTT TOPIC FOR TURN ON/OFF";
const char *topic_amps = "MQTT TOPIC FOR AMPS";

/*
 * Each device should have its own topic, i.e.:
 * home/light1/power
 * home/light1/amps
 * kitchen/microwave_power
 * ...
 * 
 * Unless you wish to control more than one plug at
 * the same time, i.e.: home/all-lights
 */
#endif // PRIVATE_DATA_H
