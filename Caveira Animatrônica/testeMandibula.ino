/*
    Teste da Mandíbula da Caveira

    Este código foi desenvolvido para testar o movimento suave da mandíbula de uma caveira animatrônica.
    Conecte o servo da mandíbula ao pino 11 do Arduino.

    Projeto: Caveira Animada com Arduino
    Data: 28 de julho de 2023
    Autor: Laboratório Maker
    Canal no YouTube: https://bit.ly/laboratoriomaker
    Blog: https://laboratoriomaker.blogspot.com
    Instagram: https://www.instagram.com/laboratoriomaker
*/

#include <Servo.h>

Servo mandibula;  // Criar um objeto Servo para controlar a mandíbula

const int mandibulaPin = 11; // Pino do Arduino para controlar a mandíbula

int posFechada = 140; // Ângulo da mandíbula na posição fechada
int posAberta = 70; // Ângulo da mandíbula na posição aberta
int passo = 1; // Passo para suavizar os movimentos (ajuste conforme necessário)
int delaySuave = 30; // Tempo de espera entre os passos (ajuste conforme necessário)

void setup() {
  mandibula.attach(mandibulaPin); // Associar o objeto mandibula ao pino escolhido
  mandibula.write(posFechada); // Inicialmente, deixar a mandíbula fechada
}

void loop() {
  // Abrir a mandíbula suavemente
  for (int i = posFechada; i >= posAberta; i -= passo) {
    mandibula.write(i);
    delay(delaySuave);
  }

  // Fechar a mandíbula suavemente
  for (int i = posAberta; i <= posFechada; i += passo) {
    mandibula.write(i);
    delay(delaySuave);
  }
}
