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

int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;

int sensorBlackValue1;
int sensorBlackValue2;
int sensorBlackValue3;
int sensorBlackValue4;

int sensorWhiteValue1;
int sensorWhiteValue2;
int sensorWhiteValue3;
int sensorWhiteValue4;

int sensorMapValue1;
int sensorMapValue2;
int sensorMapValue3;
int sensorMapValue4;

int sensorDistance[4] = {0, 25, 53, 80};
int sensorWeight[4];

int i;


void setup() {


  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);



  Wire.begin(SENSOR);           // join i2c bus as the Sensor board

  Serial.begin(9600);

  /* CONFIGURE you inputs and outputs here, call any setup functions required */

  // Initilalise the PID constants
  Kp = 15; //readHMIConst(KP);
  Ki = 0.05; //readHMIConst(KI);
  Kd = 7;  //readHMIConst(KD);

  sensorBlackValue1 = 90;
  sensorBlackValue2 = 30;
  sensorBlackValue3 = 100;
  sensorBlackValue4 = 40;

  sensorWhiteValue1 = 800;
  sensorWhiteValue2 = 800;
  sensorWhiteValue3 = 800;
  sensorWhiteValue4 = 800;

}

void loop() {

   /* //Calibration Code
    Serial.println("Put car white");
    delay(5000);
    sensorWhiteValue1 = analogRead(A0);
    sensorWhiteValue2 = analogRead(A1);
    sensorWhiteValue3 = analogRead(A2);
    sensorWhiteValue4 = analogRead(A3);
    delay(100);
/*
    Serial.println("Put car in black");
    delay(5000);
    sensorBlackValue1 = analogRead(A0);
    sensorBlackValue2 = analogRead(A1);
    sensorBlackValue3 = analogRead(A2);
    sensorBlackValue4 = analogRead(A3);
    delay(100);
    Serial.println("Stop");
    delay(5000);
 *//*
    Serial.println(sensorWhiteValue1);
    Serial.println(sensorWhiteValue2);
    Serial.println(sensorWhiteValue3);
    Serial.println(sensorWhiteValue4);
/*
    Serial.println(sensorBlackValue1);
    Serial.println(sensorBlackValue2);
    Serial.println(sensorBlackValue3);
    Serial.println(sensorBlackValue4);

    delay(100);
  */

  // Read the sensor values. Put in loop if necessary

  //Serial.println("Place sensor on surface");

  sensorValue1 = analogRead(A0);
  //Serial.println("sensor 1");
  Serial.println(sensorValue1);
  //delay(10);

  sensorValue2 = analogRead(A1);
  //Serial.println("sensor 2");
  Serial.println(sensorValue2);
  //delay(10);

  sensorValue3 = analogRead(A2);
  //Serial.println("sensor 3");
  Serial.println(sensorValue3);
  //delay(10);

  sensorValue4 = analogRead(A3);
 // Serial.println("sensor 4");
  Serial.println(sensorValue4);
  //delay(10);
  
  // Calibrating


  sensorValue1 = constrain(sensorValue1, sensorBlackValue1, sensorWhiteValue1);
  sensorValue2 = constrain(sensorValue2, sensorBlackValue2, sensorWhiteValue2);
  sensorValue3 = constrain(sensorValue3, sensorBlackValue3, sensorWhiteValue3);
  sensorValue4 = constrain(sensorValue4, sensorBlackValue4, sensorWhiteValue4);

  sensorMapValue1 = map(sensorValue1, sensorBlackValue1, sensorWhiteValue1, 255, 0);  //change to 255 for weighing, 100 for percent
  sensorMapValue2 = map(sensorValue2, sensorBlackValue2, sensorWhiteValue2, 255, 0);
  sensorMapValue3 = map(sensorValue3, sensorBlackValue3, sensorWhiteValue3, 255, 0);
  sensorMapValue4 = map(sensorValue4, sensorBlackValue4, sensorWhiteValue4, 255, 0);

  //delay(10);

  sensorWeight[0] = sensorMapValue1;
  sensorWeight[1] = sensorMapValue2;
  sensorWeight[2] = sensorMapValue3;
  sensorWeight[3] = sensorMapValue4;
  
  //delay(50);
  //Serial.println(sensorWeight[0]);
  //Serial.println(sensorWeight[1]);
  //Serial.println(sensorWeight[2]);
  //Serial.println(sensorWeight[3]);
  
  float XS = 0;
  float S = 0;

  float WA = 0;

  for (i = 0; i < 4; i++)
  {
    XS = XS + sensorWeight[i] * sensorDistance[i];
    S = S + sensorWeight[i];
  }

  WA = XS / S;
  //delay(10);

  Serial.println("Weighted average:");
  Serial.println(WA);

  //delay(10);

  float error = (WA - 40) / 10;
  Serial.println("Error:");
  Serial.println(error);

  /* ADD your own code to use the perform the line following */


  /*// Calculate the weighted average and the error
    float WA = ((sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4) / 4) ;
    float error = 0 - WA;
  */

  //delay(10);


  //int maxmin = 25;
  //Calculate the result of the PID
  float speedChange = calcPID(error);
  speedChange = constrain(speedChange, -20, 20);
  Serial.println("speedChange is ");
  Serial.println(speedChange);




/*  // Transimit 4 values of sensors to HMI sensor
  writeToI2C(HMI, 'H', sensorValue1);
  writeToI2C(HMI, 'I', sensorValue2);
  writeToI2C(HMI, 'J', sensorValue3);
  writeToI2C(HMI, 'K', sensorValue4);
*/



  // Set the speed of the motors
  int baseSpeed = 11;
  /*
  writeToI2C(CAR, 'L', baseSpeed - speedChange);
  writeToI2C(CAR, 'R', baseSpeed + speedChange);
  */
  writeToI2C(CAR, 'L', (baseSpeed - speedChange));
  writeToI2C(CAR, 'R', (baseSpeed + speedChange)); 

  Serial.println();

  delay(10);
  
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

