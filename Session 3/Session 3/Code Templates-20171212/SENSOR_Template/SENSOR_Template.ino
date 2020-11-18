///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// SENSOR_Template.ino: HMI Template Sketch                  //
//                      Session 3 - IR Line Following        // 
//                                                           // 
///////////////////////////////////////////////////////////////

// Libraries
#include <Wire.h>
#include "SENSOR_Template.h"

void setup() {
  Wire.begin(SENSOR);           // join i2c bus as the Sensor board
  
  Serial.begin(9600);

  /* CONFIGURE you inputs and outputs here, call any setup functions required */

  // Initilalise the PID constants
  Kp = readHMIConst(KP);
  Ki = readHMIConst(KI);
  Kd = readHMIConst(KD);
}

void loop() {
  /* ADD your own code to use the perform the line following */

  // Read the sensor values
  // Calculate the weighted average and the error
  float WA = ?;
  float error = 0 - WA;
  // Calculate the result of the PID
  float speedChange = calcPID(error);
  // Set the speed of the motors
  writeToI2C(CAR, 'L', baseSpeed + speedChange);
  writeToI2C(CAR, 'R', baseSpeed - speedChange);
}

float calcPID(float error)
{
  static float errorOld = 0;
  static float errorSum = 0;
  
  errorSum += error;
  float errorDiff = error - errorOld;
  
  float pidOutput = (Kp*error) + (Ki*errorSum) + (Kd*errorDiff);
  
  errorOld = error;

  return pidOutput;
}

void writeToI2C(char device, char command, int parameter)
{
  Wire.beginTransmission(device); // transmit to car
    Wire.write(command);  // send the command first
    Wire.write((byte)((parameter & 0xFF00) >> 8));  // send the parameter as two bytes
    Wire.write((byte)((parameter & 0x00FF)));
  Wire.endTransmission();    // stop transmitting
}

float readHMIConst(char PIDConst)
{
  PIDConstVal constantVal;

  writeToI2C(HMI, 'D', PIDConst);
  
  Wire.requestFrom(HMI, 4);      // request constant value from the HMI
  
  for(byte i = 0; i < sizeof(float); i++)
    constantVal.rawValues[i] = Wire.read();  // reconstruct the float from the recieved bytes

  return constantVal.value;
}

