#define BLYNK_PRINT Serial
#include "ESP8266WiFi.h"
#include "BlynkSimpleEsp8266.h"


#define BLYNK_TEMPLATE_ID "TMPL28J6Yd21V"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "3UsKRujFH46qbri6KrVA7yU__DkafNqT"

char auth[] = BLYNK_AUTH_TOKEN;
// Credenciais da rede WiFi
char ssid[] = "FELIPE_S-2G";
char pass[] = "FHFG0928";
int quant = 0;
int media = 0;
int soma = 0;

// Defina o pino do sensor e o valor limiar
const int sensorPin = A0;
const float percent = 0.1;


void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Conecta ao Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Configuração do sensor
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Executa o Blynk
  Blynk.run();

  // Lê o valor do sensor
  int sensorValue = analogRead(sensorPin);
  soma += sensorValue;
  quant++;
  media = soma/quant;

  Serial.print("Soma: ");
  Serial.println(soma);

  Serial.print("Quantidade: ");
  Serial.println(quant);

  Serial.print("Média: ");
  Serial.println(media);

  if(quant >= 500){
    soma = 0;
    quant = 0;
  }

  Serial.print("Valor do Sensor: ");
  Serial.println(sensorValue);

  if(sensorValue > (media + (media*0.1))){
    Blynk.virtualWrite(V1, 1);
  }else{ Blynk.virtualWrite(V1, 0);}
  // Aguarda 1 segundo antes de ler novamente
  delay(1000);
}
