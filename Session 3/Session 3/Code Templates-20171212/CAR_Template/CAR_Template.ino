///////////////////////////////////////////////////////////////
//                                                           // 
// H61AEE: Dept. EEE, The University of Nottingham 2017      //
// Author: D. Fallows                                        //
//                                                           //
// CAR_Template.ino: Vehicle Template Sketch                 //
//                   Session 3 - IR Line Following           //
//                                                           // 
///////////////////////////////////////////////////////////////

// Libraries
#include <Wire.h>
#include <H61AEE_S03.h>
#include "CAR_Template.h"

void setup() {
  Wire.begin(CAR);              // join i2c bus as the car
  Wire.onReceive(receiveEvent); // register function to be called whenever data is received
  Wire.onRequest(requestEvent); // register function to be called when data needs to be transmitted
  
  Serial.begin(9600);           // start serial for output

  pinMode(YELLOW_LED, OUTPUT);   // Configure LED outputs
  pinMode(RED_LED, OUTPUT);

  car.setupVehicle();
}

void loop() {  

  //Serial.println("Recieved");
  //delay(500);

  
  // Check if a new command has been received and process the result
  if(newCommandFlag)
  {
    commandActive = true;
    switch(command)
    {
      
      case 'L': car.setSpeed(M1, (-parameter));
                car.setSpeed(M2, (parameter));
                break;
      case 'R': car.setSpeed(M3, parameter);
                car.setSpeed(M4, parameter);
                break;
      case 'S': car.setSpeed(ALL, 0);
                break;
      case 'D': returnData = parameter;
                break;
    }
    
    commandActive = false;    // Reset flags
    newCommandFlag = false;
  }
}

// This function executes whenever I2C data is received
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
  // Check what data is required based on the last Data command
  if(returnData == 0)
  {
    Wire.write(commandActive);
  }
  else if(returnData == 1)
  {
    unsigned long encoder = car.readEncoder(LEFT);  // the encoder value is a 4 byte number
    
    Wire.write((byte)((encoder & 0xFF000000) >> 24)); // send each byte separately from MSB to LSB
    Wire.write((byte)((encoder & 0x00FF0000) >> 16));
    Wire.write((byte)((encoder & 0x0000FF00) >> 8));
    Wire.write((byte)(encoder & 0x000000FF));
  }
  else if(returnData == 2)
  {
    unsigned long encoder = car.readEncoder(RIGHT);  // the encoder value is a 4 byte number
    
    Wire.write((byte)((encoder & 0xFF000000) >> 24)); // send each byte separately from MSB to LSB
    Wire.write((byte)((encoder & 0x00FF0000) >> 16));
    Wire.write((byte)((encoder & 0x0000FF00) >> 8));
    Wire.write((byte)(encoder & 0x000000FF));
  }
}

