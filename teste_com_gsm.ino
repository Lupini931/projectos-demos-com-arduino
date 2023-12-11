

#include <Sim800L.h>
#include <SoftwareSerial.h>               

#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA

#define RX  10
#define TX  11

#define  led 13

Sim800L GSM(RX, TX);

/*
 * In alternative:
 * Sim800L GSM;                       // Use default pinout
 * Sim800L GSM(RX, TX, RESET);        
 * Sim800L GSM(RX, TX, RESET, LED);
 */

char* text;
char* number;
bool error;           //to catch the response of sendSms

 
#define CURRENT_CAL 18.40 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A2; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float ruido = 0.185; //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)
 
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA
 
void setup(){  
    GSM.begin(4800); 
    pinMode(led,OUTPUT);
    
    digitalWrite(led,LOW);
    
      number="+244951107889";    //change to a valid number. 
        error=GSM.sendSms(number,text);
  Serial.begin(9600); //INICIALIZA A SERIAL
 
  emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)

}
 
void loop(){

    
  emon1.calcVI(17,100); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO


  
    Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
 
}
