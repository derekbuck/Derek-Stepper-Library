/*
  DerekStepper - Library for controlling bipolar stepper drivers.
  Compatible drivers: A4988, DRV8825, and more to come.
  Created by Derek D. Boekelheide, November 17, 2020.
*/

#include "DerekStepper.h"

//Pin Variables
const byte dirPin = 3;    //Direction Pin
const byte stepPin = 2;   //Step Pin
const byte ms1 = 10;      //Microstep Pins
const byte ms2 = 11;
const byte ms3 = 12;

const int stepsPerRevolution = 200;   //Change to match the motor you are using

Stepper stepper(A4988, stepsPerRevolution, dirPin, stepPin);   //Initialize stepper

void setup() {
  stepper.microstepPins(ms1, ms2, ms3); //Enable microstepping
  stepper.stepSize(1);                  //set microstep size(1, 2, 4, 8, or 16)
  stepper.stepperSpeed(60);             //Set stepper speed, in RPMs (60 RPMS)
}

void loop() {
  stepper.step(stepsPerRevolution);   //Turn one revolution
  delay(1000);                        //Delay one second
  stepper.step(-stepsPerRevolution);  //Turn back one revolution
  delay(1000);                        //Delay one second
}
