///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// HMI_Template.ino: HMI Template Sketch                     //
//                   Session 3 - IR Line Following           // 
//                                                           // 
///////////////////////////////////////////////////////////////

// Libraries
#include <Wire.h>
#include "HMI_Template.h"

void setup() {
  Wire.begin(HMI);              // join i2c bus as the HMI
  Wire.onReceive(receiveEvent); // register function to be called whenever data is received
  Wire.onRequest(requestEvent); // register function to be called when data needs to be transmitted
  
  Serial.begin(9600);

  Kp.value = 0; // initialise the PID constants
  Ki.value = 0;
  Kd.value = 0;

  /* CONFIGURE you inputs and outputs here, call any setup functions required */
}

void loop() {
  /* ADD your own code to use the HMI to set the PID values */
  
  // Check if a new command has been received and process the result
  if(newCommandFlag)
  {
    commandActive = true;
    switch(command)
    {
      case 'D': returnData = parameter;
                break;
    }
    
    commandActive = false;    // Reset flags
    newCommandFlag = false;
  }
}

void receiveEvent(int howMany)
{
  if(howMany != 3)  // Commands should be 3 bytes long. Anything else is an error
  {
    emptyBuffer();
    return;
  }
  
  command = Wire.read(); // Read the first byte (the command character)

  boolean commandFound = false;   // Check the received command against the list of valid commands
  for(int i = 0; i < NUM_COMMANDS; i++)
  {
    if(command == commandList[i])
    {
      commandFound = true;
    }
  }
  if(!commandFound)   // If the command isn't on the list then ignore
  {
    emptyBuffer();
    return;
  }
  
  byte MSB = Wire.read();   // receive MSB of parameter
  byte LSB = Wire.read();   // receive LSB of parameter

  parameter = (MSB << 8) | LSB; // combine the two bytes into an integer

  newCommandFlag = true;  // Set the flag to indicate a new command is ready for processing
}

// Function to clear the I2C buffer
void emptyBuffer(void)
{
  while(Wire.available())
  {
    Wire.read();
  }
}

// This function is executed whenever data is requested
void requestEvent(void) {
  PIDConstVal returnVal;
  returnVal.value = 0;
  
  // Check what data is required based on the last Data command
  switch(returnData)
  {
    case 0: returnVal = Kp;
            break;
    case 1: returnVal = Ki;
            break;
    case 2: returnVal = Kd;
            break;
  }

  for(byte i = 0; i < sizeof(float); i++)
    Wire.write(returnVal.rawValues[i]); // send each byte separately from MSB to LSB
}

