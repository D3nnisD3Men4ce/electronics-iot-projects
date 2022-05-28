#include <SimpleTimer.h>
#define relay_NutrientSolutionPin     8
#define relay_pHBufferPin             7

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

bool NutrientPump = false;
bool pHpump = false;

// the timer object
SimpleTimer timer;

// a function to be executed periodically
void repeatMe() {
    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
}

void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
    pinMode(relay_NutrientSolutionPin, OUTPUT);
    pinMode(relay_pHBufferPin, OUTPUT);
    Serial.begin(115200);
    timer.setInterval(1000, repeatMe);
}

void loop() {
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;
      // Prints the distance on the Serial Monitor


      
    timer.run();

    if (distance < 30){
      
    }
}
