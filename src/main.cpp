#include <Arduino.h>

// Define the trig and echo pin
#define TRIG_PIN 22
#define ECHO_PIN 19

// Define the R, Y, G Traffic Light Pins
#define RED_PIN 4
#define YELLOW_PIN 16
#define GREEN_PIN 17

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

// Function to control traffic lights based on distance
void controlTrafficLight(float distance) {
  // Turn off all lights first
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  
  if (distance > 0 && distance <= 20) {
    // Too close - RED light
    digitalWrite(RED_PIN, HIGH);
    Serial.println(" [RED LIGHT - TOO CLOSE!]");
  } else if (distance > 20 && distance <= 50) {
    // Medium distance - YELLOW light
    digitalWrite(YELLOW_PIN, HIGH);
    Serial.println(" [YELLOW LIGHT - CAUTION]");
  } else if (distance > 50 && distance <= 200) {
    // Safe distance - GREEN light
    digitalWrite(GREEN_PIN, HIGH);
    Serial.println(" [GREEN LIGHT - SAFE DISTANCE]");
  } else {
    // Out of range - all lights off
    Serial.println(" [OUT OF RANGE - NO LIGHTS]");
  }
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Configure ultrasonic sensor pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Configure traffic light pin modes
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  // Initialize all lights to OFF
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  
  // Wait for serial monitor to connect
  delay(2000);
  
  Serial.println("===========================================");
  Serial.println("  HC-SR04 Ultrasonic Sensor + Traffic Light");
  Serial.println("              ESP32 Control");
  Serial.println("===========================================");
  Serial.print("TRIG Pin: ");
  Serial.println(TRIG_PIN);
  Serial.print("ECHO Pin: ");
  Serial.println(ECHO_PIN);
  Serial.print("RED Pin: ");
  Serial.println(RED_PIN);
  Serial.print("YELLOW Pin: ");
  Serial.println(YELLOW_PIN);
  Serial.print("GREEN Pin: ");
  Serial.println(GREEN_PIN);
  Serial.println("===========================================");
  Serial.println("Distance Ranges:");
  Serial.println("  0-20 cm   : RED (Too Close!)");
  Serial.println("  21-50 cm  : YELLOW (Caution)");
  Serial.println("  51-200 cm : GREEN (Safe Distance)");
  Serial.println("  >200 cm   : No Light (Out of Range)");
  Serial.println("===========================================");
  Serial.println();
}

void loop() {
  // Read distance from sensor
  float distance = readDistance();
  
  // Log the measurement with clear formatting
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  // Control traffic lights based on distance
  controlTrafficLight(distance);
  
  // Wait 500ms before next measurement
  delay(500);
}