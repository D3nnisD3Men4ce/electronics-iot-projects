#define trigPin 9
#define echoPin 10
#define mist 13

long duration;
int distance;
float marker;


void setup()
{
  pinMode(mist,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 100U) //time interval: 0.1s
  {
    timepoint = millis();
    Serial.println(distance);
  }

  
  if (distance < 200) // change value sa 200 to a measurement LESS THAN sa sukod sa entrance sa inyong tent
      {
        digitalWrite(mist,HIGH);
        delay(3000); // 3000 is in milliseconds, so 3 seconds. delay(3000); means nakaremain nga on ang mist for 3 seconds. Pwede ninyo ni machange
        digitalWrite(mist, LOW);
      }

}
