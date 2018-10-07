#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "private-data.h"

#define RELAY_PIN D5

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
    delay(10);
    
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
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

    bool new_state = (char)payload[0] == '1';
    
    digitalWrite(RELAY_PIN, new_state);
    digitalWrite(LED_BUILTIN, new_state);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        
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
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);

    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(on_message);

    digitalWrite(LED_BUILTIN, LOW);
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