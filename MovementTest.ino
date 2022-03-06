const int IN1 = 2; //MSB for motor 0
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5; // MSB for motor 1
const int ENA = 10; // motor 0 enable
const int ENB = 11; // motor 1 enable

int RMS = 200;
int LMS = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  goForward();
  delay(2000);
  goReverse();
  delay(2000);
  goRight();
  delay(2000);
  goLeft();
  delay(2000);
}

void goLeft()
{
    digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going left");
  delay(2000);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void goRight(){
digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going right");
  delay(2000);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void goForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going forward");
  delay(2000);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

}
void goReverse(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.print("Going reverse");
  delay(2000);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
