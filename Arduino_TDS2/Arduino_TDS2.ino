const int ledPin =  8;      // the number of the LED pin

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated


long interval = 5000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
}

void loop()
{

  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
    Serial.println(millis()/1000);
  }
      
}
