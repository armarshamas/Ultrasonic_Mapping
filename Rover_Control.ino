#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 100
#define MAX_SPEED 150

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motorFrontRight(1, MOTOR12_1KHZ);
AF_DCMotor motorFrontLeft(2, MOTOR12_1KHZ);
AF_DCMotor motorRearRight(3, MOTOR34_1KHZ);
AF_DCMotor motorRearLeft(4, MOTOR34_1KHZ);
Servo myservo;

boolean isMovingForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  myservo.attach(10);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(40);

  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceRight = lookRight();
    delay(200);
    distanceLeft = lookLeft();
    delay(200);

    if (distanceRight >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft() {
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motorFrontRight.run(RELEASE);
  motorFrontLeft.run(RELEASE);
  motorRearRight.run(RELEASE);
  motorRearLeft.run(RELEASE);
}

void moveForward() {
  if (!isMovingForward) {
    isMovingForward = true;
    motorFrontRight.run(FORWARD);
    motorFrontLeft.run(FORWARD);
    motorRearRight.run(FORWARD);
    motorRearLeft.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motorFrontRight.setSpeed(speedSet);
      motorFrontLeft.setSpeed(speedSet);
      motorRearRight.setSpeed(speedSet);
      motorRearLeft.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  isMovingForward = false;
  motorFrontRight.run(BACKWARD);
  motorFrontLeft.run(BACKWARD);
  motorRearRight.run(BACKWARD);
  motorRearLeft.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motorFrontRight.setSpeed(speedSet);
    motorFrontLeft.setSpeed(speedSet);
    motorRearRight.setSpeed(speedSet);
    motorRearLeft.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motorFrontRight.run(FORWARD);
  motorFrontLeft.run(FORWARD);
  motorRearRight.run(BACKWARD);
  motorRearLeft.run(BACKWARD);
  delay(500);
  motorFrontRight.run(FORWARD);
  motorFrontLeft.run(FORWARD);
  motorRearRight.run(FORWARD);
  motorRearLeft.run(FORWARD);
}

void turnLeft() {
  motorFrontRight.run(BACKWARD);
  motorFrontLeft.run(BACKWARD);
  motorRearRight.run(FORWARD);
  motorRearLeft.run(FORWARD);
  delay(500);
  motorFrontRight.run(FORWARD);
  motorFrontLeft.run(FORWARD);
  motorRearRight.run(FORWARD);
  motorRearLeft.run(FORWARD);
}
