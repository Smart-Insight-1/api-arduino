#include "Ultrasonic.h"

int pinoTrigger = 8;
int pinoEcho = 7;
const int distMax = 15;

HC_SR04 sensor(pinoTrigger, pinoEcho);

// true = produto está fora
bool produtoFora = false;

unsigned long inicioTempo = 0;
unsigned long fimTempo = 0;

int sensorID = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float distancia = sensor.distance();

  // PRODUTO NÃO ESTÁ
    if (distancia == 0 || distancia > distMax) {
    if (!produtoFora) {
      produtoFora = true;
      inicioTempo = millis();
    }
  } 
  // PRODUTO VOLTOU
  else {
    if (produtoFora) {
      produtoFora = false;
      fimTempo = millis();

      float tempoFora = (fimTempo - inicioTempo) / 1000.0;

      if(tempoFora > 1) {
        Serial.print(sensorID);
        Serial.print(";");
        Serial.println(tempoFora);
      }
    }
  }

  delay(200);
}