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
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);   
  delay(5000);
  digitalWrite(5, LOW);
  digitalWrite(9, LOW);  
  delay(5000) ;
  digitalWrite(9, HIGH);
  delay(5000);
  digitalWrite(9, LOW);
  delay(5000);

  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);   
  delay(5000);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);  
  delay(5000) ;
  digitalWrite(10, HIGH);
  delay(5000);
  digitalWrite(10, LOW);
  delay(5000);

  digitalWrite(7, HIGH);
  digitalWrite(11, HIGH);   
  delay(5000);
  digitalWrite(7, LOW);
  digitalWrite(11, LOW);  
  delay(5000) ;
  digitalWrite(11, HIGH);
  delay(5000);
  digitalWrite(11, LOW);
  delay(5000);

  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);   
  delay(5000);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);  
  delay(5000) ;
  digitalWrite(12, HIGH);
  delay(5000);
  digitalWrite(12, LOW);

  while(1);
}
