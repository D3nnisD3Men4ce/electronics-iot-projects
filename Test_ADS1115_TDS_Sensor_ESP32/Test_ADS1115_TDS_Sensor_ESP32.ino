#include <Arduino.h>
#include <OneWire.h>
#include "DFRobot_ESP_PH_WITH_ADC.h"
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "EEPROM.h"

#define TemperatureSensorPin 27

#define VREF 5.0     // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point


OneWire oneWire(TemperatureSensorPin);
DallasTemperature sensors(&oneWire);
Adafruit_ADS1115 ads;
LiquidCrystal_I2C lcd(0x27, 16, 2);


int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
float Celsius = 0;
//float Fahrenheit = 0;
int16_t adc0;
float voltage, phValue;


void setup()
{
    
    Serial.begin(115200);
    EEPROM.begin(32);
//    ph.begin();
    ads.setGain(GAIN_ONE);
    ads.begin();
    lcd.begin();
}

float getTemp()
{
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
//  Fahrenheit = sensors.toFahrenheit(Celsius);

  return Celsius;
//  return Fahrenheit
}


void displayInfo(float ec, float temp){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("EC: ");
      if (ec < 0) {
        lcd.setCursor(0,0);
        lcd.print("EC: ");
        lcd.print("0");
        lcd.setCursor(0,1); // Go to second line
        lcd.print("Temp: ");
        lcd.print(temp);
      } else {
        lcd.setCursor(0,0);
        lcd.print("EC: ");
        lcd.print(ec);
        lcd.setCursor(0,1); // Go to second line
        lcd.print("Temp: ");
        lcd.print(temp);
      }
}



void loop()
{
//      Serial.println(" µS/cm");
  static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) //time interval: 1s
    {
      timepoint = millis();
      /** * index 0 for adc's pin A0 * index 1 for adc's pin A1 * index 2 for adc's pin A2 * index 3 for adc's pin A3 */
      voltage = ads.readADC_SingleEnded(0) / 10; // read the voltage
      Serial.print("EC: ");
      float ec = voltage - 100;
      if (ec < 0) {
        Serial.println("0");
      } else {
        Serial.println(ec, 4);
      }
      
  
      float temperature = getTemp(); // read your temperature sensor to execute temperature compensation
      Serial.print("Temp: ");
      Serial.print(temperature, 1);
      Serial.println("C");

      displayInfo(ec, temperature);
      
  
//      phValue = ph.readPH(voltage, temperature); // convert voltage to pH with temperature compensation
//      Serial.print("pH:");
//      Serial.println(phValue, 4);
    }
//    ph.calibration(voltage, temperature); // calibration process by Serail CMD

  }
