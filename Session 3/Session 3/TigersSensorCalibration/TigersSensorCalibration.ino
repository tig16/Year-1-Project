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

int sensorMapBlackValue1;
int sensorMapBlackValue2;
int sensorMapBlackValue3;
int sensorMapBlackValue4;

int sensorWhiteValue1;
int sensorWhiteValue2;
int sensorWhiteValue3;
int sensorWhiteValue4;

int sensorMapWhiteValue1;
int sensorMapWhiteValue2;
int sensorMapWhiteValue3;
int sensorMapWhiteValue4;

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

  Serial.println("Put car under white");
  delay(5000);
  sensorWhiteValue1 = analogRead(A0);
  sensorWhiteValue2 = analogRead(A1);
  sensorWhiteValue3 = analogRead(A2);
  sensorWhiteValue4 = analogRead(A3);
  delay(100);

  Serial.println("Put car under black");
  delay(5000);
  sensorBlackValue1 = analogRead(A0);
  sensorBlackValue2 = analogRead(A1);
  sensorBlackValue3 = analogRead(A2);
  sensorBlackValue4 = analogRead(A3);
  delay(100);

  int  a = 2;
  while (a > 1)
    // Read the sensor values
  {
    sensorValue1 = analogRead(A0);
    Serial.println("sensor 1");
    Serial.println(sensorValue1);
    delay(100);

    sensorValue2 = analogRead(A1);
    Serial.println("sensor 2");
    Serial.println(sensorValue2);
    delay(100);

    sensorValue3 = analogRead(A2);
    Serial.println("sensor 3");
    Serial.println(sensorValue3);
    delay(100);

    sensorValue4 = analogRead(A3);
    Serial.println("sensor 4");
    Serial.println(sensorValue4);
    delay(100);

    // black


    sensorBlackValue1 = constrain(sensorBlackValue1, sensorValue1, 1000);
    sensorBlackValue2 = constrain(sensorBlackValue2, sensorValue2, 1000);
    sensorBlackValue3 = constrain(sensorBlackValue3, sensorValue3, 1000);
    sensorBlackValue4 = constrain(sensorBlackValue4, sensorValue4, 1000);

    sensorMapBlackValue1 = map(sensorBlackValue1, 0, 1023, 0, 255);
    sensorMapBlackValue2 = map(sensorBlackValue2, 0, 1023, 0, 255);
    sensorMapBlackValue3 = map(sensorBlackValue3, 0, 1023, 0, 255);
    sensorMapBlackValue4 = map(sensorBlackValue4, 0, 1023, 0, 255);

    Serial.println("MAP Black sensor 1");
    Serial.println(sensorMapBlackValue1);
    Serial.println("MAP Black sensor 2");
    Serial.println(sensorMapBlackValue2);
    Serial.println("MAP Black sensor 3");
    Serial.println(sensorMapBlackValue3);
    Serial.println("MAP Black sensor 4");
    Serial.println(sensorMapBlackValue4);

    delay(300);

    // white
    sensorWhiteValue1 = constrain(sensorWhiteValue1, 10, sensorValue1);
    sensorWhiteValue2 = constrain(sensorWhiteValue2, 10, sensorValue2);
    sensorWhiteValue3 = constrain(sensorWhiteValue3, 10, sensorValue3);
    sensorWhiteValue4 = constrain(sensorWhiteValue4, 10, sensorValue4);

    sensorMapWhiteValue1 = map(sensorWhiteValue1, 0, 1023, 0, 255);
    sensorMapWhiteValue2 = map(sensorWhiteValue2, 0, 1023, 0, 255);
    sensorMapWhiteValue3 = map(sensorWhiteValue3, 0, 1023, 0, 255);
    sensorMapWhiteValue4 = map(sensorWhiteValue4, 0, 1023, 0, 255);

    Serial.println("MAP white sensor 1");
    Serial.println(sensorMapWhiteValue1);
    Serial.println("MAP white sensor 2");
    Serial.println(sensorMapWhiteValue2);
    Serial.println("MAP white sensor 3");
    Serial.println(sensorMapWhiteValue3);
    Serial.println("MAP white sensor 4");
    Serial.println(sensorMapWhiteValue4);

    delay(5000);
  }
  // WA =


  /* ADD your own code to use the perform the line following */


  /*// Calculate the weighted average and the error
    float WA = ((sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4) / 4) ;
    float error = 0 - WA;
  */

  // Calculate the result of the PID
  //  float speedChange = calcPID(error);
  //  Serial.println("speedChange is ");
  //  Serial.println(speedChange);




  // Transimit 4 values of sensors to HMI sensor
  writeToI2C(HMI, 'H', sensorValue1);
  writeToI2C(HMI, 'I', sensorValue2);
  writeToI2C(HMI, 'J', sensorValue3);
  writeToI2C(HMI, 'K', sensorValue4);


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

