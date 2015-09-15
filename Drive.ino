#include <Sonar.h>

const int MICROSECONDS_PER_INCH = 147;
const double MICROSECONDS_PER_FOOT = MICROSECONDS_PER_INCH * 12.0;


const int START_SONAR_PIN = 7;
const int LEFT_SONAR_PIN = 2;
const int CENTER_SONAR_PIN = 3;
const int RIGHT_SONAR_PIN = 4;

Sonar leftSonar(LEFT_SONAR_PIN);
Sonar centerSonar(CENTER_SONAR_PIN);
Sonar rightSonar(RIGHT_SONAR_PIN);


void setup() {
    Serial.begin(115200);
    startSonar(START_SONAR_PIN);
    Serial.println("Ready");
}

void loop() {
  Serial.print("Left: ");
  Serial.print(leftSonar.inches());

  Serial.print("  Center: ");
  Serial.print(centerSonar.inches());

  Serial.print("  Right: ");
  Serial.print(rightSonar.inches());
  Serial.println();

  delay(200);
}
