#include <SimpleDHT.h>
#include <SoftwareSerial.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;

SoftwareSerial bluetooth(10, 11);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;

  if (dht11.read(pinDHT11, &temperature, &humidity, NULL) == SimpleDHTErrSuccess) {
    Serial.print("Temperature: ");
    Serial.print((int)temperature);
    Serial.print("°C");
    Serial.print(" | ");
    Serial.print("Humidity: ");
    Serial.print((int)humidity);
    Serial.println("%");
//
//    bluetooth.print("Temperature: ");
//    bluetooth.print((int)temperature);
//    bluetooth.print("°C");
//    bluetooth.print(" | ");
//    bluetooth.print("Humidity: ");
//    bluetooth.print((int)humidity);
//    bluetooth.println("%");

  } else {
    Serial.println("Error reading DHT11 sensor");
  }
}
