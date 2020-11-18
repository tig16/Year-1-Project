/* Car Template predfined functions*/
void goForwards(int distanceUnit);
void turnLeft(int deg);
void turnRight(int deg);


/* Prototyping motor control functions*/
void m1Forward();
void m2Forward();
void m3Forward();
void m4Forward();
void m1Back();
void m2Back();
void m3Back();
void m4Back();

void leftForward();
void rightForward();
void leftBack();
void rightBack();
void stopMotors();


/*****************Main Code**************/
void setup() {
  pinMode(5, OUTPUT); //DIR 1
  pinMode(6, OUTPUT); //DIR 2
  pinMode(7, OUTPUT); //DIR 3
  pinMode(8, OUTPUT); //DIR 4
  pinMode(9, OUTPUT); //PWM 1
  pinMode(10, OUTPUT); //PWM 2
  pinMode(11, OUTPUT); //PWM 3
  pinMode(12, OUTPUT); //PWM 4

}

void loop() {

  goForwards(200);

  while (1);
}



/************Defining functions****************/


/* Motors forwards*/
void m1Forward()
{
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);  
}

void m2Forward()
{
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);  
}

void m3Forward()
{
  digitalWrite(7, HIGH);
  digitalWrite(11, HIGH);  
}

void m4Forward()
{
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);  
}

/* Motors backwards*/
void m1Back()
{
  digitalWrite(5, LOW);
  digitalWrite(9, HIGH);  
}

void m2Back()
{
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);  
}

void m3Back()
{
  digitalWrite(7, LOW);
  digitalWrite(11, HIGH);  
}

void m4Back()
{
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH);  
}

void leftForward()
{
  void m1Forward();
  void m2Forward();
}

void rightForward()
{
  void m1Forward();
  void m2Forward();
}

void leftBack()
{
  void m1Back();
  void m2Back();
}

void rightBack()
{
  void m3Back();
  void m4Back();
}


void stopMotors()
{
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);  
}


/**********Car Template Functions**********/
void goForwards(int distanceUnit)
{
  /* Going forwards */
  leftForward();
  rightForward();
  delay(5.65 * distanceUnit);

  /* Car braking */
  leftBack();
  delay(15);
  rightBack();

  /* Car stopping */
  delay(50);
  stopMotors();
}


/*
    void turnLeft(int deg)
  {
  // Write some code to make the car turn left
  }

  void turnRight(int deg)
  {
  // Write some code to make the car turn right
  }
*/

