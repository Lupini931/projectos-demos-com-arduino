//Inclusão de bibliotecas
#include<SoftwareSerial.h>    
#include<TinyGPS.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(7,8);
SoftwareSerial SerialGPS(10, 6);     
TinyGPS GPS;                       

float lat, lon, vel;
unsigned long data, hora;
unsigned short sat;
char msg;
  String urlMapa;

// Define os pinos dos módulos ultrassônicos
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

int led12 = 12;//verde
int led11 = 11;//vermelho
int led13 = 13;//amarelo
LiquidCrystal_I2C lcd(0x27,20,4);
 
// Define variáveis para armazenar os tempos de ida e volta do som
long duration1, duration2;

//Instaciar objecto
Servo servo_motor;

// Define variáveis para armazenar as distâncias medidas
float distance1, distance2;

void setup() {
   lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600); // Inicializa a comunicação serial para exibir resultados
  SerialGPS.begin(9600);  
   Serial.println("Buscando satelites...");
  mySerial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led13, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led11, OUTPUT);
  
  servo_motor.attach(9);

  digitalWrite(led13, LOW);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
}

void loop() {

 while (SerialGPS.available()) {
    if (GPS.encode(SerialGPS.read())) {

      //Hora e data
      GPS.get_datetime(&data, &hora);
      
      Serial.print("--");
      Serial.print(hora / 1000000);
      Serial.print(":");
      Serial.print((hora % 1000000) / 10000);
      Serial.print(":");
      Serial.print((hora % 10000) / 100);
      Serial.print("--");

      Serial.print(data / 10000);
      Serial.print("/");
      Serial.print((data % 10000) / 100);
      Serial.print("/");
      Serial.print(data % 100);
      Serial.println("--");
      
      //latitude e longitude
      GPS.f_get_position(&lat, &lon);

      Serial.print("Latitude: ");
      Serial.println(lat, 6);
      Serial.print("Longitude: ");
      Serial.println(lon, 6);
       urlMapa = "Local Identificado: https://maps.google.com/maps/?&z=10&q=";
           urlMapa += String(lat,6);
           urlMapa += ",";
           urlMapa += String(lon,6); 
           Serial.println(urlMapa); 
     
      //velocidade
      vel = GPS.f_speed_kmph();

      Serial.print("Velocidade: ");
      Serial.println(vel);

      //Satelites
      sat = GPS.satellites();

      if (sat != TinyGPS::GPS_INVALID_SATELLITES) {
        Serial.print("Satelites: ");
        Serial.println(sat);
      }

      Serial.println("");
    }
  }

  
  // Medição do Módulo 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2; // Conversão para cm

  // Medição do Módulo 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2; // Conversão para cm

  // Exibe os resultados
  Serial.print("Distância Módulo 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distância Módulo 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if(distance1 < 9){
    servo_motor.write(90);
    delay(1000);
    servo_motor.write(0);
    
    }else{
      servo_motor.write(0);
      }

    if(distance2 < 15){
      
      digitalWrite(led11, LOW);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, HIGH); 
      lcd.init();
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(1,1);
      lcd.print("CONTENTOR CHEIO");
      lcd.setCursor(1,2);
      lcd.print(" NAO DEITAR LIXO");
      SendMessage();  
        
    }
    
    else if((30>distance2) &&(distance2 > 15)){
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, LOW); 
       lcd.init();
  lcd.clear();
   lcd.backlight();
    lcd.setCursor(0,1);
    lcd.print("CONTENTOR QUASE CHEIO");
   lcd.setCursor(1,3);
   lcd.print(" PODE DEITAR LIXO");
      
      }else if(distance2 > 30){
      digitalWrite(led11, HIGH);
      digitalWrite(led12, LOW);
      digitalWrite(led13, HIGH); 
      
       lcd.init();
  lcd.clear();
   lcd.backlight();
    lcd.setCursor(1,1);
    lcd.print("CONTENTOR VAZIO");
   lcd.setCursor(1,2);
   lcd.print(" PODE DEITAR LIXO");
      }

 if (mySerial.available()>0) //verifica se existe alguma informação na porta serial do módulo gsm
 Serial.write(mySerial.read());//Caso existir escreve na porta serial do arduino a informação
  delay(200); // Aguarda um intervalo entre as medições
}


void gps()
{
  
}


void SendMessage()
{
  
 
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+244924887649\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Contentor de lixo esta cheio!!");// The SMS text you want to send
  delay(100);
    mySerial.println(urlMapa);// The SMS text you want to send
  
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
