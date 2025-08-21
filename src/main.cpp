#include <Arduino.h>

// Define the trig and echo pin
#define TRIG_PIN 22
#define ECHO_PIN 19

// Function to read distance from HC-SR04
float readDistance() {
  // Clear the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send a 10us pulse to TRIG_PIN
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the ECHO_PIN, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance in centimeters
  // Speed of sound is approximately 343 m/s or 0.0343 cm/μs
  // Distance = (duration * 0.0343) / 2 (divide by 2 because sound travels to object and back)
  float distance = (duration * 0.0343) / 2;
  
  return distance;
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Configure pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Wait for serial monitor to connect
  delay(2000);
  
  Serial.println("=================================");
  Serial.println("   HC-SR04 Ultrasonic Sensor");
  Serial.println("         ESP32 Test");
  Serial.println("=================================");
  Serial.print("TRIG Pin: ");
  Serial.println(TRIG_PIN);
  Serial.print("ECHO Pin: ");
  Serial.println(ECHO_PIN);
  Serial.println("=================================");
  Serial.println();
}

void loop() {
  // Read distance from sensor
  float distance = readDistance();
  
  // Log the measurement with clear formatting
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  // Add status messages for different distance ranges
  if (distance > 400 || distance <= 0) {
    Serial.println(" [OUT OF RANGE]");
  } else if (distance <= 5) {
    Serial.println(" [VERY CLOSE]");
  } else if (distance <= 20) {
    Serial.println(" [CLOSE]");
  } else if (distance <= 100) {
    Serial.println(" [MEDIUM]");
  } else {
    Serial.println(" [FAR]");
  }
  
  // Wait 500ms before next measurement
  delay(500);
}