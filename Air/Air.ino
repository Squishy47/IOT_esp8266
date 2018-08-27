#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <DHT.h>
#include <WiFiUdp.h>
#include <EasyNTPClient.h>
#include <ESP8266WiFi.h>      
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define DEBUG true
#define DHTPIN 2
#define DHTTYPE DHT11
#define updateServerURL "http://URL_OF_SERVER:PORT"
#define AIO_SERVER      "IP OF MQTT BROKER"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

// ------------------------------ Objects ------------------------------
WiFiClient client;
WiFiManager wifiManager;
WiFiUDP udp;
EasyNTPClient ntpClient(udp, "0.uk.pool.ntp.org", 0);
DHT dht(DHTPIN, DHTTYPE);
DynamicJsonBuffer jsonBuffer;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT);
Adafruit_MQTT_Publish temperaturePub = Adafruit_MQTT_Publish(&mqtt, "temp");
Adafruit_MQTT_Subscribe temperatureSub = Adafruit_MQTT_Subscribe(&mqtt, "temp");

// ------------------------------ Variables ------------------------------
int now;
int heartbeatTimestamp      = 0;
int HeartbeatInterval       = 10000;
String deviceID             = String(ESP.getChipId());
float tempStorage = 0.f;
float humStorage = 0.f;

// ------------------------------ Functions ------------------------------
void setup() {
    Serial.begin(115200);
    Serial.println("BOOTING...");
    Serial.println();
    dht.begin();
    setupWifi();
    otaHandler();
}

void loop() {
    ArduinoOTA.handle();
    MQTT_connect();
    
    now = millis();
    if(now - heartbeatTimestamp > HeartbeatInterval) {
        heartbeatTimestamp = now;
        transmitJsonData(getSensorData());
    }           
}
