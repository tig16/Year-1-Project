void goForwards(int distanceUnit);
void turnLeft(int deg);
void turnRight(int deg);

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



/* Defining functions */



void goForwards(int distanceUnit)
{

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);

  delay(5.65 * distanceUnit);


  /* Car braking */
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  delay(15);
  
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

  /* Car stopping */
  delay(50);

  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
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

