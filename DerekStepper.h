/*
  DerekStepper.h - Library for controlling bipolar stepper drivers.
  Created by Derek D. Boekelheide, November 29, 2020.
  Released into the public domain.
*/

#ifndef DerekStepper_h
#define DerekStepper_h

#include "Arduino.h"

#define A4988 0
#define DRV8825 1
#define TB6600 255

class Stepper
{
  public:
    Stepper(byte driverType, int stepsPerRevolution, byte dirPin, byte stepPin);
    void microstepPins (byte ms1, byte ms2, byte ms3);
    void step(long steps);
    void stepSize(byte stepSize);
    void stepperSpeed(float rpm);
  private:
    byte _stepSize = 1;
    long _stepFrequency;
    byte _driverType;
    int _stepsPerRevolution;
    byte _dirPin;
    byte _stepPin;
    byte _ms1;
    byte _ms2;
    byte _ms3;
};

#endif