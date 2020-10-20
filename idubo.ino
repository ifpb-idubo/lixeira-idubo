#include "FS.h"
#include "SPIFFS.h"
#include "DataToMaker.h"
#include <WiFi.h>
#include <Ultrasonic.h>

#define redLED 2

#define FORMAT_SPIFFS_IF_FAILED true
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  900

const char* chave = "da16BXvAxO7z3AkY2spx-H"; // Chave IFTTT
String nomeProjeto = "idubo";    // Nome do projeto pro IFTTT

String nomeRede  = "";               // Variável onde ficará salva o nome da rede local
String senhaRede = "";               // Variável onde ficará salva a senha da rede local

int distancia;                       // Variável que guardará a distância lida pelo sensor ultrassônico
Ultrasonic ultrasonic(12, 13);       // Instanciação do ultrassom, pino 12 ligado ao Trigger e 13 ao Echo

bool hasNetwordData = false;      // Booleana que irá receber 0 caso não haja dados da rede armazenados e 1 caso tenha
RTC_DATA_ATTR int bootCount = 0;     // Variável alocada na memória não-volátil da partição RTC do chip da ESP que contará qual o número do boot atual do programa

DataToMaker event(chave, nomeProjeto);

void setup() {
  Serial.begin(115200);                                          // Inicia a comunicação Serial
  Serial.println("Boot de número: " + String(bootCount));           // Printa no Monitor Serial o número atual do boot

  setPins();

  verifyData(SPIFFS, "/", 0);                              // Define temDadoArmazenado como false caso não exista dados salvos no root e true caso tenha. Também lista o nome dos arquivos salvos na SPIFFS
  //deleteData();
}

void loop() {
  // put your main code here, to run repeatedly:

}
