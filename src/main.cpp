// #include <Arduino.h>
// #include <time.h>

// #include "scheduler.h"
// #include "sensors.h"

// // void readSensors(void* p){
// // }

// // void saveData(void* p){
// // }

// void setup(){
//   // Sched_Init();           // periodic task

//   // CONFIG init, sensors

//   // Calculate LCM (least comun multiplier) to configure periodical interrupt
// }

// void loop(){

//   // 1- SET NEXT SENSOR INTERRUP

//   // 2- RUN THIS READ TASK CYCLE

//   // 3- PROCESS THIS DATA CYCLE

//   // 4- SAVE THIS DATA CYCLE

//   // 5- CHECK ALARMS

//   // 6- SIGFOX COMMUNICATION

//   // 7- DEEPSLEEP

//   // 8- WAIT NEXT INTERRUPT

//   // Sched_Dispatch();
// }

#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <SD.h> //INCLUSÃO DE BIBLIOTECA
 
const int chipSelect = 5; //PINO DIGITAL UTILIZADO PELO TERMINAL CS DO MÓDULO
 
// void setup(){
//     Serial.begin(115200); //INICIALIZA A SERIAL
//     while(!Serial){ //ESPERA PELA CONEXÃO DA PORTA SERIAL (APENAS PARA O ARDUINO LEONARDO) 
//     };

//     Serial.println("Inicializando o cartão de memória..."); //IMPRIME O TEXTO NO MONITOR SERIAL
//     Serial.println("********************************************"); //IMPRIME NO MONITOR SERIAL
//     pinMode(SS, OUTPUT); //DEFINE O PINO COMO SAÍDA
    
//     if(!SD.begin(chipSelect)){ //SE O CARTÃO DE MEMÓRIA NÃO ESTIVER PRESENTE OU FALHAR, FAZ
//         Serial.println("Cartão de memória falhou ou não está presente!"); //IMPRIME O TEXTO NO MONITOR SERIAL
//         return; //NÃO FAZ MAIS NADA
//     }

//     Serial.println("Cartão de memória inicializado com sucesso!"); //IMPRIME O TEXTO NO MONITOR SERIAL
//     Serial.println("********************************************"); //IMPRIME NO MONITOR SERIAL
//     Serial.println("Mensagem do arquivo de texto que está no cartão de memória:"); //IMPRIME O TEXTO NO MONITOR SERIAL
//     Serial.println(); //QUEBRA DE LINHA NO MONITOR SERIAL
    
//     SDFile dataFile = SD.open("arquivo.txt"); //dataFile RECEBE O CONTEÚDO DO ARQUIVO DE TEXTO (ABRIR UM ARQUIVO POR VEZ)
  
//     Serial.println("OI");

//     if(dataFile){ //SE EXISTIREM DADOS A SEREM LIDOS, FAZ
//         while(dataFile.available()){ //ENQUANTO HOUVER CONTEÚDO A SER LIDO, FAZ
//             Serial.write(dataFile.read()); //ESCREVE NA SERIAL AS INFORMAÇÕES DO ARQUIVO DE TEXTO
//         }
//         dataFile.close(); //ENCERRA A LEITURA (SEMPRE FECHAR O ARQUIVO ATUAL PARA ABRIR UM OUTRO ARQUIVO)
//     }
//     else{ //SENÃO, FAZ
//       Serial.println("Erro ao abrir o arquivo!"); //IMPRIME O TEXTO NO MONITOR SERIAL
//     } 
// }

// void loop(){
// }

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(5)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   myFile = SD.open("/arquivo.txt", FILE_WRITE);

//   // if the file opened okay, write to it:
//   if (myFile) {
//     Serial.print("Writing to test.txt...");
//     myFile.println("testing 1, 2, 3.");
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }

  // re-open the file for reading:
  myFile = SD.open("/arquivo.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}