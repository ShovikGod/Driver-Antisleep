#include <Wire.h>

const int MPU_addr=0x68;
int16_t axis_X, axis_Y, axis_Z;
int minVal=265, maxVal=402;
double x, y, z;
int LED=2;

void setup(){
  pinMode(LED,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  axis_X=Wire.read()<<8|Wire.read();
  axis_Y=Wire.read()<<8|Wire.read();
  axis_Z=Wire.read()<<8|Wire.read();
  int xAng=map(axis_X,minVal,maxVal,-90,90);
  int yAng=map(axis_Y,minVal,maxVal,-90,90);
  int zAng=map(axis_Z,minVal,maxVal,-90,90);
  z=RAD_TO_DEG*(atan2(-yAng,-xAng)+PI);
  Serial.println(z);
  if(z>=255 && z<=290){
    Serial.println("OFF!!");
    digitalWrite(LED,LOW);
  }
  else{
    Serial.println("ON!!");
    digitalWrite(LED,HIGH);
  }
  delay(100);
}
