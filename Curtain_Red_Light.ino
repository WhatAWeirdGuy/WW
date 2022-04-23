//must install movingAvg library

#include <movingAvg.h>
int distanceSensorPin = A1;
int ledIndicator = 3; 
movingAvg distanceSensor(50);

void setup() {
  pinMode(distanceSensorPin, INPUT);
  pinMode(ledIndicator, OUTPUT);
  distanceSensor.begin();
  Serial.begin(9600);
}

void loop() {
  int ds = analogRead(distanceSensorPin);
  int avg = distanceSensor.reading(ds);
  
  
  if (avg < 140) {
        digitalWrite(ledIndicator, HIGH); // Connects ground to motor module
        Serial.println(avg);
    }
  
  else {
      digitalWrite(ledIndicator, LOW);
      Serial.println(avg);
      }
}
