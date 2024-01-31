// Incluir as bibliotecas necessarias
#include <OneWire.h> // Responsável por coordenar a comunicacao com o sensor 
#include <DallasTemperature.h> // Responsável por receber os dados do sensor e os interpretar
#include <LiquidCrystal_I2C.h> // Gere o display LCD

// Pre configurar a comunicacao entre o DS18B20 e o Arduino
#define ONE_WIRE_BUS 2 // Define o pino do Arduino que recebera os dados do sensor transferidos pelo oneWire 

OneWire oneWire(ONE_WIRE_BUS); // Estabelece comunicacao via oneWire com o DS18B20 atraves do pino ja definido

DallasTemperature sensor(&oneWire); // Aponta para a biblioteca a presenca de sensores conectados atraves da comunicacao estabelecida

const int LCD_linhas = 2; // Número de linhas do seu display LCD
const int LCD_colunas = 16; // Número de colunas do seu display LCD
const int numeroPiscadas = 3; // Número de vezes que o dado pisca
// As próximas 3 variáveis descrevem os intervalos de tempo empregados no display LCD e podem ser editados conforme o desejo do usuário
// OBS: Como todo o processo de requisitar, receber e interpretar o dado de temperatura leva, aproximadamente, 0.5 seg, para manter um intervalo total de cerca de 5 seg, a soma das variáveis abaixo foi ajustada para cerca de 4.5 seg
const float LCD_tempoAceso = 2.5; // Tempo, em segundos, em que o dado é exibido
const float LCD_tempoPiscando = 1.8; // Tempo, em segundos, em que o dado permanece piscando
const float LCD_tempoApagado = 0.2; // Intervalo, em segundos, entre a exibição dos dados

LiquidCrystal_I2C lcd(0x27,LCD_colunas,LCD_linhas); // Declara o display como um objeto chamado "lcd"

// Comandos executados ao inicializar o Arduino
void setup() {

  Serial.begin(9600); // Inicia a porta serial com velocidade de 9600

  sensor.begin(); // Inicia os sensores

  lcd.init(); // Inicia o display lcd(x, y), de x colunas e y linhas; Nesse caso, lcd(16,2);
  lcd.backlight(); // Liga a luz de fundo do display
  lcd.setCursor(0, 0); // Posiciona o cursor na primeira coluna (0) e na primeira linha (0)
  lcd.print("Temperatura: "); // Imprime, na primeira linha, o texto “Temperatura:”
  Serial.println("Display LCD ligado"); // Informa, na porta serial, que o display esta ligado

}

// Comandos que serao executados repetidamente (loop)
void loop() {

  sensor.requestTemperatures(); // Solicita ao sensor os dados de temperatura

  float tempC = sensor.getTempCByIndex(0); // Recebe o dado, o converte para graus Celsius e o armazena na variavel tempC

  if (tempC != -127.00) { // Caso o sensor funcione corretamente

    // Os proximos comandos imprimem a temperatura na porta serial
    Serial.print("Temperatura: "); 
    Serial.print(tempC); // Imprime a temperatura obtida 
    Serial.print(" °C"); // Imprime o simbolo de grau e a letra “C”
    Serial.println(); // Imprime uma quebra de linha 

    // O resultado fica como:
    /*
      Temperatura: 25.75 °C
    */

    lcd.backlight(); // Liga a luz de fundo do display

    // Os proximos comandos imprimem a temperatura no display LCD
    lcd.setCursor(0, 1); // Posiciona o cursor na primeira coluna (0) e na segunda linha (1)
    lcd.print(tempC); // Imprime o valor da temperatura coletada
    lcd.print(" ");
    lcd.print(char(223)); // Imprime o simbolo de grau
    lcd.print("C"); // Imprime a letra “C”

    // O resultado fica como:
    /*
      Temperatura:
      25.75 °C
    */

    delay(LCD_tempoAceso * 1000); // Estabelece um intervalo em milisegundos entre as medicoes
    
    // Apaga e reescreve o valor no display, fazendo o valor piscar
    for (int i = 0; i < numeroPiscadas; i++) {
      lcd.setCursor(0, 1);
      for (int j = 0; j < LCD_colunas; j++) {
        lcd.print(" ");
      }
      
      delay((LCD_tempoPiscando * 1000)/(numeroPiscadas * 2)); // Gere uma pausa entre os processos de apagar e reescreer os dados

      lcd.setCursor(0, 1); // Posiciona o cursor na primeira coluna (0) e na segunda linha (1)
      lcd.print(tempC); // Imprime o valor da temperatura coletada
      lcd.print(" ");
      lcd.print(char(223)); // Imprime o simbolo de grau
      lcd.print("C"); // Imprime a letra “C”

      delay((LCD_tempoPiscando * 1000)/(numeroPiscadas * 2)); // Gere uma pausa entre os processos de apagar e reescreer os dados
    }

    lcd.noBacklight(); // Desliga a luz de fundo do display

    delay(LCD_tempoApagado*1000);

  } else { // Caso o sensor nao funcione corretamente

    Serial.println("Erro ao ler temperatura!"); // Imprime uma mensagem de erro

  }
}
