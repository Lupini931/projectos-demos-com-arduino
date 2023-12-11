

#include <WiFiManager.h>
#include <ESP8266Firebase.h>

#define FIREBASE_HOST "https://iotestacionamento-default-rtdb.firebaseio.com/"                 
#define FIREBASE_Authorization_key "7hzilXVjpHbc4Uke2WBQicS3tm27GeldVK8WksTs"


 
int sensor1 = 0;    //Contador de vagas no sensor1  
int sensor2 = 0;     //Contador de vagas no sensor2  
FirebaseData firebaseData;
FirebaseJson json;



void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
pinMode(2,OUTPUT);

   


 WiFi.mode(WIFI_STA);                               
   
 Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  WiFiManager wm;

        bool res;
        res = wm.autoConnect("AutoConnectAP");
        if(!res) {
        Serial.println("Failed to connect");
        digitalWrite(2,LOW);
        // ESP.restart();
    }
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
          digitalWrite(2,HIGH);
    }

delay(100);
 
 
  
}

void loop() { 
   //Calcula a quantidade de vagas disponiveis e ocupadas, e imprime no display  

sensor1++;
sensor2++;
  Serial.print("sensor1 = ");  
 Serial.println(sensor1);  
  
 Serial.print("sensor2 ");  
 Serial.println(sensor2);
 
      Firebase.setInt(firebaseData,"sen1", sensor1);
      Firebase.setInt(firebaseData,"sen2", sensor2);

  Serial.println();
delay(500);
 
}
