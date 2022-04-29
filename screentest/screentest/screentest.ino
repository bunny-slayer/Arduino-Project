#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int BUZ1 = D0;
void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(BUZ1, OUTPUT);
  digitalWrite(BUZ1, LOW);
}
void loop() {
  digitalWrite(BUZ1, HIGH); // สั่งให้ ขา D0 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(250); // หน่วงเวลา 50mS
  digitalWrite(BUZ1, LOW);  // สั่งให้ ขา D0 ปล่อยลอจิก 0 ไฟ LED ดับ
  delay(250);
  lcd.clear();
  lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
  lcd.print("LCD1602 START"); //พิมพ์ข้อความ "LCD1602 I2c Test"
  lcd.setCursor(2, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
  lcd.print("myarduino.net"); //พิมพ์ข้อความ "myarduino.net"
  delay(250);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(0,1);
  lcd.print("World");
  delay(250);
}
