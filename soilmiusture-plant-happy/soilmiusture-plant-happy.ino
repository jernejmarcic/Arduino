// Include necessary libraries
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>

// Define OLED reset pin
#define OLED_RESET 4
// Create display object
Adafruit_SSD1306 display(OLED_RESET);

// Create RTC object
RTC_DS3231 rtc;

// Define button pins
const int buttonHour = 3;
const int buttonMinute = 4;
const int buttonSecond = 5;
// Define buzzer pin
const int buzzerPin = 2;

// Define the initial state for each button
bool lastButtonHourState = LOW;
bool lastButtonMinuteState = LOW;
bool lastButtonSecondState = LOW;

// Define debounce delay in milliseconds
const int debounceDelay = 50;

// Define alarm time variable
DateTime alarmTime;

// Setup function runs once when you press reset or power the board
void setup() {
  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Initialize RTC
  if (!rtc.begin()) {
    display.println("Couldn't find RTC"); // Print error message if RTC not found
    while (1); // Stop execution
  }
  if (rtc.lostPower()) {
    display.println("RTC lost power, lets set the time!"); // Print message if RTC lost power
    // Set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Set the button pins as input
  pinMode(buttonHour, INPUT);
  pinMode(buttonMinute, INPUT);
  pinMode(buttonSecond, INPUT);

  // Set the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Set the initial alarm time to the current time
  alarmTime = rtc.now();
}

// Loop function runs over and over again forever
void loop() {
  DateTime now = rtc.now(); // Get the current time from RTC
  
  // Check the state of the hour button
  bool buttonHourState = digitalRead(buttonHour);
  // If the button is pressed (HIGH) and it was not pressed in the last iteration (LOW),
  // increment the hour value of the alarm time
  if (buttonHourState == HIGH && lastButtonHourState == LOW) {
    delay(debounceDelay); // Debounce delay
    // Check the button state again after the debounce delay
    if (digitalRead(buttonHour) == HIGH) {
      alarmTime = alarmTime + TimeSpan(0,1,0,0); // Increase the hour by 1
    }
  }
  lastButtonHourState = buttonHourState; // Update the last button state
  
  // Repeat the above process for minute and second buttons
  bool buttonMinuteState = digitalRead(buttonMinute);
  if (buttonMinuteState == HIGH && lastButtonMinuteState == LOW) {
    delay(debounceDelay);
    if (digitalRead(buttonMinute) == HIGH) {
      alarmTime = alarmTime + TimeSpan(0,0,1,0); // Increase the minute by 1
    }
  }
  lastButtonMinuteState = buttonMinuteState;

  bool buttonSecondState = digitalRead(buttonSecond);
  if (buttonSecondState == HIGH && lastButtonSecondState == LOW) {
    delay(debounceDelay);
    if (digitalRead(buttonSecond) == HIGH) {
      alarmTime = alarmTime + TimeSpan(0,0,0,1); // Increase the second by 1
    }
  }
  lastButtonSecondState = buttonSecondquote("lastButtonSecondState = buttonSecondState;")
display.clearDisplay();,the buzzer)
}
  lastButtonSecondState = buttonSecondState;

  // Clear the display
  display.clearDisplay();
  // Set the text size
  display.setTextSize(1);
  // Set the text color
  display.setTextColor(WHITE);
  // Set the cursor to top left corner
  display.setCursor(0,0);

  // Print the current time text and values
  display.println("Current time: ");
  display.setCursor(0,16);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.println(now.second(), DEC);

  // Print the alarm time text and values
  display.println("Alarm time: ");
  display.setCursor(0,32);
  display.print(alarmTime.hour(), DEC);
  display.print(':');
  display.print(alarmTime.minute(), DEC);
  display.print(':');
  display.println(alarmTime.second(), DEC);

  // Update the display with the above settings and text
  display.display();

  // If the current time is equal to or later than the alarm time, turn on the buzzer
  if (now.unixtime() >= alarmTime.unixtime()) {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    delay(500); // Wait for 500 milliseconds
    digitalWrite(buzzerPin, LOW); // Then turn off the buzzer
  }
}

