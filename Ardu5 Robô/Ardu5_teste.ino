/*
    Teste do Robô Ardu5
    Tutorial: https://youtu.be/lEOsWI0G7xk (Prueba de Robot Ardu5)

    Este programa acende todos os LEDs e quando se tapa a fotorresistência, inicia uma sequência em ordem descendente de 13 ao 9

    Projeto: Robô Ardu5
    Data: 05 de agosto de 2023
    Autor: Laboratório Maker
    Canal no YouTube: https://bit.ly/laboratoriomaker
    Blog: https://laboratoriomaker.blogspot.com
    Instagram: https://www.instagram.com/laboratoriomaker

    Projeto original: Ardu5 Prueba, Por: elprofegarcia.com
*/


// Define o tempo de retardo (espera) entre os acionamentos dos LEDs
int retardo = 200;

// Função setup() é executada uma vez quando a placa Arduino é ligada ou resetada
void setup() {
  // Configura os pinos 13, 12, 11, 10 e 9 como saída (LEDs)
  pinMode(13, OUTPUT);  // Olho esquerdo
  pinMode(12, OUTPUT);  // Olho direito
  pinMode(11, OUTPUT);  // LED vermelho
  pinMode(10, OUTPUT);  // LED amarelo
  pinMode(9, OUTPUT);   // LED verde

  pinMode(8, INPUT);  // Entrada do LDR

  // Liga todos os LEDs (13 ao 9) por 1 segundo e depois desliga-os por 1 segundo
  digitalWrite(13, HIGH);  // Olho esquerdo
  digitalWrite(12, HIGH);  // Olho direito
  digitalWrite(11, HIGH);  // LED vermelho
  digitalWrite(10, HIGH);  // LED amarelo
  digitalWrite(9, HIGH);   // LED verde
  delay(1000);
  digitalWrite(13, LOW);  // Olho esquerdo
  digitalWrite(12, LOW);  // Olho direito
  digitalWrite(11, LOW);  // LED vermelho
  digitalWrite(10, LOW);  // LED amarelo
  digitalWrite(9, LOW);   // LED verde
  delay(1000);

  // Liga novamente todos os LEDs por 1 segundo e depois desliga-os por 1 segundo
  digitalWrite(13, HIGH);  // Olho esquerdo
  digitalWrite(12, HIGH);  // Olho direito
  digitalWrite(11, HIGH);  // LED vermelho
  digitalWrite(10, HIGH);  // LED amarelo
  digitalWrite(9, HIGH);   // LED verde
  delay(1000);
  digitalWrite(13, LOW);  // Olho direito
  digitalWrite(12, LOW);  // Olho direito
  digitalWrite(11, LOW);  // LED vermelho
  digitalWrite(10, LOW);  // LED amarelo
  digitalWrite(9, LOW);   // LED verde
  delay(1000);
}

// Função loop() é executada continuamente após a função setup() terminar
void loop() {
  // Verifica se a fotorresistência foi tapada
  if (digitalRead(8) == 1) {
    // Inicia a sequência dos LEDs em ordem descendente do 13 ao 9
    digitalWrite(13, HIGH);  // Olho esquerdo
    delay(retardo);
    digitalWrite(13, LOW);   // Olho esquerdo
    digitalWrite(12, HIGH);  // Olho direito
    delay(retardo);
    digitalWrite(12, LOW);   // Olho direito
    digitalWrite(11, HIGH);  // LED vermelho
    delay(retardo);
    digitalWrite(11, LOW);   // LED vermelho
    delay(retardo);
    digitalWrite(9, HIGH);  // LED verde
    delay(retardo);
    digitalWrite(9, LOW);  // LED verde
  } else {
    // Se a fotorresistência não estiver tapada, mantém o LED Amarelo aceso
    digitalWrite(10, HIGH);  // LED amarelo
  }
}
