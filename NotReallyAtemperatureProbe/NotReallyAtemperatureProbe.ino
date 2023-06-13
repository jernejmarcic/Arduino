#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SENSOR_PIN A0 // connect the sensor to analog pin A0
#define LED_PIN 2 // connect the LED to digital pin 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float convertResistanceToTemperature(float resistance) {
  // This function should be implemented based on the sensor's datasheet
  // For now, we will simply return the resistance as a placeholder
  return resistance;
}

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  float resistance = sensorValue * (5.0 / 1023.0); // convert to resistance
  float temperature = convertResistanceToTemperature(resistance); // convert resistance to temperature

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Temperature: "));
  display.println(temperature, "C");
  display.display();

  if(temperature > 24.0) { // change the threshold as needed
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(1000);
}
