#include "DFRobot_ESP_PH.h"
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>


Adafruit_ADS1115 ads;
DFRobot_ESP_PH ph;
#define ESPADC 4096.0   //the esp Analog Digital Convertion value
#define ESPVOLTAGE 3.3 //the esp voltage supply value
float voltage, phValue, temperature = 25;
int16_t adc0;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);//needed to permit storage of calibration value in eeprom
  ads.setGain(GAIN_ONE);
  ads.begin();
  ph.begin();
}

void loop()
{
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 1000U) //time interval: 1s
  {
    timepoint = millis();
    //voltage = rawPinValue / esp32ADC * esp32Vin
    voltage = ads.readADC_SingleEnded(0)/10; 
    Serial.print("voltage:");
    Serial.println(voltage, 4);
    
    //temperature = readTemperature();  // read your temperature sensor to execute temperature compensation
    Serial.print("temperature:");
    Serial.print(temperature, 1);
    Serial.println("^C");

    phValue = ph.readPH(voltage, temperature); // convert voltage to pH with temperature compensation
    Serial.print("pH:");
    Serial.println(phValue, 4);
  }
  ph.calibration(voltage, temperature); // calibration process by Serail CMD
}
