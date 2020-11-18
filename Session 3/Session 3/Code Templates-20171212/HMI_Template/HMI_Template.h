///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// HMI_Template.h: HMI Template Sketch                       //
//                 Session 3 - IR Line Following             // 
//                                                           // 
///////////////////////////////////////////////////////////////

#ifndef HMI_Template_h
#define HMI_Template_h

// Defines
#define HMI 0xA1	//I2C Addresses
#define CAR 0xA2
#define SENSOR 0xA3

// Union for PID constant values sent over I2C
union PIDConstVal
{
  byte rawValues[sizeof(float)];
  float value;
};

// Function declarations
void requestEvent(void);
void receiveEvent(int howMany);
void emptyBuffer(void);

// Global Variables
boolean newCommandFlag = false;
boolean commandActive = false;
char command = 0;
int parameter = 0;
int returnData = 0;

PIDConstVal Kp;
PIDConstVal Ki;
PIDConstVal Kd;

// List of commands available
#define NUM_COMMANDS 1
char commandList[NUM_COMMANDS] = {'D'};
	//'D' = set the data to be returned: 0 = Kp, 1 = Ki, 2 = Kd

#endif
