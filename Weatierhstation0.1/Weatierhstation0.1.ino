#include <DHT.h>
#include <Adafruit_BMP085.h> // or Adafruit_BMP280.h

#define DHTPIN 3 // Change to the GPIO you connected DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp; // or Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();
  // Read pressure
  float pressure = bmp.readPressure();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  delay(2000); // Delay between reads
}
