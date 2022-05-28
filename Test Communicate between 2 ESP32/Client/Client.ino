#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>


#define ledPin 27


float Celsius = 0;
//float Fahrenheit = 0;

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const char* serverNameTemp = "http://192.168.4.1/temperature";

String temperature;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    temperature = httpGETRequest(serverNameTemp);
    Serial.println("Temperature: " + temperature);
    if (temperature.toFloat() > 31.0) {
      digitalWrite(ledPin, HIGH);
    }
    else {digitalWrite(ledPin, LOW);}
  } 
  else {Serial.println("WiFi Disconnected");}
  
  
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


   
