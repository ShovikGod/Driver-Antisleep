#include <Wire.h>

const int MPU_addr = 0x68;
int16_t axis_X, axis_Y, axis_Z;
int minVal = 265, maxVal = 402;
double x, y, z;
unsigned long start=0, previous=0;
unsigned int BUZZER = 2, LED_R = 5, LED_G = 6, LED_R_state=1;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
}
void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  axis_X = Wire.read() << 8 | Wire.read();
  axis_Y = Wire.read() << 8 | Wire.read();
  axis_Z = Wire.read() << 8 | Wire.read();
  int yAng = map(axis_Y, minVal, maxVal, -90, 90);
  int zAng = map(axis_Z, minVal, maxVal, -90, 90);
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  Serial.println(x);
  if (x >= 235 && x <= 300) {
    Serial.println("OFF!!");
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, HIGH);
  }
  else {
    Serial.println("ON!!");
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED_G, HIGH);
    start = millis();
    if (start-previous>100){
      previous=start;
      if (LED_R_state==0)
        LED_R_state=1;
      else
        LED_R_state=0;
      digitalWrite(LED_R, LED_R_state);
    }
  }
  delay(50);
}
