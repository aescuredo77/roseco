#ifndef MotorA_h
#define MotorA_h
#include "Arduino.h"
#pragma once
#include <Wire.h>

/// instructions
#define DIR 0x10
#define DIRSPEED 0x11
#define POS 0x20
#define POSSPEED 0x21
#define READPOS 0x30
#define CLEAR 0x40
///type motors
#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1
#define LIDAR 2
#define GRIPPER 3
#define ARM_BASE 4
#define ARM_RIGHT 5
#define ARM_LEFT 6

class motor
{
  public:
    motor(int type);
    motor(int type, int address);
    void dir(int _dir);
    void dirSpeed(int _dir, int _speed);
    void pos(int _pos);
    void posSpeed(int _pos, int _speed);
    int16_t readpos();
    void clearcount();
    uint8_t _delay=2;
  private:
    int _type;
    uint8_t _address;
    
};
#endif
