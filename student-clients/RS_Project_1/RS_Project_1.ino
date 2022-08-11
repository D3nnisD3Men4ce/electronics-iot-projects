#include <LiquidCrystal_I2C.h>

//#define trigPin 19
//#define echoPin 18

#define trigPin 7
#define echoPin 8
#define backup_pump 2

// Define variables:
long duration;

float distance;
int head_count;

LiquidCrystal_I2C lcd(0x27, 8, 2);


void setup() {
  // Define inputs and outputs
  pinMode(backup_pump,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin();
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(115200);
}

void loop() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance:
  distance = duration * 0.034 / 2;


  if(distance < 120){
    digitalWrite(backup_pump,HIGH);
    head_count++;
    lcd_display();
    delay(3000);
    digitalWrite(backup_pump,LOW);
  }
    
  

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Water Level = ");
  Serial.print(head_count);
  Serial.println("%");
  

  lcd_display();

  delay(1000);
}


void lcd_display()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Head count:  ");
  lcd.setCursor(0, 1);
  lcd.print(head_count);
}
