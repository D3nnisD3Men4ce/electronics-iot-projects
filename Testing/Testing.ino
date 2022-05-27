int runMinutes;
int runHours;
int runSeconds;
int secsRemaining;
unsigned long runMillis;
unsigned long allSeconds;

int tdsValue = 900;

bool runPump = false;
bool restPump = false;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    if (!runPump && !restPump) {
      if (tdsValue <= 1000){
        runPump = true;
      }
    }
    else {
        runMillis= millis();
        allSeconds=millis()/1000;
        secsRemaining=allSeconds%3600;
        runMinutes=secsRemaining/60;
        runSeconds=secsRemaining%60;
        
         if (runPump) {
           Serial.print(runSeconds);
           Serial.println(" <= Pumping");

           if (((runSeconds > 0) && (runSeconds % 15) == 0) ) { 
              runPump = false;
              restPump =true;
              Serial.println("Stop Pumping");
           }  
         }

         if (restPump) {
           Serial.print(runSeconds);
           Serial.println(" <= Resting");
           if (((runMinutes > 0) && (runMinutes % 1) == 0) ) { 
              runPump = false;
              restPump =false;
              Serial.println("Rest no more");
           }  
         }         
    }      
}
