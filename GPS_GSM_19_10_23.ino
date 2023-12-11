
//lupini david +244931997478
//Actualizado 11/10/2022
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#include <NewPing.h>
#include <Servo.h>

static const int servoPin = 9;
LiquidCrystal_I2C lcd(0x27,20,4);
Servo servo1;

bool estado =false;
int pos = 0;    // variable to store the servo position
int ledverde = 12;//verde
int ledvermelho = 11; //vermelho
int ledamarelo = 13;//amarelo
int rele = A3;//RELE
int nivel2=0;

#define TRIGGER_PIN1 2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1    3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE1 18 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // NewPing setup of pins and maximum distance.

void sensor1();
void sensor2();

#define TRIGGER_PIN2 4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2    5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE2 40 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2); // NewPing setup of pins and maximum distance.


int x=0;

SoftwareSerial serialGSM(7,8); // RX, TX
SoftwareSerial serialGPS(10,6);

TinyGPS gps;

void leGPS();

int ledgps =A3;

String number = "+244924887649"; // +880 is the country code

void setup() {
 lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  serialGPS.begin(9600);   
  serialGSM.begin(9600); 
    servo1.attach(servoPin);

  Serial.println("Sketch Iniciado!");
pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledamarelo, OUTPUT);
  

  digitalWrite(ledverde, HIGH);
  digitalWrite(ledvermelho,HIGH);
  digitalWrite(ledamarelo, HIGH);


  leGPS();
}

void loop() {

      
  digitalWrite(ledverde, HIGH);
  digitalWrite(ledvermelho,HIGH);
  digitalWrite(ledamarelo, HIGH);
  
  Serial.print("Sensor1: ");
  Serial.print(sonar1.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

    
      
       digitalWrite(ledverde, LOW);
      digitalWrite(ledvermelho, HIGH);
      digitalWrite(ledamarelo, LOW);
      
    
     Serial.print("CONTENTOR VAZIO");
   
     Serial.println(" PODE DEITAR LIXO");
 
     lcd.setCursor(2,1);
     lcd.print("CONTENTOR VAZIO");
     lcd.setCursor(2,2);
     lcd.print("PODE DEITAR LIXO");
       lcd.setCursor(0,3);
     lcd.print("NIVEL1:--ACEITAVEL--");

 
sensor1();
sensor2();
static unsigned long delayLeGPS = millis();

  if ( (millis() - delayLeGPS) > 10000 ) {
     leGPS();     
     delayLeGPS = millis(); 
  }
  
        float flat, flon;
        unsigned long age;

        gps.f_get_position(&flat, &flon, &age);

        if ( (flat == TinyGPS::GPS_INVALID_F_ANGLE) || (flon == TinyGPS::GPS_INVALID_F_ANGLE) ) {
           Serial.println( "GPS Sem Sinal !!!");
           analogWrite(ledgps,HIGH);
        }
        else{
          analogWrite(ledgps,LOW);   
        }
       
     if(estado==true){
       x++;
        Serial.println("Enviando SMS de Resposta."); 
       delay(1000);
      if(x==1){
        
          Serial.println("cheio");
            leGPS();
     String urlMapa = "Local Identificado: https://maps.google.com/maps/?&z=10&q=";
           urlMapa += String(flat,6);
           urlMapa += ",";
           urlMapa += String(flon,6);
        
   serialGSM.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  serialGSM.println("AT+CMGS=\"" + number + "\"\r"); // Replace x with mobile number
  delay(1000);

  serialGSM.println(urlMapa);// The SMS text you want to send
  delay(100);
   serialGSM.println((char)26);// ASCII code of CTRL+Z
  delay(1000);

        x=2;   
        estado=false;  
      }
      else{
          Serial.println("Normal");
           estado=false; 
      }
      
      
      
      
 
    }
    
    }

    
 



void leGPS() {
unsigned long delayGPS = millis();

   serialGPS.listen();
   bool lido = false;
   while ( (millis() - delayGPS) < 500 ) { 
      while (serialGPS.available()) {
          char cIn = serialGPS.read(); 
          lido = gps.encode(cIn); 
      }

      if (lido) { 
         float flat, flon;
         unsigned long age;
    
         gps.f_get_position(&flat, &flon, &age);
    
         String urlMapa = "Local Identificado: https://maps.google.com/maps/?&z=10&q=";
         
         urlMapa += String(flat,6);
         urlMapa += ",";
         urlMapa += String(flon,6);
         Serial.println(urlMapa);
         
         break; 
      }}}



      void sensor1(){
  if((sonar1.ping_cm()>=1&&sonar1.ping_cm()<=18)&&sonar1.ping_cm()!=0){
  
   analogWrite(rele, 255);
  servo1.write(180); 
      delay(3000);
       
      servo1.write(0); 
          delay(100);
           analogWrite(rele, 0);
          
          while(sonar1.ping_cm()>=1&&sonar1.ping_cm()<=18){
          Serial.println("AFASTAR DO BALDE");
        
    }

  }
  if(sonar1.ping_cm()==0){

      Serial.println("DEPOSITE O LIXO");
    
  }
}


void sensor2(){
  int nivel2=sonar2.ping_cm();
  nivel2=map(nivel2,0,40,0,20);
  
  Serial.print("Sensor2: ");
  Serial.print(nivel2); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("nivel");
  
    if(nivel2 <=4&&nivel2 >=1){
      estado=true;
      digitalWrite(ledverde, HIGH);
      digitalWrite(ledvermelho, LOW);
      digitalWrite(ledamarelo, HIGH); 
       
      Serial.print("CONTENTOR CHEIO");
      Serial.println(" NAO DEITAR LIXO");
          
 
      lcd.clear();
        lcd.setCursor(2,1);
      lcd.print("CONTENTOR CHEIO");
      lcd.setCursor(1,2);
      lcd.print(" NAO DEITAR LIXO");
       lcd.setCursor(0,3);
     lcd.print("NIVEL3: --CRITICO--");
           
    }


        else if(nivel2>5 &&nivel2 <=10){
      
       digitalWrite(ledverde, LOW);
      digitalWrite(ledvermelho, HIGH);
      digitalWrite(ledamarelo, HIGH);
      
      Serial.print("NÍVEL INTERMéEDIO");
   
     Serial.println(" PODE DEITAR LIXO");
          lcd.clear();
     lcd.setCursor(2,1);
     lcd.print("CONTENTOR VAZIO");
     lcd.setCursor(1,2);
     lcd.print(" PODE DEITAR LIXO");
      lcd.setCursor(0,3);
     lcd.print("NIVEL2:-INTERMEDIO--");
     delay(500);

      
  
  }

          else if(nivel2>10){
      
       digitalWrite(ledverde, HIGH);
      digitalWrite(ledvermelho, HIGH);
      digitalWrite(ledamarelo, LOW);
      
      Serial.print("NÍVEL ACEITAVEL");
   
     Serial.println(" PODE DEITAR LIXO");
          lcd.clear();
     lcd.setCursor(2,1);
     lcd.print("CONTENTOR VAZIO");
     lcd.setCursor(1,2);
     lcd.print(" PODE DEITAR LIXO");
      lcd.setCursor(0,3);
     lcd.print("NIVEL1:-INTERMEDIO--");
     delay(500);

      
  
  }


    
}
