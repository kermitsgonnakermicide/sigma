#include "Arduino.h"
#include <Wire.h>
#include "mpu.h"


int ENA = 19;
int IN1 = 23;
int IN2 = 18;

double speed;

void setup(){
  MPU::setup(0x68);
  Serial.begin(115200);
}
void loop(){
  float x, y, z;
  MPU::getAngle(&x, &y, &z);

  if (z >= 180){
  speed = map(z, 180, 360, 0, 255);
  }
  else{
    speed = map(z, 0, 180, 255, 0);
  }
  Serial.println(speed);

  if (z >= 180){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
  }
  else{
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
    analogWrite(ENA, speed);
  }
}