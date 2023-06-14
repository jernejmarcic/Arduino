// Include the necessary libraries.
// Wire.h is a library that provides functions for communication with I2C devices, which the OLED display uses.
#include <Wire.h>
// Adafruit_GFX.h is a graphics library for displays like the OLED one we're using.
#include <Adafruit_GFX.h>
// Adafruit_SSD1306.h is a library specifically for controlling SSD1306 OLED displays.
#include <Adafruit_SSD1306.h>

// Define constants for the screen width and height, in pixels.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Define the pin that the temperature sensor is connected to. A0 is an analog input pin on the Arduino.
#define SENSOR_PIN A0
// Define the pin that the LED is connected to. 2 is a digital pin on the Arduino.
#define LED_PIN 2

// Create an instance of the Adafruit_SSD1306 class, which we will use to control the OLED display.
// The parameters specify the screen width and height, the I2C interface to use, and the reset pin for the display (which we're not using, so it's -1).
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// This function will convert the resistance value read from the sensor to a temperature.
// It needs to be implemented based on the sensor's datasheet.
// Right now, it just returns the resistance value as a placeholder.
float convertResistanceToTemperature(float resistance) {
  return resistance;
}

// The setup function runs once when the Arduino is powered on or reset.
void setup() {
  // Configure the sensor pin as an input.
  pinMode(SENSOR_PIN, INPUT);
  // Configure the LED pin as an output.
  pinMode(LED_PIN, OUTPUT);

  // Try to initialize the display.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // If the display couldn't be initialized, print an error message and stop the program.
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Clear the display.
  display.clearDisplay();
}

// The loop function runs over and over again as long as the Arduino is powered on.
void loop() {
  // Read the value from the sensor pin.
  int sensorValue = analogRead(SENSOR_PIN);
  // Convert the sensor reading to a resistance value.
  float resistance = sensorValue * PUT THE VLAUE FROM UR CODE HERE;
  // Convert the resistance to a temperature.
  float temperature = convertResistanceToTemperature(resistance);

  // Clear the display.
  display.clearDisplay();
  // Set the text size to 1 (normal size).
  display.setTextSize(1);
  // Set the text color to white.
  display.setTextColor(WHITE);
  // Set the cursor to the top-left corner of the display.
  display.setCursor(0, 0);
  // Print the string "Temperature: " to the display.
  display.println(F("Temperature: "));
  // Print the temperature value to the display.
  display.println(temperature);
  // Send the buffer to the display, causing it to update with the text we've written.
  display.display();

  // If the temperature is above 24 degrees, turn the LED on.
  if(temperature > 24.0) {
    digitalWrite(LED_PIN, HIGH);
  } 
  // If the temperature is 24 degrees or below, turn the LED off.
  else {
    digitalWrite(LED_PIN, LOW);
  }
  // Wait for 1 second (1000 milliseconds) before the next loop iteration.
  // This delay allows the LED to remain in its current state (on or off) for a noticeable amount of time.
  // Without this delay, the LED would flicker too fast for us to see clearly.
  delay(1000);
}
