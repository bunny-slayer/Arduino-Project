#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzerPin = D0;
int infra = D4;
int ledPin = D3;
int cameraPin = D5;
int val = 0;
void setup() {
  pinMode(ledPin, OUTPUT);  // sets the pin as output
  pinMode(infra, INPUT); // sets the pin as input
  pinMode(buzzerPin, OUTPUT);
  pinMode(cameraPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(cameraPin, LOW);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Status:"); 
  lcd.setCursor(0, 1); 
  lcd.print("Device Standby");
}
int count = 0 ;
int start = 0 ;
int lasttime = 0 ; 
int state = 0;
void loop() {
  unsigned int now = millis(); 
  int sensorvalue = digitalRead(infra);
  if (sensorvalue == 0 && start == 0 && state == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status:"); 
    lcd.setCursor(0, 1); 
    lcd.print("ATK Detected");
    lasttime = millis();
    count = 0 ;
    start = 1;
    state = 1;
  }
    if(now - lasttime > 1000 && start == 1)
  {
    Serial.println(count);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: Waiting"); 
    lcd.setCursor(0, 1); 
    lcd.print(10-count);
    lasttime = now;
    count+=1;
    if(count >= 10)
    {
      Serial.println("Send img to line already!");
      digitalWrite(cameraPin, HIGH);
      count = 0;
      start = 0;
      while(state == 1)
      {
           if (!digitalRead(infra)){
            state = 0;
           }
           digitalWrite(ledPin, HIGH);
           digitalWrite(buzzerPin, LOW);
           delay(100);
           digitalWrite(ledPin, LOW);
           digitalWrite(buzzerPin, HIGH);
           delay(100);
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Status:"); 
           lcd.setCursor(0, 1); 
           lcd.print("LINE Sent");
      }
      digitalWrite(cameraPin, LOW);
      Serial.println("Finish!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Status:"); 
      lcd.setCursor(0, 1); 
      lcd.print("Device Standby");
    }
  }
  delay(100);
}
