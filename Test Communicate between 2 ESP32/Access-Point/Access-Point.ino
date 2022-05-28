#include <OneWire.h>
#include <DallasTemperature.h>


#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h> 
#include <Adafruit_Sensor.h>

#define TemperatureSensorPin 27
//#define TemperatureSensorPin D5

OneWire oneWire(TemperatureSensorPin);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
//float Fahrenheit = 0;

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";


AsyncWebServer server(80);

String getTemp() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  return String(Celsius);

}


void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.println("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getTemp().c_str());
  });

  sensors.begin();
  server.begin();
  
}

void loop()
{
  Serial.println(getTemp());
  delay(1000);
}


   
