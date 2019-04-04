

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

const int pingPin = A0; // Ultrasonic Trigger
const int echoPin = A1; // Ultrasonic Receiver

// REFERENCE SWITCH IS ON LEFT SIDE
#define ForwardTurn 115
#define Forward 105
#define Stop 90
#define Reverse 77
#define ReverseComp 60
#define ReverseTurn 50

int pinLight = 5;

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

  servoRight.write(ReverseComp);
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
  stop();

  pinMode(pinLight, OUTPUT);

  digitalWrite(pinLight, HIGH);

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
  delay(200);
  digitalWrite(pinLight, LOW);
  while (Serial.available() > 0) { //Looking for incoming data
    incoming_state = Serial.read();  //Reading the data
  }
  Serial.println(incoming_state);
  if (incoming_state == 108) {
    turnLeft(30);

  } else if (incoming_state == 114) {
    turnRight(30);

  } else if (incoming_state == 103) {
    forward(0.1);

  } else if (incoming_state == 99) {
    reverse(0.075);
  } else if (incoming_state == 115) {
    digitalWrite(pinLight, HIGH);
    stop();
//  } else if (incoming_state == 110) {
//    stop();
//    stop();
//    forward(0.1);
//    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
//
//    //Check for a wall and turn if too close
//    if (checkWall() < 40) {
//      delay(10);
//      if (checkWall() < 35) {
//        stop();
//        turnRight(80);
//      }
//    }
//
//    if (euler.y() > 1.3) {
//      reverse(0.2);
//      stop();
//      turnRight(80);
//      stop();
//    }
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
