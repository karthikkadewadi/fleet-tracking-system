#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

String URL="http://api.thingspeak.com/update?api_key=BT8Q26D2XIZXJJH3&field1=";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.disconnect();
  delay(2000);
  Serial.print("Start connection");
  WiFi.begin("motog32","Karthik@904");
  while((!(WiFi.status()== WL_CONNECTED))){
      delay(200);
      Serial.print("..");
    }
  Serial.println("Connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
      String dataa = Serial.readStringUntil('\n');
      Serial.println(dataa);
      int comma = dataa.indexOf(',');
      int a = dataa.indexOf('|');
      int b = dataa.indexOf('/');
      if(comma != -1 && a!=-1 && b!=-1){
          float t = dataa.substring(0,comma).toFloat();
          float h = dataa.substring(comma+1,a).toFloat();
          float latitude = dataa.substring(a+1,b).toFloat();
          float longitude = dataa.substring(b+1).toFloat();
          Serial.print(t);
          Serial.print(h);
          Serial.print(latitude);
          Serial.println(longitude);
          sendData(t,h,latitude,longitude);
        }
      
    }
}


void sendData(float t,float h,float latitude,float longitude){
  WiFiClient client;
  HTTPClient http;
  String newUrl = URL + String(t)+"&field2="+String(h)+"&field3="+String(latitude)+"&field4="+String(longitude);
  http.begin(client,newUrl);
  int responsecode = http.GET();
  String data = http.getString();
  Serial.println(data);
  http.end();
  }
