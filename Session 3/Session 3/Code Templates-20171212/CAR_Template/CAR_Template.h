///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// CAR_Template.h: Vehicle Template Sketch                   //
//                 Session 3 - IR Line Following             // 
//                                                           // 
///////////////////////////////////////////////////////////////

#ifndef CAR_Template_h
#define CAR_Template_h

// Defines
#define RED_LED 13
#define YELLOW_LED 4

#define HMI 0xA1	//I2C Addresses
#define CAR 0xA2
#define SENSOR 0xA3

// Function declarations
void requestEvent(void);
void receiveEvent(int howMany);
void emptyBuffer(void);

// Global variables
Vehicle car;
boolean newCommandFlag = false;
boolean commandActive = false;
char command = 0;
int parameter = 0;
int returnData = 0;

// List of commands available
#define NUM_COMMANDS 4
char commandList[NUM_COMMANDS] = {'L', 'R', 'S', 'D'};
	//'L' = set left motor speed
	//'R' = set right motor speed
	//'S' = stop the robot
	//'D' = set the data to be returned: 0 = command active, 1 = left encoder, 2 = right encoder

#endif