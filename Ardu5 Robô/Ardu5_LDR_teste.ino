/*
    Teste do Sensor de Luz (LDR) com o Robô Ardu5
    Tutorial: https://youtu.be/7_SB3e8mmMk

    Se tiver luz ambiente, somente o led amarelo acende; caso não tenha luz ambiente, todos os led´s acendem.

    Entrada digital do LDR pelo Pin 8
    Pin 10 ativa o LDR, por isso ele precisa estar ligado
    Indicador de Luz com os pinos 9, 11, 12 e 13.

    Projeto: Robô Ardu5
    Data: 05 de agosto de 2023
    Autor: Laboratório Maker
    Canal no YouTube: https://bit.ly/laboratoriomaker
    Blog: https://laboratoriomaker.blogspot.com
    Instagram: https://www.instagram.com/laboratoriomaker

    Projeto original: Ardu5, Por: elprofegarcia.com
*/

void setup() {
  // Configurando os pinos que controlam os LEDs como Entrada e Saídas
  pinMode(8, INPUT);    // Porta 8 como Entrada do LDR
  pinMode(9, OUTPUT);   // Portas 9 a 13 como saídas
  pinMode(10, OUTPUT);  // LED Amarelo
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}
  void loop() {
    digitalWrite(10, HIGH);     // Coloca 5V no LDR
    if (digitalRead(8) == 1) {  // Se NÃO EXISTIR luz, acende todos os led´s
      digitalWrite(9, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
    }
    digitalWrite(9, LOW);  // Se EXISTIR luz, apaga os led´s e mantém o led amarelo ligado
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
