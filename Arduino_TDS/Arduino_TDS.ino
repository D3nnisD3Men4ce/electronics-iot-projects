#include <OneWire.h>
#include <DallasTemperature.h>

#define TdsSensorPin A1

#define TemperatureSensorPin 7

#define MasterBlendRelayPin 8

#define VREF 5.0     // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point

OneWire oneWire(TemperatureSensorPin);
DallasTemperature sensors(&oneWire);

int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
float Celsius = 0;
//float Fahrenheit = 0;
const unsigned long MasterBlendPumpInterval = 10000;
unsigned long MasterBlendTimer;

//int runMinutes;
//int runHours;
//int runSeconds;
//int secsRemaining;
//unsigned long runMillis;
//unsigned long allSeconds;
//
//bool isPumping = true;
//bool isTimeCheckBusy = false;
//bool isDataLogBusy = false;


void setup()
{
    sensors.begin();
    Serial.begin(9600);
    pinMode(TdsSensorPin,INPUT);
    pinMode(MasterBlendRelayPin, OUTPUT);
    MasterBlendTimer = millis();
}

void loop()
{

//    runMillis= millis();
//    allSeconds=millis()/1000;
//    secsRemaining=allSeconds%3600;
//    runMinutes=secsRemaining/60;
//    runSeconds=secsRemaining%60;
//    runHours= allSeconds/3600;
//
//    // less than 1000 pump
//    // no pump within 1000-1200
//    // no pump more than 1200
//    
//    if (tdsValue <= 1000){
//      if (((runSeconds % 15) == 0) && !isPumping) {
//          isPumping = true;
//          
//          isPumping = false;
//      } 
//  
//      if (((runSeconds % 5) == 0 && !isTimeCheckBusy)) {
//          isTimeCheckBusy = true;
//   
//          isTimeCheckBusy = false;
//      }
//  
//      if (((runSeconds % 10) == 0) && !isDataLogBusy) {
//          isDataLogBusy = true;
//      
//          isDataLogBusy = false;
//      }
//    }
      

    
  
   static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   


   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
//      float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationCoefficient=1.0+0.02*(temperature-getTemp());    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      
      Serial.print("EC Value: ");
      Serial.print(tdsValue*2,0);
      Serial.println(" µS/cm");

      Serial.print("Water Temperature: ");
      Serial.print(getTemp());
      Serial.println("C");
   }


    unsigned long pumpStart = millis();
    if ((millis () - pumpStart) >= MasterBlendPumpInterval){
      nutrientPump(tdsValue*2);
  }
}
int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}



float getTemp()
{
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
//  Fahrenheit = sensors.toFahrenheit(Celsius);

  return Celsius;
//  return Fahrenheit
}


void nutrientPump(float tdsValue){
  if (tdsValue >= 1000 && tdsValue >= 1200){
    digitalWrite(MasterBlendRelayPin, LOW);
  }
  else{
    digitalWrite(MasterBlendRelayPin, HIGH);
  }
  MasterBlendTimer = millis ();
}
