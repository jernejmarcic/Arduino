#include <ESP8266WiFi.h>
#include <Wire.h>

#define MQ9_ANALOG_PIN A0

float Ro = 9.83; // MQ-9 resistance in clear air for methane
float a = 27.038; // factor for methane
float b = -3.21; // exponent for methane

void setup() {
  Serial.begin(9600);
}

void loop() {
  float Rs = analogRead(MQ9_ANALOG_PIN);
  float ratio = Rs / Ro;
  float ppm = a * pow(ratio, b);

  Serial.print("Methane concentration: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  
  delay(1000);
}
