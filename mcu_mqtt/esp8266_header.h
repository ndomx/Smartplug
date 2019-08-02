/*
 * Header file for functions:
 * This file is read before the main code by the compiler, and so,
 * it allow us to make use of this functions before declaring them
 * in the main code.
 * 
 * The use of this kind of files is absolutely optional for small
 * codes/projects like this one, but I find it a good practice to
 * use them anyway.
 */

#ifndef ESP8266_HEADER_H
#define ESP8266_HEADER_H

#include <Arduino.h>

#define RELAY_PIN D1
#define LED_RED D7 // For MQTT debugging
#define LED_BLUE D8 // For WiFi debugging
#define ADC_PIN A0

#define PUB_MSG_LENGTH 20

#define AMPS_ARRAY_LENGTH 40
#define TICKER_INTERVAL_MS 2

#define TICKER_REST_MS 1000

#define MIN_AMPS 0.01 // Threshold for off state
#define MAX_AMPS 5.0 // Max current supported by sensor

#define is_connected(x) x > MIN_AMPS

void setup_wifi(void);

void setup_mqtt(void);
void on_message(char *topic, byte *payload, unsigned int length);
void reconnect(void);
void publish(void);

void measure_amps(void);
void calculate_amps_rms(void);
void on_measurement_ready(void);

void toggle_plug(bool next_state);

#endif // ESP8266_HEADER_H
