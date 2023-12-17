
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MQ9_ANALOG_PIN A0
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float Ro = 9.83; // MQ-9 resistance in clear air for methane
float a = 27.038; // factor for methane
float b = -3.21; // exponent for methane

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Methane Sensor");
  display.display();
}

void loop() {
  float Rs = analogRead(MQ9_ANALOG_PIN);
  float ratio = Rs / Ro;
  float ppm = a * pow(ratio, b);



  Serial.print("Methane concentration: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Methane Concentration");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(ppm);
  display.println(" ppm");
  display.display();

  delay(1000);
}
