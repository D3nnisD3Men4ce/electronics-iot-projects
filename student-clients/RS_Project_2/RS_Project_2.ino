#include <DHT.h>;
//I2C LCD:
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display,Pls check your lcd.
  
//Constants
#define DHTPIN 12     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22
#define mist_pump 13
#define manual_mist 14
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino



//Variables
//int chk;
int h;  //Stores humidity value
int t; //Stores temperature value
int ButtonState     = 0;   // take current button state
int LastButtonState = 0;   // take last button state
int MistState        = 0;  // take light status

void setup()
{
    Serial.begin(115200);
    Serial.println("Temperature and Humidity Sensor Test");
    dht.begin();
    lcd.begin();
    pinMode(mist_pump, OUTPUT);
    pinMode(manual_mist, INPUT_PULLUP);
}


void loop()
{
    //Read data and store it to variables h (humidity) and t (temperature)
    // Reading temperature or humidity takes about 250 milliseconds!
    h = dht.readHumidity();
    t = dht.readTemperature();

  
    ButtonState = digitalRead(manual_mist);
  
    if (LastButtonState == 0 && ButtonState == 1)
    {
      if (MistState == 0)
      {
        digitalWrite(mist_pump, HIGH);
        MistState = 1;

      }
      
      else
      {
        digitalWrite(mist_pump, LOW);
        MistState = 0;
      }
    }
    LastButtonState = ButtonState;
    delay(100);

    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(t);
    Serial.println(" ° Celsius");


    if (MistState == 0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(t);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Hum:");
        lcd.print(h);
        lcd.print("%");
          
        delay(1000); //Delay 1 sec.
    } else{
      Serial.println("Misting");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(t);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Hum:");
        lcd.print(h);
        lcd.print("%");
        lcd.setCursor(10, 0);
        lcd.print("MIST");
        lcd.setCursor(10, 1);
        lcd.print("ACTIVE");
        delay(1000); //Delay 1 sec.
    }

    



    //This portion only runs when temperature is greater than 30 and humidity is less than 50
    //This condition can be modified depending on the user
    if (t > 34 && h < 50 && MistState == 0){
      digitalWrite(mist_pump, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp:");
        lcd.print(t);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Hum:");
        lcd.print(h);
        lcd.print("%");
        lcd.setCursor(10, 0);
        lcd.print("MIST");
        lcd.setCursor(10, 1);
        lcd.print("ACTIVE");
      delay(180000); // Turn on pump for 3 minutes or 180000 milliseconds
      digitalWrite(mist_pump, LOW); //Turns off after delay
      delay(3600000); // Turn off for 1 hour
    }
  

}
