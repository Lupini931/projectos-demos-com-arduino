#include <SoftwareSerial.h>
#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA

SoftwareSerial sim(10, 11);

String number = "+244951338626"; // +880 is the country code
#define verde1 10
#define amarelo1 9
#define vermelho1 8






 // SENSOR 1 DE CORRENTE FAIXA 1
#define CURRENT_CAL 18.40 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A2 ; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float ruido = 0.08; //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)
 
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA
 // Inicia variáveis de tempo
unsigned long millisTarefa1 = millis();


void setup() {
  Serial.begin(9600);
 
    // Define pinos dos leds como saída
  pinMode(verde1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(vermelho1, OUTPUT);


    
  Serial.println("Wait few seconds...");
  delay(5000);
  Serial.println("Sistem Started...");
  sim.begin(9600);
    
    
    emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)


   // emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)


  delay(1000);
   digitalWrite(verde1, HIGH);
    digitalWrite(amarelo1, HIGH);
     digitalWrite(vermelho1, HIGH);
     
     

}

void loop() {

// 1º FAIXA
  // Verifica se já passou 2000 milisegundos (VERDE)
  if((millis() - millisTarefa1) < 2000){
        
    Serial.println(" VERDE LIGADO");
    // Acende o led do pino 7
    digitalWrite(verde1, LOW);
     digitalWrite(amarelo1, HIGH);
    digitalWrite(vermelho1, HIGH);




   emon1.calcVI(17,100); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO

  Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
    
     if (currentDraw<0.35){
     Serial.println(" LINHA1 COM DEFEITO");

              SendMessage();
    }
    
    }



  // Verifica se já passou 4000 milisegundos  AMARELO
  if((millis() - millisTarefa1) > 4000){
        
   Serial.println(" AMARELO LIGADO");

    digitalWrite(verde1, HIGH);
      digitalWrite(vermelho1, HIGH);
     digitalWrite(amarelo1, LOW);

// FAIXA 1
        emon1.calcVI(17,100); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO

  Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
    
     if (currentDraw<0.35){
     Serial.println(" LINHA1 COM DEFEITO");

              SendMessage();
    }



    

    
     


}

  


    // Verifica se já passou 8000 milisegundos VERMELHO
  if((millis() - millisTarefa1) > 8000){
        
  Serial.println(" VERMELHO LIGADO");
    digitalWrite(verde1, HIGH);
    digitalWrite(amarelo1, HIGH);
     digitalWrite(vermelho1, LOW);


        emon1.calcVI(17,100); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO

  Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
    
     if (currentDraw<0.35){
     Serial.println(" LINHA1 COM DEFEITO");

              SendMessage();
    }


}
  

  
  // Verifica se já passou 8000 milisegundos
  if((millis() - millisTarefa1) > 16000){
    millisTarefa1 = millis();
  }
  
  


  
  }





void SendMessage()
{
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "LINHA 1 COM PROBLEMA";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(5000);
}
