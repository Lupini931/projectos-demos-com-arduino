#include <EEPROM.h>


#define btincrem 7
#define btleitura 6
#define btapagar 5

int addr=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 
  delay(1000);

  
pinMode(btincrem,INPUT_PULLUP);
pinMode(btleitura,INPUT_PULLUP);
pinMode(btapagar,INPUT_PULLUP);
}

void loop() {
      



 
  if(digitalRead(btincrem)==LOW){
      addr++;
      delay(200);
       Serial.print("INCREMENTO:");
      Serial.println(EEPROM.read(0));
      
  }
     EEPROM.write(0, addr);
     
    if(digitalRead(btleitura)==LOW){
     delay(200);
        EEPROM.write(1,EEPROM.read(0));
        Serial.print("VALOR GRAVADO NA EEPROM:");
        Serial.println(EEPROM.read(1));
          Serial.println();
              

  }
  
  if(digitalRead(btapagar)==LOW){
         delay(200);
      EEPROM.write(1,0);
       
      Serial.println("VALOR GRAVADO NA EEPROM APAGADO COM SUCESSO");
       Serial.println("POR FAVOR FAÇA A LEITURA DA EEPROM ");
        Serial.println();
       

   
  }
 
   
  
}
