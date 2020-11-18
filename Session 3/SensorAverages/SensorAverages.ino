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

int sensorValue1Total = 0;
int sensorValue2Total = 0;
int sensorValue3Total = 0;
int sensorValue4Total = 0;

int sensorValue1Avg = 0;
int sensorValue2Avg = 0;
int sensorValue3Avg = 0;
int sensorValue4Avg = 0;


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
  Kp = readHMIConst(KP);
  Ki = readHMIConst(KI);
  Kd = readHMIConst(KD);
}

void loop() {

  Serial.println("Put car on chosen surface");
  delay(5000)

  for (i = 0; i  < 25; i++)
  {
    sensorValue1Total = sensorValue1Total + analogRead(A0);
    sensorValue2Total = sensorValue2Total + analogRead(A1);
    sensorValue3Total = sensorValue3Total + analogRead(A2);
    sensorValue4Total = sensorValue4Total + analogRead(A3);
    delay(100);
  }


  /* Calculating avergae for each sensor on chosen surface*/
  sensorValue1Avg = sensorValue1Total / 25;
  sensorValue2Avg = sensorValue2Total / 25;
  sensorValue3Avg = sensorValue3Total / 25;
  sensorValue4Avg = sensorValue4Total / 25;
  delay(100);

  Serial.println("Measurements have concluded");
  delay(100);

  /*Printing average sensor values*/
  Serial.println(sensorValue1Avg);
  Serial.println(sensorValue2Avg);
  Serial.println(sensorValue3Avg);
  Serial.println(sensorValue4Avg);

  while (1);



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

