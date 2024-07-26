#include <SoftwareSerial.h>
#include <DHT.h>
#include <TinyGPS++.h>

#define DHTPIN 2        // Pin where the DHT sensor is connected
#define DHTTYPE DHT11   // Type of DHT sensor used (DHT11, DHT21, DHT22)

const int rxPin = 3;   // Connect GPS TX pin to Arduino pin 3
const int txPin = 4;   // Connect GPS RX pin to Arduino pin 4
SoftwareSerial gpsSerial(rxPin, txPin); // Create a software serial port for GPS communication

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor
TinyGPSPlus gps; // Create a TinyGPS++ object

void setup() {
  Serial.begin(9600); // Start serial communication with computer
  gpsSerial.begin(9600); // Start serial communication with GPS module
  dht.begin(); // Start the DHT sensor
}

void loop() {
  // Read data from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read data from GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Get GPS data
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      // Print all data in a single line
      Serial.print(temperature);
      Serial.print(",");
      Serial.print(humidity);
      Serial.print("|");
      Serial.print(latitude); 
      Serial.print("/");
      Serial.println(longitude); 
      delay(1000);
    }
  }
}
