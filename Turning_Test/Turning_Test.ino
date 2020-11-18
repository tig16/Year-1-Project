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
  
  delay(1500);


  //Motor 1 & 2 (Left) forward
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);

  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);

  //Motor 3 & 4 (Right) backwards
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);

  delay(600);

  /* Braking Mechanism*/

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);

  delay(40);

  //Turning off motors
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  while (1);
}
