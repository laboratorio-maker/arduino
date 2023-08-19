/*
  Projeto: Caveira Animada com Arduino
  Data: 28 de julho de 2023
  Autor: Laboratório Maker
  Canal no YouTube: https://bit.ly/laboratoriomaker
  Blog: https://laboratoriomaker.blogspot.com
  Instagram: https://www.instagram.com/laboratoriomaker

  Descrição:
  Neste projeto, criamos uma caveira animada usando o Arduino e alguns componentes eletrônicos. 
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


#include <Servo.h>
#include <EEPROM.h> // Biblioteca para trabalhar com a EEPROM

// DEFININDO OS PINOS DO ARDUINO:
// PINOS DO SENSOR:
const int trigPin = 8; // Pino de saída do sensor ultrassônico (trigger)
const int echoPin = 7;  // Pino de entrada do sensor ultrassônico (echo)

// PINOS DOS SERVOS:
const int olhoEsquerdoPin = 3; // Pino digital com PWM para o servo do olho esquerdo
const int olhoDireitoPin = 5;  // Pino digital com PWM para o servo do olho direito
const int mandibulaPin = 11;   // Pino digital com PWM para o servo da mandíbula

const int enderecoOlhos = 0; // Endereço na EEPROM para armazenar a posição dos olhos
const int enderecoMandibula = 2; // Endereço na EEPROM para armazenar a posição da mandíbula

// NOME DOS 3 SERVOS DA CAVEIRA:
Servo olhoEsquerdo;  
Servo olhoDireito;   
Servo mandibula;     

// MICRO SERVOS:
int velocidade = 10;     // Velocidade padrão dos servos

// ÂNGULO DOS MICRO SERVOS:
int fechada = 140;
const int abertura1 = 110;
const int abertura2 = 90;
const int abertura3 = 70;

const int olharFora = 125;
const int olharDentro = 55;
int olharFrente = 90; 



// TEMPO DE ESPERA ENTRE AS ANIMAÇÕES:
const int tempoEspera = 500; // 500 milissegundos

// DISTÂNCIAS DE CONTROLE DAS ANIMAÇÕES:
const int distanciaProxima = 20; // 20 centímetros
const int distanciaIntermediaria = 50; // 50 centímetros

void setup() {
  // Configuração dos pinos dos servos:
  // 1 - Criar os objetos olhoEsquerdo, olhoDireito e mandibula da classe Servo da biblioteca Servo.h.
  // 2 - Associar cada objeto a um pino específico usando a função attach().
  // 3 - Depois dessa configuração, você pode usar os objetos olhoEsquerdo, olhoDireito e mandibula para controlar os respectivos servos 
  // conectados aos pinos definidos, movimentando-os para as posições desejadas.
  olhoEsquerdo.attach(olhoEsquerdoPin);
  olhoDireito.attach(olhoDireitoPin);
  mandibula.attach(mandibulaPin);
  
  // Carregar posições calibradas da EEPROM (se existirem)
  olharFrente = EEPROM.read(enderecoOlhos);
  fechada = EEPROM.read(enderecoMandibula);

  if (olharFrente == 0xFF || fechada == 0xFF) {
    // Se as posições calibradas ainda não foram salvas na EEPROM (valores padrão de fábrica),
    // realizar a calibração e salvar as posições calibradas na EEPROM
    calibrarPosicoesIniciais();
    EEPROM.write(enderecoOlhos, olharFrente);
    EEPROM.write(enderecoMandibula, fechada);
  }
}

void loop() {
  // Medir a distância do sensor ultrassônico
  long duracao, distancia; // Cria duas variáveis do tipo long, o que significa que elas são números inteiros de 32 bits, adequados para armazenar valores maiores que 32.767.
  pinMode(trigPin, OUTPUT); // Configura o pino trigPin como uma saída digital (OUTPUT)
  digitalWrite(trigPin, LOW); // reiniciar o sinal de disparo antes de enviar um novo pulso.
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT); // Configura o pino echoPin como uma entrada digital (INPUT)

  duracao = pulseIn(echoPin, HIGH);  // A função pulseIn() mede a duração (em microssegundos) do pulso recebido no pino echoPin, que representa o tempo que o som levou para ir e voltar do objeto. 
  // A velocidade do som no ar é de 343 m/s, em centímetros seria: 34.300 cm/s ou 0,0343 cm/μs. 
  // Distância = (Tempo de ida e volta do som / 2) * Velocidade do som no ar

  // exemplo em microsegundos: 1176,46 μs = (588,23 μs IDA + 588,23 μs VOLTA)
  // exemplo em segundos: 1176,46 / 1.000.000 = 0,00117646 segundos

  // Se usar o tempo de duração em microsegundos, a fórmula da distância em centímetros será:
  // Distância = (duração em microssegundos x 0,0343) / 2 = 19,99982 ou
  // Distância = (duração em microssegundos / 2) * 0.0343 = 19,99982 = 20cm

  // Se usar o tempo de duração em segundos, terá que 1º converter a duração do pulso de microsegundos para segundos em seguida usar a fórmula da distância em centímetros:
  // Segundos = Microssegundos / 1.000.000  // Converte microsegundos para segundos
  // Distância = (duração em segundos x 34.300) / 2 = 19,99982 ou
  // Distância = (duração em segundos / 2) * 34.300 = 19,99982

  duracao = duracao / 1000000.0; // Converte a duração para segundos
  distancia = (duracao / 2) * 34300; // Calcula a distância em centímetros
  // Como o pulso medido pelo pulseIn() representa a ida e a volta do som, dividimos o valor de duracao por 2 para obter o tempo de ida. 
  
  // Controle dos movimentos com base na distância medida
  if (distancia <= distanciaProxima) {
    // Se a distância for menor ou igual a 20 cm, animação próxima
    moverOlhos(olharDentro);
    moverMandibula(abertura1);
    delay(tempoEspera);
    moverOlhos(olharFrente);
    moverMandibula(fechada);
    delay(tempoEspera);
  } else if (distancia <= distanciaIntermediaria) {
    // Se a distância for maior que 20 e menor ou igual a 50 cm, animação intermediária
    moverOlhos(olharFora);
    moverMandibula(abertura2);
    delay(tempoEspera);
    moverOlhos(olharFrente);
    moverMandibula(fechada);
    delay(tempoEspera);
  } else {
    // Se a distância for maior que 50 cm, animação distante
    moverOlhos(olharFora);
    moverMandibula(abertura3);
    delay(tempoEspera);
    moverOlhos(olharFrente);
    moverMandibula(fechada);
    delay(tempoEspera);
  }
}

// Função para mover os olhos para uma determinada posição
void moverOlhos(int pos) {
  // Movimenta os dois olhos para a posição passada como parâmetro
  olhoEsquerdo.write(pos);
  olhoDireito.write(pos);
  delay(velocidade);
}

// Função para mover a mandíbula para uma determinada posição
void moverMandibula(int pos) {
  mandibula.write(pos);
  delay(velocidade);
}

// Função para calibrar as posições iniciais dos servos e garantir que os olhos iniciem na posição frontal (90 graus)
void calibrarPosicoesIniciais() {
  olharFrente = 90;
  fechada = 120;
}
