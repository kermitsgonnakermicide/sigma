/*
Author  : Andrea Lombardo
Site    : https://www.lombardoandrea.com
Source  : https://github.com/AndreaLombardo/L298N/

Here you can see how to work in a common configuration. 

Speed range go from 0 to 255, default is 100.
Use setSpeed(speed) to change.

Sometimes at lower speed motors seems not running.
It's normal, may depends by motor and power supply.

Wiring schema in file "L298N - Schema_with_EN_pin.png"
*/

// Include the library
/* #include <L298N.h>

// Pin definition
const unsigned int IN1 = 23;
const unsigned int IN2 = 22;
const unsigned int EN = 19;
String jeff = "";
int speed = 70;
// Create one motor instance
L298N motor(EN, IN1, IN2);

void setup()
{
  // Used to display information
  Serial.begin(115200);
  // Set initial speed
  motor.setSpeed(speed);
}
void printSomeInfo()
{
  Serial.print("Motor is moving = ");
  Serial.print(motor.isMoving());
  Serial.print(" at speed = ");
  Serial.println(motor.getSpeed());
}
void loop()
{
  char f = '\n';
  if (Serial.available()){
    jeff = Serial.readStringUntil('\n');
    if (jeff == "a"){
      speed += 10;
      motor.setSpeed(speed);
      Serial.println("Speed: " + speed);
    }
    else if (jeff == "b"){
      speed += -10;
      motor.setSpeed(speed);
    }
    Serial.flush();
  }

}

/*
Print some informations in Serial Monitor
*/

/*
Author  : Andrea Lombardo
Site    : https://www.lombardoandrea.com
Source  : https://github.com/AndreaLombardo/L298N/

Here you can see how to work in a common configuration. 

Speed range go from 0 to 255, default is 100.
Use setSpeed(speed) to change.

Sometimes at lower speed motors seems not running.
It's normal, may depends by motor and power supply.

Wiring schema in file "L298N - Schema_with_EN_pin.png"
*/

// Include the library
#include <L298N.h>

// Pin definition
const unsigned int IN1 = 23;
const unsigned int IN2 = 22;
const unsigned int EN = 19;

// Create one motor instance
L298N motor(EN, IN1, IN2);

void setup()
{
  // Used to display information
  Serial.begin(9600);

  // Wait for Serial Monitor to be opened
  while (!Serial)
  {
    //do nothing
  }

  // Set initial speed
  motor.setSpeed(70);
}

void printSomeInfo()
{
  Serial.print("Motor is moving = ");
  Serial.print(motor.isMoving());
  Serial.print(" at speed = ");
  Serial.println(motor.getSpeed());
}

void loop()
{

  // Tell the motor to go forward (may depend by your wiring)
  motor.forward();

  // Alternative method:
  // motor.run(L298N::FORWARD);

  //print the motor status in the serial monitor
  printSomeInfo();

  delay(3000);

  // Stop
  motor.stop();

  // Alternative method:
  // motor.run(L298N::STOP);

  printSomeInfo();

  // Change speed
  motor.setSpeed(255);

  delay(3000);

  // Tell the motor to go back (may depend by your wiring)
  motor.backward();

  // Alternative method:
  // motor.run(L298N::BACKWARD);

  printSomeInfo();

  motor.setSpeed(120);

  delay(3000);

  // Stop
  motor.stop();

  printSomeInfo();

  delay(3000);
}

/*
Print some informations in Serial Monitor
*/