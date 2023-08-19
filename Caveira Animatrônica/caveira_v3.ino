/*
  Projeto: Caveira Animatrônica com Arduino
  Data: 28 de julho de 2023
  Autor: Laboratório Maker
  Canal no YouTube: https://bit.ly/laboratoriomaker
  Blog: https://laboratoriomaker.blogspot.com
  Instagram: https://www.instagram.com/laboratoriomaker

  Descrição:
  Neste projeto, foi criado uma caveira animatrônica usando o Arduino e alguns componentes eletrônicos. 
  A caveira possui dois LEDs vermelhos nos olhos e três micro servos motores, 
  sendo dois deles responsáveis pelos movimentos dos olhos e o outro pelo movimento da boca.

  Um sensor ultrassônico (HR-SC04) é utilizado para detectar a proximidade de objetos 
  em relação à caveira. 
  Conforme uma pessoa se aproxima ou se afasta da caveira, diferentes animações são ativadas. 
  A animação dos olhos e da boca variam em velocidade e intensidade, 
  proporcionando uma experiência divertida e interativa.

  Este código foi desenvolvido para fins educacionais e de entretenimento. 
  Acesse o canal no YouTube, blog e Instagram para mais projetos e conteúdos relacionados 
  à eletrônica, programação e Maker.
*/

#include <Servo.h>  // Biblioteca para controlar servos
#include <EEPROM.h> // Biblioteca para utilizar a memória EEPROM
#include <HCSR04.h> // Biblioteca para controlar o sensor ultrassônico

const int trigPin = 8;       // Pino de trigger do sensor ultrassônico
const int echoPin = 7;       // Pino de echo do sensor ultrassônico

const int olhoEsquerdoPin = 3;   // Pino de controle do servo do olho esquerdo
const int olhoDireitoPin = 5;    // Pino de controle do servo do olho direito
const int mandibulaPin = 11;     // Pino de controle do servo da mandíbula

Servo olhoEsquerdo;       // Objeto para controlar o servo do olho esquerdo
Servo olhoDireito;        // Objeto para controlar o servo do olho direito
Servo mandibula;          // Objeto para controlar o servo da mandíbula

const int olhoEsquerdoFora = 50;    // Posição do olho esquerdo para olhar para fora
const int olhoEsquerdoDentro = 130; // Posição do olho esquerdo para olhar para dentro
int olhoEsquerdoFrente = 90;        // Posição do olho esquerdo para olhar para frente (inicial)

const int olhoDireitoFora = 130;    // Posição do olho direito para olhar para fora
const int olhoDireitoDentro = 50;   // Posição do olho direito para olhar para dentro
int olhoDireitoFrente = 90;         // Posição do olho direito para olhar para frente (inicial)

int fechada = 140;          // Posição da mandíbula fechada
const int abertura1 = 110;  // Primeira abertura da mandíbula
const int abertura2 = 90;   // Segunda abertura da mandíbula
const int abertura3 = 70;   // Terceira abertura da mandíbula

const int distanciaLonge = 50;   // Distância acima de 50 centímetros (para animação longe)
const int distanciaMedia = 30;   // Distância entre 30 e 50 centímetros (para animação média)
const int distanciaPerto = 15;   // Distância menor ou igual a 15 centímetros (para animação perto)

float distancia;         // Variável para armazenar a distância medida pelo sensor ultrassônico

HCSR04 hc(trigPin, echoPin);  // Objeto para controlar o sensor ultrassônico

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial (para debug)

  olhoEsquerdo.attach(olhoEsquerdoPin);   // Vincula o objeto ao pino do servo do olho esquerdo
  olhoDireito.attach(olhoDireitoPin);     // Vincula o objeto ao pino do servo do olho direito
  mandibula.attach(mandibulaPin);         // Vincula o objeto ao pino do servo da mandíbula

  olhoEsquerdo.write(olhoEsquerdoFrente); // Define a posição inicial dos olhos (frente)
  olhoDireito.write(olhoDireitoFrente);   // Define a posição inicial dos olhos (frente)
  mandibula.write(fechada);               // Fecha a mandíbula inicialmente
}

void loop() {
  float totalDistance = 0;

  for (int i = 0; i < 5; i++) {
    totalDistance += hc.dist();   // Realiza 5 medições consecutivas de distância e soma os valores
    delay(100);                   // Aguarda um pequeno intervalo entre cada medição
  }

  distancia = totalDistance / 5;  // Calcula a média das 5 medições para obter uma distância mais estável

  if (distancia > distanciaLonge) {
    animacaoDistanciaLonge();  // Chama a função para animação quando a distância for "longe"
  } else if (distancia > distanciaMedia) {
    animacaoDistanciaMedia();  // Chama a função para animação quando a distância for "média"
  } else if (distancia > distanciaPerto) {
    animacaoDistanciaPerto();  // Chama a função para animação quando a distância for "perto"
  } else {
    animacaoDistanciaMuitoPerto(); // Chama a função para animação quando a distância for "muito perto"
  }
}

void animacaoDistanciaLonge() {
  int posicaoOlhos = random(olhoEsquerdoFora - 10, olhoEsquerdoDentro + 10);
  olhoEsquerdo.write(posicaoOlhos);  // Move os olhos para uma posição aleatória
  olhoDireito.write(posicaoOlhos);
  delay(random(500, 1000));   // Aguarda um tempo aleatório para criar um efeito de piscar dos olhos
}

void animacaoDistanciaMedia() {
  int speed = random(1, 4); // 1: rápido, 2: médio, 3: lento

  for (int i = 0; i < 30; i++) { // Movimento suave dos olhos
    int posicaoOlhos = random(olhoEsquerdoDentro + 10, olhoEsquerdoFora - 10);
    olhoEsquerdo.write(posicaoOlhos);  // Move os olhos para uma posição aleatória
    olhoDireito.write(posicaoOlhos);
    delay(30 * speed);  // Aguarda um pequeno intervalo de tempo entre cada movimento dos olhos
  }

  int posicaoBoca = random(abertura2, abertura3);
  mandibula.write(posicaoBoca); // Abre a mandíbula para uma posição aleatória
  delay(300);
  mandibula.write(fechada);    // Fecha a mandíbula novamente após um curto intervalo
  delay(300);
}

void animacaoDistanciaPerto() {
  int speed = random(1, 4); // 1: rápido, 2: médio, 3: lento

  for (int i = 0; i < 30; i++) { // Movimento suave dos olhos
    int posicaoOlhos = random(olhoEsquerdoDentro + 10, olhoEsquerdoFor
