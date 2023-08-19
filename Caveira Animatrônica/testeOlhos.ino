/*
    Teste dos Olhos da Caveira

    Este código foi desenvolvido para testar o movimento suave dos olhos de uma caveira animatrônica.
    Conecte os servos dos olhos no pino 3 (esquerdo) e pino 5 (direito) do Arduino.

    Projeto: Caveira Animada com Arduino
    Data: 28 de julho de 2023
    Autor: Laboratório Maker
    Canal no YouTube: https://bit.ly/laboratoriomaker
    Blog: https://laboratoriomaker.blogspot.com
    Instagram: https://www.instagram.com/laboratoriomaker
*/

#include <Servo.h>

Servo olhoEsquerdo;   // Cria um objeto Servo para controlar o olho esquerdo
Servo olhoDireito;    // Cria um objeto Servo para controlar o olho direito

const int olhoEsquerdoPin = 3; // Pino digital com PWM para o servo do olho esquerdo
const int olhoDireitoPin = 5;  // Pino digital com PWM para o servo do olho direito

const int olharFora = 125;
const int olharDentro = 55;   // Modificado para iniciar em 90 graus
int olharFrente = 90;

int passo = 1;          // Passo para suavizar os movimentos (ajuste conforme necessário)
int delaySuave = 20;    // Tempo de espera entre os passos (ajuste conforme necessário)

void setup() {
  olhoEsquerdo.attach(olhoEsquerdoPin);   // Associa o servo do olho esquerdo ao pino escolhido
  olhoDireito.attach(olhoDireitoPin);     // Associa o servo do olho direito ao pino escolhido
  olhoEsquerdo.write(olharFrente);        // Inicialmente, posiciona os olhos para frente
  olhoDireito.write(olharFrente);
}

void loop() {
  // Olhar para fora suavemente
  for (int i = olharFrente; i <= olharFora; i += passo) {
    olhoEsquerdo.write(i);
    olhoDireito.write(i);
    delay(delaySuave);
  }

  // Olhar para dentro suavemente
  for (int i = olharFora; i >= olharDentro; i -= passo) {
    olhoEsquerdo.write(i);
    olhoDireito.write(i);
    delay(delaySuave);
  }

  // Retornar para a posição de frente suavemente
  for (int i = olharDentro; i <= olharFrente; i += passo) {
    olhoEsquerdo.write(i);
    olhoDireito.write(i);
    delay(delaySuave);
  }
}
