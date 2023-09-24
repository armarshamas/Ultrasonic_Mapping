#include <Servo.h>

#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7
#define trigPinRadar 10
#define echoPinRadar 11

Servo servo;
int servoPin = 12;
int servoAngle = 0;
int servoIncrement = 1;
bool increasing = true;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPinRadar, OUTPUT);
  pinMode(echoPinRadar, INPUT);
  
  servo.attach(servoPin);
  servo.write(servoAngle);
}

void loop() {
  long duration1, duration2, duration3, durationRadar;
  int distance1, distance2, distance3, distanceRadar;
  
  // Rotate the servo smoothly from 0 to 180 degrees and then back to 0
  if (increasing) {
    servoAngle += servoIncrement;
    if (servoAngle >= 180) {
      servoAngle = 180;
      increasing = false;
    }
  } else {
    servoAngle -= servoIncrement;
    if (servoAngle <= 0) {
      servoAngle = 0;
      increasing = true;
    }
  }
  servo.write(servoAngle);
  delay(15);
  
  // Measure distance for Sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  
  // Measure distance for Sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  
  // Measure distance for Sensor 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;
  
  // Measure distance for radar visualization
  digitalWrite(trigPinRadar, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRadar, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRadar, LOW);
  durationRadar = pulseIn(echoPinRadar, HIGH);
  distanceRadar = durationRadar * 0.034 / 2;
  
  // Send the distance values to the computer
  Serial.print(distance1);
  Serial.print(",");
  Serial.print(distance2);
  Serial.print(",");
  Serial.print(distance3);
  Serial.print(",");
  Serial.print(distanceRadar);
  Serial.print(",");
  Serial.println(servoAngle);
  
  delay(100);
}
