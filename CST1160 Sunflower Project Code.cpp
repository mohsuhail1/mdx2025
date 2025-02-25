#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int waterSensorPin = A0;   // Water sensor 
int servoPin = 10;         // Servo Motor
int waterThreshold = 600;  // Threshold for the servo motor to move

Servo Myservo;
bool servomovement = false; 
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  pinMode(waterSensorPin, INPUT);
  Myservo.attach(servoPin);
  Serial.begin(9600); 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Clear");
  Myservo.write(0);
}

void loop() {
  int sensorValue = analogRead(waterSensorPin); // Read moisture level
  Serial.print("Moisture Level: ");
  Serial.println(sensorValue);  // Print the moisture level to the Serial Monitor
  if (sensorValue >= waterThreshold ) {
    if (!servomovement) {
      for (int pos = 0; pos <= 90; pos++) {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("RAIN!!!!!");
        Myservo.write(pos);  // Move servo to the current position
        delay(15);  
      }
    servomovement = true;
    delay(5000); //wait for 5 seconds to check again when under the roof 
    }
  }
  else if (sensorValue < waterThreshold && servomovement) {
     for (int pos = 90; pos >= 0; pos--) {
      lcd.clear(); // Clear previous message
      lcd.setCursor(3, 0); // Set cursor to the same position as in setup
      lcd.print("CLEAR"); // Display "CLEAR" message
      Myservo.write(pos);
      delay(15);
     }
    servomovement = false;
  }
}