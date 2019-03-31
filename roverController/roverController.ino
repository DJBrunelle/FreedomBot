

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

const int pingPin = A0; // Ultrasonic Trigger
const int echoPin = A1; // Ultrasonic Receiver

// REFERENCE SWITCH IS ON LEFT SIDE
#define ForwardTurn 120
#define Forward 105
#define Stop 90
#define Reverse 60
#define ReverseTurn 50

Servo servoRight;
Servo servoLeft;

void forward(float distance) {
  int timer = distance * 3250;

  servoRight.write(Forward);
  servoLeft.write(Forward);
  delay(timer);
}

void reverse(float distance) {
  int timer = distance * 3250;

  servoRight.write(Reverse);
  servoLeft.write(Reverse);
  delay(timer);
}

void turnRight(float angleDegrees) {

  int timer = map(angleDegrees, 0, 360, 100, 2000);

  servoRight.write(ForwardTurn);
  servoLeft.write(ReverseTurn);
  delay(timer);
  stop();
}
void turnLeft(float angleDegrees) {

  int timer = map(angleDegrees, 0, 360, 100, 2000);

  servoRight.write(ReverseTurn);
  servoLeft.write(ForwardTurn);
  delay(timer);
  stop();
}

void stop() {
  servoRight.write(Stop);
  servoLeft.write(Stop);
  delay(1000);
}

void setup () {
  Serial.begin(9600);
  servoRight.attach(9);
  servoLeft.attach(11);

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  delay(1000);

  bno.setExtCrystalUse(true);

  //  Start moving forward, with little delay and no stopping
  forward(0.5);
}
void loop() {
  int incoming_state;
  while (Serial.available() > 0) { //Looking for incoming data
    incoming_state = Serial.read();  //Reading the data
  }
  Serial.println(incoming_state);
  if (incoming_state == 108) {
    turnLeft(30);
    delay(1000);
  } else if (incoming_state == 114) {
    turnRight(30);
    delay(1000);
  } else if(incoming_state == 103) {
    forward(1);
    stop();
  }


  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  //Check for a wall and turn if too close
  if (checkWall() < 33) {
    delay(10);
    if (checkWall() < 27) {
      stop();
      delay(100);
      turnRight(80);
      forward(0.1);
    }
  }

  if (euler.y() > 1.3) {
    reverse(0.2);
    stop();
    turnRight(80);
    stop();
    forward(0.1);
  }
}

// Check how close an object is from front of ultrasonic sensor
long checkWall() {
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  return cm;
}

//Conversion analog input from ultrasonic sensor to cm
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
