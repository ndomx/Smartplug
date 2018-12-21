/*
 * Smartplug controller code for ESP8266.
 * Author: ndomx (https://github.com/ndomx)
 * 
 * This code uses the PubSubClient library and
 * is based on the example code provided the author.
 * Original code available on:
 * https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "private-data.h"
#include "smartplug-functions.h"

#define RELAY_PIN D1
#define LED_RED D7 // For MQTT debugging
#define LED_BLUE D8 // For WiFi debugging

String clientId = "ESP8266-sp1"; // Be sure to change it for each device

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    pinMode(RELAY_PIN, OUTPUT);

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(on_message);

    digitalWrite(RELAY_PIN, LOW);

    client.subscribe(topic);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

void setup_wifi()
{
    delay(10);
    
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    bool blue_state = LOW;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        digitalWrite(LED_BLUE, blue_state);
        blue_state ^= HIGH;
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    digitalWrite(LED_BLUE, HIGH);
}

void on_message(char *topic, byte *payload, unsigned int length)
{
    Serial.print(topic);
    Serial.print(" | ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    
    digitalWrite(RELAY_PIN, payload[0] == '1');
}

void reconnect()
{
    digitalWrite(LED_RED, HIGH);
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            client.subscribe(topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
    digitalWrite(LED_RED, LOW);
}