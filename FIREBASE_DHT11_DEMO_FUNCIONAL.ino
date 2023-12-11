
#include <WiFiManager.h>
#include <ESP32Firebase.h>
#include "DHT.h"

#define DHTPIN 19  

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define REFERENCE_URL "https://iotirrigacao-default-rtdb.firebaseio.com/"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);

void setup() {
  Serial.begin(9600);
  pinMode(18,OUTPUT);

   
  pinMode(2,OUTPUT);


   dht.begin(); 
 WiFiManager wm;

        bool res;
        res = wm.autoConnect("AutoConnectAP");
        if(!res) {
        Serial.println("Failed to connect");
        digitalWrite(15,LOW);
        // ESP.restart();
    }
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
          digitalWrite(15,HIGH);
    }


}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
 
  Serial.print("Humidity: ");  
  Serial.print(h);
  
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
  
  firebase.setFloat ("Temp",t);
 
  firebase.setFloat ("Humidity",h);
 int command = firebase.getInt("solo"); // Get data from database.

  if(command == 0){ //  STOP
    digitalWrite(2, LOW);
  
  }
    if(command == 1){ //  STOP
    digitalWrite(2, HIGH);
  
  }
   
  
  delay(3000);
}
