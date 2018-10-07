#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "private-data.h"

#define RELAY_PIN D1
#define LED_RED D6
#define LED_GREEN D7
#define LED_BLUE D8

String clientId = "ESP8266-light1"; // Be sure to change it for each device

WiFiClient espClient;
PubSubClient client(espClient);

bool blue_state = LOW;

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

        digitalWrite(LED_BLUE, blue_state);
        blue_state ^= HIGH;
    }

    blue_state = LOW;
    digitalWrite(LED_BLUE, LOW);

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
    
    digitalWrite(RELAY_PIN, payload[0] == '1');

    blink_led();
}

void reconnect()
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
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

        blue_state ^= HIGH;
        digitalWrite(LED_BLUE, blue_state);
    }
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
}

void blink_led()
{
    digitalWrite(LED_BLUE, LOW);
    delay(300);
    digitalWrite(LED_BLUE, HIGH);
    delay(300);
    digitalWrite(LED_BLUE, LOW);
    delay(300);
    digitalWrite(LED_BLUE, HIGH);
}

void setup()
{
    pinMode(RELAY_PIN, OUTPUT);

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