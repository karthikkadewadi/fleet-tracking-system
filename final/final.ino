#include <NeoSWSerial.h>
#include <TinyGPS++.h>

const int rxPin = 3; // Connect GPS TX pin to Arduino pin 3
const int txPin = 4; // Connect GPS RX pin to Arduino pin 4
NeoSWSerial gpsSerial(rxPin, txPin); // Create a software serial port for GPS communication

//NeoSWSerial bluetooth(10, 11); // RX, TX for Bluetooth

TinyGPSPlus gps; // Create a TinyGPS++ object

void setup() {
  Serial.begin(9600); // Start serial communication with computer
  gpsSerial.begin(9600); // Start serial communication with GPS module
//  bluetooth.begin(9600); // Start serial communication with Bluetooth
  Serial.println("GPS Module Test");
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) { // Feed GPS data to TinyGPS++
      if (gps.location.isValid()) { // Check if GPS data is valid
        // Construct a single string containing latitude and longitude


        // Print latitude and longitude to Serial Monitor
        Serial.println(gps.location.lat());

        // Send latitude and longitude over Bluetooth via software serial
     //   bluetooth.println(gpsData);
      }
    }
  }
  delay(1000);
}
