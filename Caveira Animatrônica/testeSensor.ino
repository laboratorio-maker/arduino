/*
    Teste do Sensor de Distância Ultrassônico

    Este código foi desenvolvido para testar o funcionamento do sensor de distância ultrassônico (HC-SR04) com o Arduino.
    Conecte o pino Trig do sensor ao pino 8 do Arduino e o pino Echo ao pino 7.

    Projeto: Teste de Sensor de Distância Ultrassônico
    Data: 28 de julho de 2023
    Autor: Laboratório Maker
    Canal no YouTube: https://bit.ly/laboratoriomaker
    Blog: https://laboratoriomaker.blogspot.com
    Instagram: https://www.instagram.com/laboratoriomaker
*/

#include <HCSR04.h>

HCSR04 hc(8, 7); // Inicialização da classe HCSR04 (pino trig, pino echo)
const int numMeasurements = 5; // Número de medições para calcular a média

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    float totalDistance = 0;

    for (int i = 0; i < numMeasurements; i++) {
        totalDistance += hc.dist(); // Realiza várias medições e soma os resultados
        delay(100); // Aguarda um breve intervalo entre cada medição
    }

    float averageDistance = totalDistance / numMeasurements;
    float distanceInCm = averageDistance / 2; // Converte o resultado em centímetros (cada microssegundo equivale a 0,017 cm)

    int meters = distanceInCm / 100; // Obtém a parte inteira dos metros
    int centimeters = distanceInCm - (meters * 100); // Obtém a parte decimal dos centímetros

    Serial.print("Distância média: ");
    Serial.print(meters);
    Serial.print(" metros e ");
    Serial.print(centimeters);
    Serial.println(" centímetros");

    delay(1000); // Aguarda um intervalo entre as leituras completas
}
