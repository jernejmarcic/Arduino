#include <Wire.h> // Include Wire library for I2C communication
#include <RTClib.h> // Include Real Time Clock library
#include <Adafruit_GFX.h> // Include Adafruit Graphics library for OLED
#include <Adafruit_SSD1306.h> // Include Adafruit SSD1306 library for OLED
#include <Bounce2.h> // Include Bounce2 library for debouncing buttons

// Define OLED display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Notes


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create an RTC object
RTC_DS1307 rtc;

// Define the alarm time
DateTime alarmTime;

// Define the buzzer pin
const int buzzer = 2;

// Define the button pins
const int hourButton = 3;
const int minuteButton = 4;
const int secondButton = 5;
const int buzzerOffButton = 7; 

// Create Bounce objects for each button
Bounce debouncerHour = Bounce(); 
Bounce debouncerMinute = Bounce(); 
Bounce debouncerSecond = Bounce(); 
Bounce debouncerBuzzerOff = Bounce(); 

// Add a flag to indicate whether the alarm is active
bool alarmActive = false;

void setup() {
  Serial.begin(9600); // Initialize serial
  pinMode(buzzer, OUTPUT); // Set buzzer as output

  // Setup the buttons with internal pull-up resistors and attach the debouncers
  pinMode(hourButton, INPUT_PULLUP);
  debouncerHour.attach(hourButton);
  debouncerHour.interval(5); // interval in ms
  
  pinMode(minuteButton, INPUT_PULLUP);
  debouncerMinute.attach(minuteButton);
  debouncerMinute.interval(5); // interval in ms
  
  pinMode(secondButton, INPUT_PULLUP);
  debouncerSecond.attach(secondButton);
  debouncerSecond.interval(5); // interval in ms

  // Setup the buzzer off button with internal pull-up resistor and attach the debouncer
  pinMode(buzzerOffButton, INPUT_PULLUP);
  debouncerBuzzerOff.attach(buzzerOffButton);
  debouncerBuzzerOff.interval(5); // interval in ms

  // Initialize display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(WHITE); 
  display.setCursor(0,0); 

  if (! rtc.begin()) { // Initialize RTC
    display.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) { // Check to see if the RTC is running
    display.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the RTC to the date & time this sketch was compiled
  }

  alarmTime = rtc.now(); // Initialize alarm time to current time
}

void loop() {
  DateTime now = rtc.now(); // Get the current date and time

  debouncerHour.update(); // Update the debouncer state for the hour button
  if (debouncerHour.fell()) { // If the hour button was pressed
    alarmTime = alarmTime + TimeSpan(0,1,0,0); // Increase the alarm hour by one
  }

  debouncerMinute.update(); // Update the debouncer state for the minute button
  if (debouncerMinute.fell()) { //Apologies for the cutoff, here is the remaining part of the code:

    // If the minute button was pressed
    alarmTime = alarmTime + TimeSpan(0,0,1,0); // Increase the alarm minute by one
  }

  debouncerSecond.update(); // Update the debouncer state for the second button
  if (debouncerSecond.fell()) { // If the second button was pressed
    alarmTime = alarmTime + TimeSpan(0,0,0,1); // Increase the alarm second by one
  }

  // If current time matches alarm time, activate the alarm
  if (now.hour() == alarmTime.hour() && now.minute() == alarmTime.minute() && now.second() == alarmTime.second()) {
    alarmActive = true;
  }

  // Update the debouncer state for the buzzer off button
  debouncerBuzzerOff.update(); 
   // If the buzzer off button was pressed
  if (debouncerBuzzerOff.fell()) { 
    alarmActive = false; // Deactivate the alarm
  }

 



  // If the alarm is active, turn on the buzzer. Otherwise, turn it off.
  digitalWrite(buzzer, alarmActive ? HIGH : LOW);

  // Display the current time and alarm time on the OLED
  display.clearDisplay(); // Clear the display
  display.setCursor(0,0); // Set the cursor to the top-left corner
  display.print("Current t.: ");
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.println(now.second(), DEC);
  
  display.print("Alarm time: ");
  display.print(alarmTime.hour(), DEC);
  display.print(':');
  display.print(alarmTime.minute(), DEC);
  display.print(':');
  display.println(alarmTime.second(), DEC);

  display.display(); // Update the display with all of the above graphics
}
