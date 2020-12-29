/*
  DerekStepper.cpp - Library for controlling bipolar stepper drivers.
  Created by Derek D. Boekelheide, November 29, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "DerekStepper.h"

Stepper::Stepper(byte driverType, int stepsPerRevolution, byte dirPin, byte stepPin){
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  _driverType = driverType;
  _stepsPerRevolution = stepsPerRevolution;
  _dirPin = dirPin;
  _stepPin = stepPin;
}

void Stepper::microstepPins (byte ms1, byte ms2, byte ms3){
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  _ms1 = ms1;
  _ms2 = ms2;
  _ms3 = ms3;
}

void Stepper::step(long steps){
  if (steps){
    digitalWrite(_dirPin, steps < 0 ? 1 : 0);
    long _delayMicros = ((_stepFrequency / _stepSize) - 2);
    if (_delayMicros < 16383){
      for (long i = 0; i < (steps > 0 ? steps : -(steps)); i++) {
        digitalWrite(_stepPin, HIGH);
        delayMicroseconds(2);
        digitalWrite(_stepPin, LOW);
        delayMicroseconds(_delayMicros);
      }
    }
    else{
      for (long i = 0; i < (steps > 0 ? steps : -(steps)); i++) {
        digitalWrite(_stepPin, LOW);
        delay(2);
        digitalWrite(_stepPin, HIGH);
        delay(_delayMicros / 1000);
      }
    }
  }
}

void Stepper::stepSize(byte stepSize){  
  if (_driverType == 255) return;
  _stepSize = stepSize;
  byte keyCombo[2][6] = { {B000, B100, B010, B110, B111},
                          {B000, B100, B010, B110, B001, B111}
                        };
  digitalWrite(_ms1, (keyCombo[_driverType][(byte)(log(_stepSize) / log(2))] & B100) >> 2);
  digitalWrite(_ms2, (keyCombo[_driverType][(byte)(log(_stepSize) / log(2))] & B010) >> 1);
  digitalWrite(_ms3, (keyCombo[_driverType][(byte)(log(_stepSize) / log(2))] & B001));
}

void Stepper::stepperSpeed(float rpm){
  _stepFrequency = (60000000 / _stepsPerRevolution) / rpm;
}