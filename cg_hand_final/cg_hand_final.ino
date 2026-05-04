#include <Servo.h>

// Finger servos
Servo thumb;
Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo pinkyFinger;

// pins
const int trigPin = 12;
const int echoPin = 11;

// Default distance from webpage slider
int thresholdDistance = 120;

// Current sensor distance
int distance = 0;

void setup() {
  Serial.begin(115200);

  // Servo pins
  thumb.attach(3);
  indexFinger.attach(5);
  middleFinger.attach(6);
  ringFinger.attach(9);
  pinkyFinger.attach(10);

  // Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  closeHand();
}

void loop() {
  // Read distance update from slider
  if (Serial.available() > 0) {
  String data = Serial.readStringUntil('\n');
  data.trim();

  if (data.startsWith("DIST:")) {
    thresholdDistance = data.substring(5).toInt();

    Serial.print("UPDATED THRESHOLD: ");
    Serial.println(thresholdDistance);
  }
}

  // Read ultrasonic sensor
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Threshold: ");
  Serial.print(thresholdDistance);
  Serial.println(" cm");

  // Open hand when person is close
  if (distance > 0 && distance <= thresholdDistance) {
    openHand();
  } else {
    closeHand();
  }

  delay(200);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  int cm = duration * 0.034 / 2;
  return cm;
}

void openHand() {
  thumb.write(20);
  indexFinger.write(120);
  middleFinger.write(120);
  ringFinger.write(120);
  pinkyFinger.write(120);
}

void closeHand() {
  thumb.write(20);
  indexFinger.write(20);
  middleFinger.write(20);
  ringFinger.write(20);
  pinkyFinger.write(20);
}