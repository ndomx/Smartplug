/*
 * Smartplug controller code for ESP8266.
 * Author: ndomx (https://github.com/ndomx)
 * 
 * This code uses the PubSubClient library and
 * is based on the example code provided the author.
 * Original code available on:
 * https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
 */

#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "private_data.h"
#include "esp8266_header.h"

String clientId = "ESP8266-sp1"; // Be sure to change it for each device

WiFiClient espClient;
PubSubClient client(espClient);

char pub_msg[PUB_MSG_LENGTH];

Ticker rms_calculation;
float amps_array[AMPS_ARRAY_LENGTH];
int amps_index;

float amps_rms;

long last_measurement;
bool is_resting;

void setup()
{
    pinMode(SWOUT, OUTPUT);
    pinMode(SWIN, INPUT);
    pinMode(OC, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
    pinMode(ADC_PIN, INPUT);

    // Ensure the OC flag starts deactivated
    digitalWrite(OC, HIGH);

    Serial.begin(115200);
    setup_wifi();
    setup_mqtt();

    rms_calculation.attach_ms(TICKER_INTERVAL_MS, measure_amps);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    if (is_resting)
    {
        long now = millis();
        if (now - last_measurement > TICKER_REST_MS)
        {
            is_resting = false;
            rms_calculation.attach_ms(TICKER_INTERVAL_MS, measure_amps);
        }
    }
}

void setup_wifi()
{
    delay(10);
    
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    bool led_state = LOW;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        digitalWrite(LED_WIFI, led_state);
        led_state ^= HIGH;
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    digitalWrite(LED_WIFI, LOW);
}

void setup_mqtt()
{
    client.setServer(mqtt_server, 1883);
    client.setCallback(on_message);

    client.subscribe(topic_power);
}

void on_message(char *topic, byte *payload, unsigned int length)
{
    digitalWrite(LED_WIFI, HIGH);

    Serial.print(topic);
    Serial.print(" | ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    
    toggle_plug(payload[0] == '1');

    digitalWrite(LED_WIFI, LOW);
}

void reconnect()
{
    digitalWrite(LED_WIFI, HIGH);
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            client.subscribe(topic_power);
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

void publish(void)
{
    Serial.print("Publish: [");
    Serial.print(topic_amps);
    Serial.print("] amps_rms = ");
    Serial.println(amps_rms);
    
    snprintf(pub_msg, PUB_MSG_LENGTH, "amps_rms: %f", amps_rms);
    client.publish(topic_amps, pub_msg);
}

void measure_amps()
{
    // The current sample has an offset of Vdd/2,
    // so its necessary to substract 1024/2 from the
    // sampled value
    float amps = (analogRead(ADC_PIN) - 512) * MAX_AMPS / 512;

    amps_array[amps_index++] = amps * amps;
    if (amps_index >= AMPS_ARRAY_LENGTH)
    {
        amps_index = 0;
        on_measurement_ready();
    }
}

void on_measurement_ready()
{
    rms_calculation.detach();

    calculate_amps_rms();
    publish();

    last_measurement = millis();
    is_resting = true;
}

void calculate_amps_rms()
{
    float sum;
    for (int idx = 0; idx < AMPS_ARRAY_LENGTH; idx++)
    {
        sum += amps_array[idx];
    }
    
    amps_rms = sum / AMPS_ARRAY_LENGTH;
    /*
     * Technically, amps_rms would be equal to the sqrt of
     * the actual quantity, but its best not to calculate
     * sqrts in the mcu, but to calculate them server side
     */

    if (amps_rms > OVERCURRENT_TH * OVERCURRENT_TH)
    {
        // Theres no software way of clearing the OC flag
        // To turn it off, the MCU must be resetted
        digitalWrite(OC, LOW);
    }
}

void toggle_plug(bool next_state)
{
    bool opmode = digitalRead(OPMODE);
    if (opmode)
    {
        bool swin = digitalRead(SWIN);
        digitalWrite(SWOUT, swin);
    }
    else
    {
        digitalWrite(SWOUT, next_state);
    }
}