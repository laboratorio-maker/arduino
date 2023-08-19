/*
   Robô Ardu5 - Animações diversas (*não usa o ldr)

   4 Animações diferentes

   Projeto: Robô Ardu5
   Data: 05 de agosto de 2023
   Autor: Laboratório Maker
   Canal no YouTube: https://bit.ly/laboratoriomaker
   Blog: https://laboratoriomaker.blogspot.com
   Instagram: https://www.instagram.com/laboratoriomaker
*/


// Define os LEDs
const int OlhoEsquerdo = 13;
const int OlhoDireito = 12;
const int LedVermelho = 11;
const int LedAmarelo = 10;
const int LedVerde = 9;

// Define o intervalo de tempo em milissegundos para cada animação
const int atrasoAnimacao = 80;

void setup() {
  // Configuração dos LEDs como saída
  pinMode(OlhoEsquerdo, OUTPUT);
  pinMode(OlhoDireito, OUTPUT);
  pinMode(LedVermelho, OUTPUT);
  pinMode(LedAmarelo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
}

// Função para acender todos os LEDs
void todosLedsLigados() {
  digitalWrite(OlhoEsquerdo, HIGH);
  digitalWrite(OlhoDireito, HIGH);
  digitalWrite(LedVermelho, HIGH);
  digitalWrite(LedAmarelo, HIGH);
  digitalWrite(LedVerde, HIGH);
}

// Função para apagar todos os LEDs
void todosLedsDesligados() {
  digitalWrite(OlhoEsquerdo, LOW);
  digitalWrite(OlhoDireito, LOW);
  digitalWrite(LedVermelho, LOW);
  digitalWrite(LedAmarelo, LOW);
  digitalWrite(LedVerde, LOW);
}

// Função para realizar o efeito de piscar alternado
void piscarAlternado() {
  for (int i = 0; i < 3; i++) {        // Repete o efeito 3 vezes
    digitalWrite(OlhoEsquerdo, HIGH);  // Acende o olho esquerdo
    digitalWrite(LedVermelho, HIGH);   // Acende o LED vermelho
    delay(150);             // Aguarda o tempo do efeito

    digitalWrite(OlhoEsquerdo, LOW);  // Apaga o olho esquerdo
    digitalWrite(LedVermelho, LOW);   // Apaga o LED vermelho
    delay(150);            // Aguarda o tempo do efeito

    digitalWrite(OlhoDireito, HIGH);  // Acende o olho direito
    digitalWrite(LedAmarelo, HIGH);   // Acende o LED amarelo
    delay(150);            // Aguarda o tempo do efeito

    digitalWrite(OlhoDireito, LOW);  // Apaga o olho direito
    digitalWrite(LedAmarelo, LOW);   // Apaga o LED amarelo
    delay(150);           // Aguarda o tempo do efeito
  }
}

void loop() {
  // ANIMAÇÃO 1: Luzes de Polícia
  for (int a = 0; a < 3; a++) {  // Repete a animação 3 vezes
    // Primeira fase: Piscar os olhos
    for (int i = 0; i < 3; i++) {        // Repete cada fase da animação 3 vezes
      todosLedsDesligados();             // Apaga todos os LEDs
      digitalWrite(OlhoEsquerdo, HIGH);  // Acende o olho esquerdo
      digitalWrite(OlhoDireito, HIGH);   // Acende o olho direito
      delay(atrasoAnimacao);             // Aguarda o tempo da animação
      todosLedsDesligados();             // Apaga todos os LEDs
      delay(atrasoAnimacao);             // Aguarda o tempo da animação
    }
    // Segunda fase: Acende os LEDs do peito
    for (int i = 0; i < 3; i++) {       // Repete cada fase da animação 3 vezes
      todosLedsDesligados();            // Apaga todos os LEDs
      digitalWrite(LedVermelho, HIGH);  // Acende o LED vermelho
      digitalWrite(LedAmarelo, HIGH);   // Acende o LED amarelo
      digitalWrite(LedVerde, HIGH);     // Acende o LED verde
      delay(atrasoAnimacao);            // Aguarda o tempo da animação
      todosLedsDesligados();            // Apaga todos os LEDs
      delay(atrasoAnimacao);            // Aguarda o tempo da animação
    }
  }
  // ANIMAÇÃO 2: LED acende e apaga na sequência
  for (int a = 0; a < 3; a++) {  // Repete a animação 3 vezes
    // Segunda fase: Acende os LEDs do peito e apaga na sequência
    for (int i = OlhoEsquerdo; i >= LedVerde; i--) {  // Percorre os LEDs de 13 a 9
      digitalWrite(i, HIGH);                          // Acende o LED atual
      delay(atrasoAnimacao);                          // Aguarda o tempo da animação
      digitalWrite(i, LOW);                           // Apaga o LED atual
    }
  }

  // ANIMAÇÃO 3: Sequência da animação 2 invertida
  for (int a = 0; a < 3; a++) {                       // Repete a animação 3 vezes
    for (int i = LedVerde; i <= OlhoEsquerdo; i++) {  // Percorre os LEDs de 9 a 13 (inverso)
      digitalWrite(i, HIGH);                          // Acende o LED atual
      delay(atrasoAnimacao);                          // Aguarda o tempo da animação
      digitalWrite(i, LOW);                           // Apaga o LED atual
    }
  }
  // ANIMAÇÃO 4: Piscar Alternado
  piscarAlternado();
}
