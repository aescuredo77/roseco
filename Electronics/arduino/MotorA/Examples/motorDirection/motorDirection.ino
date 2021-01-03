#include <MotorA.h>
//#include <Wire.h>

motor m1(MOTOR_RIGHT);

void setup() {
  Wire.begin();
  // put your setup code here, to run once:

}

void loop() {
  m1.dir(1);
  delay(1000);
  m1.dir(0);
  delay(500);
  m1.dir(2);
  delay(1000);
  // put your main code here, to run repeatedly:

}
