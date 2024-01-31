// Incluir as bibliotecas necessarias 
#include <OneWire.h> // Responsável por coordenar a comunicacao com o sensor 
#include <DallasTemperature.h> // Responsável por receber os dados do sensor e os interpretar

// Pre configurar a comunicacao entre o DS18B20 e o Arduino 
#define ONE_WIRE_BUS 2 // Define o pino do Arduino que recebera os dados do sensor transferidos pelo oneWire 

OneWire oneWire(ONE_WIRE_BUS); // Estabelece comunicacao via oneWire com o DS18B20 atraves do pino ja definido

DallasTemperature sensor(&oneWire); // Aponta para a biblioteca a presenca de sensores conectados atraves da comunicacao estabelecida 

// Comandos executados ao inicializar o Arduino 
void setup() { 

  Serial.begin(9600); // Inicia a porta serial com velocidade de 9600 

  sensor.begin(); // Inicia os sensores 
} 

// Comandos que serao executados repetidamente (loop)
void loop() { 

  sensor.requestTemperatures(); // Solicita ao sensor os dados de temperatura 

  float tempC = sensor.getTempCByIndex(0); // Recebe o dado, o converte para graus Celsius e o armazena na variavel tempC 

  if(tempC != -127.00){ // Caso o sensor funcione corretamente

    // Os proximos comandos imprimem a temperatura na porta serial 
    Serial.print("Temperatura: "); 
    Serial.print(tempC); // Imprime a temperatura obtida 
    Serial.print(" °C"); // Imprime o simbolo de grau e a letra “C”
    Serial.println(); // Imprime uma quebra de linha 
  
    // O resultado fica como: 
    /* 
    Temperatura: 25.75 °C 
    */ 
    
    delay(5000); // Estabelece um intervalo em milisegundos entre as medicoes (5000 ms = 5 s)

  }else{ // Caso o sensor nao funcione corretamente

    Serial.println("Erro ao ler temperatura!"); // Imprime uma mensagem de erro

  }
}
