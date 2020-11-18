///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// SENSOR_Template.h: HMI Template Sketch                    //
//                    Session 3 - IR Line Following          // 
//                                                           // 
///////////////////////////////////////////////////////////////

#ifndef SENSOR_Template_h
#define SENSOR_Template_h

// Defines
#define HMI 0xA1	//I2C Addresses
#define CAR 0xA2
#define SENSOR 0xA3

#define KP 0
#define KI 1
#define KD 2

// Function declarations
void writeToI2C(char device, char command, int parameter);
float readHMIConst(char PIDConst);
float calcPID(float error);

// Global Variables
boolean newCommandFlag = false;
boolean commandActive = false;
char command = 0;
int parameter = 0;
int returnData = 0;

float Kp = 0;
float Ki = 0;
float Kd = 0;

// List of commands available
#define NUM_COMMANDS 1
char commandList[NUM_COMMANDS] = {'D'};
	//'D' = set the data to be returned: 0 = Kp, 1 = Ki, 2 = Kd

// Union for PID constant values sent over I2C
union PIDConstVal
{
  byte rawValues[sizeof(float)];
  float value;
};


#endif
