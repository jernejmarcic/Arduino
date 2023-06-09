#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SOIL_MOISTURE_SENSOR_PIN A0
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int dryValue; // Sensor reading in dry soil
int wetValue; // Sensor reading in water

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Check if EEPROM has been initialized
  if (EEPROM.read(0) == '#') {
    // Load calibration values from EEPROM
    EEPROM.get(1, dryValue);
    EEPROM.get(1 + sizeof(dryValue), wetValue);
  } else {
    // Perform calibration
    Serial.println("Please place the sensor in dry soil...");
    delay(5000); // Wait 5 seconds
    dryValue = analogRead(SOIL_MOISTURE_SENSOR_PIN);

    Serial.println("Please place the sensor in water...");
    delay(5000); // Wait 5 seconds
    wetValue = analogRead(SOIL_MOISTURE_SENSOR_PIN);

    // Save calibration values to EEPROM
    EEPROM.write(0, '#');
    EEPROM.put(1, dryValue);
    EEPROM.put(1 + sizeof(dryValue), wetValue);
  }
}

void loop() {
  int sensorValue = analogRead(SOIL_MOISTURE_SENSOR_PIN);
  int soilMoisture = map(sensorValue, dryValue, wetValue, 0, 100);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Soil Moisture:");
  display.println(soilMoisture);
  display.println("%");
  display.display();

  delay(1000); // Wait 1 second between readings
}
