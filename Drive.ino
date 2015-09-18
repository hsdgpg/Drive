#include <PciManager.h>
#include <Sonar.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

const int START_SONAR_PIN = 7;
const int LEFT_SONAR_PIN = 2;
const int CENTER_SONAR_PIN = 3;
const int RIGHT_SONAR_PIN = 4;
const int SERVO_PIN = 10;

const int SPEED = 80;

const int MIN_SIDE_DISTANCE = 36;  // inches
const int MIN_CENTER_DISTANCE = 10;
const int SERVO_CENTER = 1500; // microseconds
const int SERVO_MIN = 1100;
const int SERVO_MAX = 1900;
const int SERVO_GAIN = 30; // microseconds/inch

Sonar leftSonar(LEFT_SONAR_PIN);
Sonar centerSonar(CENTER_SONAR_PIN);
Sonar rightSonar(RIGHT_SONAR_PIN);

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1);


Servo servo;

void setup() {
    Serial.begin(115200);
    startSonar(START_SONAR_PIN);
    servo.attach(SERVO_PIN);
    
    AFMS.begin(); 
    motor->setSpeed(SPEED);
    motor->run(FORWARD);
    
    Serial.println("Ready");
}

void printDistances(int left, int center, int right) {
  Serial.print("Left: ");
  Serial.print(left);

  Serial.print("  Center: ");
  Serial.print(center);

  Serial.print("  Right: ");
  Serial.print(right);
  Serial.println();
}

void k_turn(int left, int center, int right) {
  if (left > right) {
    servo.writeMicroseconds(SERVO_MAX);
  } else {
    servo.writeMicroseconds(SERVO_MIN);
  }
  
  delay(250);
  motor->run(BACKWARD);
  delay(2000);
  
  motor->setSpeed(0);
  servo.writeMicroseconds(SERVO_CENTER);
  delay(200);
  
  motor->run(FORWARD);
  motor->setSpeed(SPEED);
}
  

void loop() {
  int servo_ms;
  
  int left = leftSonar.inches();
  int center = centerSonar.inches();
  int right = rightSonar.inches();
  printDistances(left, center, right);
  
  if (center < MIN_CENTER_DISTANCE) {
    k_turn(left, center, right);
  }
  
  if (left < MIN_SIDE_DISTANCE || right < MIN_SIDE_DISTANCE) {
    servo_ms = SERVO_CENTER - SERVO_GAIN * (left - right);
    if (servo_ms < SERVO_MIN) {
      servo_ms = SERVO_MIN;
    } else if (servo_ms > SERVO_MAX) {
      servo_ms = SERVO_MAX;
    }
  } else {
    servo_ms = SERVO_CENTER;
  }
  
  Serial.print("servo_ms: ");
  Serial.println(servo_ms);
  
  servo.writeMicroseconds(servo_ms);
}
