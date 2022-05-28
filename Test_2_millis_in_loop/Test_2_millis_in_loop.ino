void setup()
{
  Serial.begin(115200);

}


void loop()
{

    static unsigned long timepoint2 = millis();
    if (millis() - timepoint2 > 5000U) //time interval: 2s
    {
      timepoint2 = millis();
      Serial.println("Hello");
      Serial.println(timepoint2);
    }

    
  static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) //time interval: 2s
    {
      timepoint = millis();
      if ((timepoint/1000) % 5 == 0){
        return;
      }
      Serial.println("5");
      Serial.println(timepoint);
    }


   

  }
