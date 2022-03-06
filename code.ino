#include <SoftwareSerial.h>
#include "NewPing.h"

// VARIABLES AND PINS DEFENITION
const int IN1 = 2; //MSB for motor 0
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5; // MSB for motor 1
const int ENA = 10; // motor 0 enable
const int ENB = 11; // motor 1 enable
const int wall_threshold = 24; // maximum distance to read if there is a wall

// Boolean values to read walls
boolean frontwall ;
boolean leftwall ;
boolean rightwall ;

// Values to store sensor reading
float leftSensor, rightSensor, frontSensor;

// analog values for motors enable
int RMS = 200;
int LMS = 200;

// Sensors triggers and echos defenition
int trigger_front = A1;
int echo_front = A4;

int trigger_left = A3;
int echo_left = A0;

int trigger_right = A5;
int echo_right = A2;


// SETUP FUNCTION
void setup() {
  Serial.begin(9600);
  //set H-Bridge pin as output
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

  //set trigger as output and echo as input in each sensor
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);

  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);

  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);

}

// MAIN LOOP
void loop() {

  //check where there is a wall around the robot
  frontwall = wallFront();
  leftwall = wallLeft();
  rightwall = wallRight();

  Serial.print("front wall : ");
  Serial.println(frontwall);
  Serial.print("left wall : ");
  Serial.println(leftwall);
  Serial.print("right wall : ");
  Serial.println(rightwall);

  if (frontwall && leftwall && rightwall)
  {
    reverse(100);
    return;
  }

  if (!leftwall) // no left walll
  {
    left(300);
    delay(1000);
    //Center();
    forward(400);
    //Center();
  }
  else if (leftwall && !frontwall) // wall left and no front wall
  {
    // move forward
    forward(400);
    // Center();
  }
  else // wall left and wall front , no wall right
  {
    right(300);
    //Center();
  }
  delay(500);
}

// MOVEMENT FUNCTIONS
void reverse(int amountOfDelay)
{
  // right and left motor will go reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.print("Going reverse");
  delay(amountOfDelay);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void forward(int amountOfDelay)
{
  // right and left motors will go forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going forward");
  delay(amountOfDelay);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

}

void right(int amountOfDelay)
{
  //right motor will go reverse, left motor runs forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going right");
  delay(amountOfDelay);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void left(int amountOfDelay)
{
  //right motor will go forward, left motor runs in reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, LMS);
  analogWrite(ENB, RMS);
  Serial.println("Going left");
  delay(amountOfDelay);
  // Stop when done
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(300);
}


// WALL CHECKING FUNCTIONS
boolean wallLeft()
{
  long duration, distance;
  digitalWrite(trigger_left, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  duration = pulseIn(echo_left, HIGH);
  distance = (duration / 2) / 29.1; 
  Serial.print("LEFT SENSOR = ");
  Serial.println(distance);

  if (distance <= wall_threshold) 
  {  
    leftSensor = distance;
    return true;
  }
  return false;
}

boolean wallFront()
{
  long duration, distance;
  digitalWrite(trigger_front, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigger_front, LOW);
  duration = pulseIn(echo_front, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("FRONT SENSOR = ");
  Serial.println(distance);
  if (distance <= wall_threshold) 
  { 
    frontSensor = distance;
    return true;
  }
  return false;
}

boolean wallRight()
{
  long duration, distance;
  digitalWrite(trigger_right, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigger_right, LOW);
  duration = pulseIn(echo_right, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("RIGHT SENSOR = ");
  Serial.println(distance);
  if (distance <= wall_threshold) 
  {  
    rightSensor = distance;
    return true;
  }
  return false;
}


void Center()
{
  // CHECK LEFT WALL AND RIGHT WALL
  boolean left1 = wallLeft();
  boolean right1 = wallRight();

  // THERE IS RIGHT WALL AND LEFT WALL
  if (left1 && right1)
  {
    // CHECK SENSORS READING DISTANCE
    // IF LEFT DISTANCE > RIGHT
    if (leftSensor > rightSensor)
    {
      Serial.println("left is more than right");
      // CALCULATE THE DIFFERENCE 
      int d = (int)(leftSensor - rightSensor);
      // GO LEFT BY THE AMOUNT OF DIFFERENCE
      left(d);
    }
    
    // IF LEFT DISTANCE > RIGHT
    else if (rightSensor > leftSensor)
    {
      Serial.println("right is more than left");
      int d = (int)(rightSensor - leftSensor);
      right(d);
    }

  }
  // THERE IS LEFT WALL AND NO RIGHT WALL
  else if (left1 && !right1)
  {
    if (leftSensor > 5) // 5 IS CONSIDERED AS THE DISTANCE VALUE WHEN THE ROBOT IS CENTERED
    {
      Serial.println("left wall only");
      int d = (int)(leftSensor - 5);
      right(d);
    }
  }
  // THERE IS RIHGT WALL AND NO LEFT WALL
  else if (right1 && !left1)
  {
    if (rightSensor > 5)
    {
      Serial.println("right wall only");
      int d = (int)(rightSensor - 5);
      left(d);
    }
  }
  else {
    Serial.println("No Wall");
  }
}
