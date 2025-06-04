#include "Arduino.h"
#include <Wire.h>
#include <MPU6050.h>
#include <L298N.h>
int ENA = 19;
int IN1 = 23;
int IN2 = 18;
float kP = 850;
float kD = 65;
double z;
double speed;
MPU6050 mpu;
// Create L298N motor object
float angle_offset = -10.3 +10.17;;
L298N motor(ENA, IN1, IN2);

const float sensor_bias = 0.85;
const float GYRO_SENS = 131.0;
float angle = 0;
unsigned long lastTime = 0;
//kP= 636, kD = 65

// Define equilibrium zone and parameters
const float EQUILIBRIUM_ZONE = 10.0; // Dead zone around 0/360 degrees
const int MIN_SPEED = 50; // Minimum speed to ensure motor movement
const int MAX_SPEED = 255; // Maximum motor speed
void changeCalibration(){
  if (Serial.available() > 0){
    switch (Serial.read()){
      case 'w':kP += 5; Serial.printf("Changed kP to %f\n",kP);delay(1000);delay(100);break;
      case 's':kP -= 5; Serial.printf("Changed kP to %f\n",kP);delay(1000);break;
      case 'a':kD -= 5; Serial.printf("Changed kD to %f\n", kD);delay(1000);break;
      case 'd':kD += 5; Serial.printf("Changed kD to %f\n",kD);delay(1000);break;
      case 'c': Serial.printf("KP : %f, KD: %f",kP,kD); delay(1000);break;
      default: ;
    }

  }
}
void setup(){
  Wire.begin();
  Serial.begin(115200);
  mpu.initialize();
  Serial.println("connect MPU6050");
  lastTime = millis();
}
float last_angle = 0;
void loop(){

  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  changeCalibration();
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  float accel_angle = atan2((float)ay, -(float)ax) - angle_offset ;
  float gyroRate = (float)gz / GYRO_SENS;
  float gyroAngle = gyroRate * dt + angle;
  angle = sensor_bias * (gyroAngle) +
          (1 - sensor_bias) * accel_angle; // may not help for yaw

  float derivative = (angle - last_angle) / dt;
  float output = kP * angle - kD * derivative;
  last_angle = angle;
  if (output > 0){
      Serial.println("Moving Forward");
      motor.forward();
  }else{
    Serial.println("Moving Backward");
      motor.backward();
   }
  motor.setSpeed(abs(output));
  Serial.printf("Speed: %f", abs(output));
  Serial.println(gyroAngle);

}
