#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);

String number = "+244931997478"; // +880 is the country code
float flat=-8.875925;
float flon=13.275204;

void setup() {
  Serial.begin(9600);
  Serial.println("Wait few seconds...");
  delay(5000);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Type c to make a call and s to send an SMS");
}

void loop() {
  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 'c':
        callNumber();
        break;
      case 's':
        SendMessage();
        break;
    }
  if (sim.available() > 0)
    Serial.write(sim.read());
}

void SendMessage()
{
    String urlMapa = "Local Identificado: https://maps.google.com/maps/?&z=10&q=";
           urlMapa += String(flat,6);
           urlMapa += ",";
           urlMapa += String(flon,6);
        Serial.println(urlMapa); 
        
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  //String SMS = "Hi Razib, How are you?";
  sim.println(urlMapa);
  delay(100);
  sim.println((char)26);
  delay(1000);
}


void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
}
