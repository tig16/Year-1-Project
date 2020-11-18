// Libraries
#include <Wire.h>
#include "HMI_Template.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 3, 4, 5, 6, 7);

const int tonePin = 12;
int black;
int white;



int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;



void setup() {
  Wire.begin(HMI);              // join i2c bus as the HMI
  Wire.onReceive(receiveEvent); // register function to be called whenever data is received
  Wire.onRequest(requestEvent); // register function to be called when data needs to be transmitted
  Serial.begin(9600);
  lcd.begin(20, 4);



  black = 0;
  white = 0;

  Kp.value = 0; // initialise the PID constants
  Ki.value = 0;
  Kd.value = 0;




  /* CONFIGURE you inputs and outputs here, call any setup functions required */
}

void loop() {
  /* ADD your own code to use the HMI to set the PID values */







  digitalWrite(12, LOW);


  // Check if a new command has been received and process the result
  if (newCommandFlag)
  {
    commandActive = true;
    switch (command)
    {
      case 'D': returnData = parameter;
        break;

      case 'H':
        sensorValue1 = parameter;  // get values from master Arduino
        Serial.println("sensorValue1");
        Serial.println(sensorValue1);
      

      case 'I':
        sensorValue2 = parameter;  // get values from master Arduino
        Serial.println("sensorValue2");
        Serial.println(sensorValue2);
      

      case 'J':
        sensorValue3 = parameter;  // get values from master Arduino
        Serial.println("sensorValue3");
        Serial.println(sensorValue3);
     

      case 'K':
        sensorValue4 = parameter;  // get values from master Arduino
        Serial.println("sensorValue4");
        Serial.println(sensorValue4);

    }



    lcd.setCursor(0, 0);
    lcd.print(sensorValue1);
    Serial.println(sensorValue1);
    
    lcd.setCursor(0, 1);
    lcd.print(sensorValue2);
    Serial.println(sensorValue2);
    
    lcd.setCursor(0, 2);
    lcd.print(sensorValue3);
    Serial.println(sensorValue3);
    
    lcd.setCursor(0, 3);
    lcd.print(sensorValue4);
    Serial.println(sensorValue4);

    lcd.setCursor(3,0);
    lcd.print("");

    lcd.setCursor(3,1);
    lcd.print("");
    
    lcd.setCursor(3,2);
    lcd.print("");
    
    lcd.setCursor(3,3);
    lcd.print("");
    



    commandActive = false;    // Reset flags
    newCommandFlag = false;
  }
}

void receiveEvent(int howMany)
{
  if (howMany != 3) // Commands should be 3 bytes long. Anything else is an error
  {


    emptyBuffer();
    return;
  }

  command = Wire.read(); // Read the first byte (the command character)

  boolean commandFound = false;   // Check the received command against the list of valid commands
  for (int i = 0; i < NUM_COMMANDS; i++)
  {
    if (command == commandList[i])
    {
      commandFound = true;
    }
  }
  if (!commandFound)  // If the command isn't on the list then ignore
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
  while (Wire.available())
  {
    Wire.read();
  }
}

// This function is executed whenever data is requested
void requestEvent(void) {
  PIDConstVal returnVal;
  returnVal.value = 0;

  // Check what data is required based on the last Data command
  switch (returnData)
  {
    case 0: returnVal = Kp;
      break;
    case 1: returnVal = Ki;
      break;
    case 2: returnVal = Kd;
      break;
  }

  for (byte i = 0; i < sizeof(float); i++)
    Wire.write(returnVal.rawValues[i]); // send each byte separately from MSB to LSB
}

