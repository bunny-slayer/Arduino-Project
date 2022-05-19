#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzerPin = D0;
int digitalPin = D4;
int ledPin = D3;
int val = 0;
void setup() {
  pinMode(ledPin, OUTPUT);  // sets the pin as output
  pinMode(digitalPin, INPUT); // sets the pin as input
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, HIGH);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  val = digitalRead(digitalPin);  //อ่านค่าสัญญาณ digital ขาD1 ที่ต่อกับ เซ็นเซอร์ตรวจจับวัตถุ IR Infrared
  Serial.print("val = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val); // พิมพ์ค่าของตัวแปร val
  if (val == 0) { // ค่า เป็น 0  ตรวจจับเจอวัตถุ สั่งให้ไฟ LED ติด
    digitalWrite(ledPin, HIGH); // สั่งให้ LED ติดสว่าง
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
    lcd.print("Status:"); //พิมพ์ข้อความ "LCD1602 I2c Test"
    lcd.setCursor(0, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("Closed"); //พิมพ์ข้อความ "myarduino.net"
  }
  else {
    digitalWrite(ledPin, LOW); // สั่งให้ LED ดับ
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
    lcd.print("Status:"); //พิมพ์ข้อความ "LCD1602 I2c Test"
    lcd.setCursor(0, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("Far"); //พิมพ์ข้อความ "myarduino.net"
  }
  delay(100);
}
