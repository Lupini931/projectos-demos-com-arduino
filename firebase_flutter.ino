/* 
 https://arduino.esp8266.com/stable/package_esp8266com_index.json
 */

#include <WiFiManager.h> 
#include <FirebaseESP32.h>


#define FIREBASE_HOST "https://iotestacionamento-default-rtdb.firebaseio.com/" //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "7hzilXVjpHbc4Uke2WBQicS3tm27GeldVK8WksTs" //Your Firebase Auth Token

FirebaseData firebaseData;
 bool De1 ;

void setup() {  
 
  Serial.begin(115200);
  
  pinMode(2,OUTPUT);
    pinMode(23,OUTPUT);
  digitalWrite(2, HIGH);
 
 

  WiFiManager wm;
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("LED_IoT 2023"); // password protected ap

   if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
          digitalWrite(2, LOW); 
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
         digitalWrite(2, HIGH);
         delay(1000);
          digitalWrite(2, LOW);
               delay(1000); 
           digitalWrite(2, HIGH);
         delay(1000);
          digitalWrite(0, LOW);
             delay(1000); 
           digitalWrite(2, HIGH); 
    }

  
delay(100);
}

void loop() {




      if (Firebase.getBool(firebaseData, "/BT")) {
   
    
          if (firebaseData.boolData()==true){
              digitalWrite(23,HIGH); //Device1 is ON
              Serial.println("LIGADO");
         
          
          }
          else if (firebaseData.boolData()==false){
              digitalWrite(23,LOW);//Device1 if OFF
                Serial.println("DESLIGADO");
          
            }}
}


   
