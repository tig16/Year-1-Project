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
  
 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);


  
  Wire.begin(SENSOR);           // join i2c bus as the Sensor board

  Serial.begin(9600);

  /* CONFIGURE you inputs and outputs here, call any setup functions required */

  // Initilalise the PID constants
  Kp = readHMIConst(KP);
  Ki = readHMIConst(KI);
  Kd = readHMIConst(KD);
}

void loop() {

  // Read the sensor values
  int sensorValue1 = analogRead(A0);
  Serial.println("sensor 1");
  Serial.println(sensorValue1);
  delay(100);
  
  int sensorValue2 = analogRead(A1);
  Serial.println("sensor 1");
  Serial.println(sensorValue1);
  delay(100);
  
  int sensorValue3 = analogRead(A2);
  Serial.println("sensor 1");
  Serial.println(sensorValue1);
  delay(100);
  
  int sensorValue4 = analogRead(A3);
  Serial.println("sensor 1");
  Serial.println(sensorValue1);
  delay(100);


 constrain(sensorValue1,20,700);
 constrain(sensorValue2,20,700);
 constrain(sensorValue3,20,700);
 constrain(sensorValue4,20,700);

 sensorValue1 = map(sensorValue1,0,1023,0,255);
 sensorValue2 = map(sensorValue2,0,1023,0,255);
 sensorValue3 = map(sensorValue3,0,1023,0,255);
 sensorValue4 = map(sensorValue4,0,1023,0,255);
 

  

  // WA = ((sensorValue1+sensorValue2+sensorValue3+sensorValue4)/4)


  /* ADD your own code to use the perform the line following */


  /*// Calculate the weighted average and the error
    float WA = ((sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4) / 4) ;
    float error = 0 - WA;
  */

  // Calculate the result of the PID
  float speedChange = calcPID(error);
  Serial.println("speedChange is ")
  Serial.println(speedChange);
  


  
  // Transimit 4 values of sensors to HMI sensor
  writeToI2C(HMI, 'H', sensorValue1);
  writeToI2C(HMI, 'I', sensorValue2);
  writeToI2C(HMI, 'J', sensorValue3);
  writeToI2C(HMI, 'K', sensorValue4);

  Serial.println("sensor 1");
  Serial.println(sensorValue1);
  Serial.println("sensor 2");
  Serial.println(sensorValue2);
  Serial.println("sensor 3");
  Serial.println(sensorValue3);
  Serial.println("sensor 4");
  Serial.println(sensorValue4);
  Serial.println();
  Serial.println();
  Serial.println();


   /* // Set the speed of the motors
   int baseSpeed = -50
   writeToI2C(CAR, 'L', baseSpeed + speedChange);
   writeToI2C(CAR, 'R', baseSpeed - speedChange);
   */
  
}









// Leave it
float calcPID(float error)
{
  static float errorOld = 0;
  static float errorSum = 0;

  errorSum += error;
  float errorDiff = error - errorOld;

  float pidOutput = (Kp * error) + (Ki * errorSum) + (Kd * errorDiff);

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

  for (byte i = 0; i < sizeof(float); i++)
    constantVal.rawValues[i] = Wire.read();  // reconstruct the float from the recieved bytes

  return constantVal.value;
}

