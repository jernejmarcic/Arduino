#include <DHT.h>;
#include <math.h>
// Define the baud rate
const int BAUD_RATE = 9600;
int gasvalue;
int lightvalue;
int seedpacketcalc;
#define gas 0
#define ldr 1
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value



void setup() {
    // Initialize the serial communication with the set baud rate
    Serial.begin(BAUD_RATE);
    dht.begin();
}

void loop() {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    gasvalue = analogRead(gas);
    lightvalue = analogRead(ldr); 
    unsigned long seedpacketcalc = round(abs((long)gasvalue * (long)hum * (long)temp * (long)lightvalue));




 //   Serial.println(hum);
 //   Serial.println(temp);
 //   Serial.println(gasvalue);
 //   Serial.println(lightvalue);
    Serial.println(seedpacketcalc);





    
    delay(1000);  // Wait for a second
}
