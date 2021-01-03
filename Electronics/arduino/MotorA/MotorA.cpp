#include "Arduino.h"
#include "MotorA.h"

motor::motor(int type)
{
  _type=type;
  switch(type){
    case 0: // right motor
          _address=0x10;
          break;
    case 1: // left motor
          _address=0x11;
          break;
    case 2: // Lidar
          _address=0x20;
          break;
    case 3: // Gripper
          _address=0x08;
          break;
    case 4: //Abase
          _address=0x18;
          break;
    case 5: // Aright
          _address=0x19;
          break;
    case 6: // Aleft
          _address=0x1A;
          break;
        
  }
}

motor::motor(int type, int address)
{
    _type = type;
    _address = address;
}

/*
Direction  0: Stop,1:CW,2:CCW 
*/

 void motor::dir(int _dir)
 {
  if(_type==0 || _type==1 || _type==2) {
    // i2cWritebyte(_address,DIR,_dir);
    Wire.beginTransmission(_address); 
    Wire.write(DIR);
    Wire.write(_dir);
    Wire.endTransmission();
    delay(_delay); 
  }
 }
/*
 {0: Stop,1:CW,2:CCW}, speed[0..255] 
 */
 void motor::dirSpeed(int _dir, int _speed)
 {
  if(_type==0 || _type==1 || _type==2) {
    //i2cWrite3byte(adI2c,DIRSPEED,_dir,_speed);
    Wire.beginTransmission(_address); 
    Wire.write(DIRSPEED);
    Wire.write(_dir);
    Wire.write(_speed);
    Wire.endTransmission();
    delay(_delay);
  }
 }
 
 void motor::pos(int _pos)
 {
   //i2cWrite2byte (adI2c,0x20, posición);
   Wire.beginTransmission(_address); 
   Wire.write(POS);
   Wire.write(_pos>>8);
   Wire.write(_pos);
   Wire.endTransmission();
   delay(_delay);
 }
 void motor::posSpeed(int _pos, int _speed)
 {
  //i2cWrite4byte (adI2c,0x21,posición, 127);
  Wire.beginTransmission(_address); 
  Wire.write(POSSPEED);
  Wire.write(_pos>>8);
  Wire.write(_pos);
  Wire.write(_speed);
  Wire.endTransmission();
  delay(_delay);
 }
 int16_t motor::readpos()
 {
  //int16_t valor=i2cRead2byte(adI2c,0x30);
  int16_t dato=0;
  Wire.beginTransmission(_address); 
  Wire.write(READPOS);
  Wire.endTransmission();
  delay(_delay);
  Wire.requestFrom(_address, 1);
  dato = Wire.read(); // receive a byte as character
  Wire.requestFrom(_address, 1);
  dato |= Wire.read() << 8; // receive a byte as character
  Wire.endTransmission();
  delay(_delay);
  return dato;
 }
 void motor::clearcount()
 {
  Wire.beginTransmission(_address); 
  Wire.write(CLEAR);
  Wire.endTransmission();
  delay(_delay);
 }
