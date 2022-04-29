int LEDD0 = D0; // ขา D0
int LEDD1 = D1; // ขา D1
int buttonPin = D2;
int buttonState = 0;

void setup()
{
  pinMode(LEDD0, OUTPUT); // กำหนดการทำงานของขา D0 ให้เป็น Output
  pinMode(LEDD1, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(LEDD0, LOW);
  digitalWrite(LEDD1, LOW);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if(buttonState == LOW){
    digitalWrite(LEDD1, HIGH);
    Serial.print("LED :");
    Serial.println(buttonState);
    digitalWrite(LEDD0, HIGH); // สั่งให้ ขา D0 ปล่อยลอจิก 1 ไฟ LED ติด
    delay(250); // หน่วงเวลา 50mS
    digitalWrite(LEDD0, LOW);  // สั่งให้ ขา D0 ปล่อยลอจิก 0 ไฟ LED ดับ
    delay(250);
  }
  else{
    digitalWrite(LEDD1, LOW);
    Serial.print("LED :");
    Serial.println(buttonState);
  }
}
