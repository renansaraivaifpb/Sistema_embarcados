#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_1(32,16,2);

const int ledPinos[] = {13, 12, 11, 10, 9, 8};
const int botoesPinos[] = {2, 3, 4, 5, 6, 7};
const int numLeds = 6;

void setup() {
  lcd_1.init();
  lcd_1.setCursor(0,0);
  lcd_1.backlight();
  lcd_1.display();
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPinos[i], OUTPUT);
    pinMode(botoesPinos[i], INPUT); // Habilita o resistor de pull-up interno nos pinos dos botões
  }
}
int ordem_correta[6];
int ordem_selecionada[6];
bool botao0Pressionado = false; // Variável para rastrear se o botão 1 foi pressionado
bool botao1Pressionado = false; // Variável para rastrear se o botão 2 foi pressionado
bool botao2Pressionado = false;
bool botao3Pressionado = false;
bool botao4Pressionado = false;
bool botao5Pressionado = false;

void resetar_condicoes_game(){
	botao0Pressionado = false; // Variável para rastrear se o botão 1 foi pressionado
    botao1Pressionado = false; // Variável para rastrear se o botão 2 foi pressionado
    botao2Pressionado = false;
    botao3Pressionado = false;
    botao4Pressionado = false;
    botao5Pressionado = false;
}

void loop() {
  bool numeros_unicos[6] = {false}; // Array para rastrear números únicos
  int quantidade_gerada = 0; // Contador para acompanhar a quantidade de números gerados

  while (quantidade_gerada < 6) {
    int numero = random(8, 14); // Gera um número aleatório entre 8 e 13
    int indice = numero - 8; // Calcula o índice no array (subtrai 8 para ajustar)

    if (!numeros_unicos[indice]) { // Verifica se o número ainda não foi gerado
      ordem_correta[quantidade_gerada++] = numero; // Adiciona o número ao array
      numeros_unicos[indice] = true; // Marca o número como gerado
    }
  }

  // mostrar ao jogador a sequencia que ele deve memorizar
  Serial.println("new sequence");
  for (int i = 0; i < 6; i++) {
    Serial.print(ordem_correta[i]);
    Serial.print(",");
    digitalWrite(ordem_correta[i],HIGH);
   	delay(100);
    digitalWrite(ordem_correta[i],LOW);
    delay(50);
  }
  Serial.println("\n \n aperte os botoes correspondentes \n");
  int x = 0;
  do {
    if(digitalRead(botoesPinos[0]) == HIGH && !botao0Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[0]);
      ordem_selecionada[x] = botoesPinos[0] + 11;
      botao0Pressionado = true;
      x++;
    } 
    if(digitalRead(botoesPinos[1]) == HIGH && !botao1Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[1]);
      ordem_selecionada[x] = botoesPinos[1] + 9;
      botao1Pressionado = true;
      x++;
    } 
    if(digitalRead(botoesPinos[2]) == HIGH && !botao2Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[2]);
      ordem_selecionada[x] = botoesPinos[2] + 7;
      botao2Pressionado = true;
      x++;
    } 
    if(digitalRead(botoesPinos[3]) == HIGH && !botao3Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[3]);
      ordem_selecionada[x] = botoesPinos[3] + 5;
      botao3Pressionado = true;
      x++;
    } 
    if(digitalRead(botoesPinos[4]) == HIGH && !botao4Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[4]);
      ordem_selecionada[x] = botoesPinos[4] + 3;
      botao4Pressionado = true;
      x++;
    }  
    if(digitalRead(botoesPinos[5]) == HIGH && !botao5Pressionado) {
      Serial.println("\n pressionado");
      Serial.print("indice: ");
      Serial.print(x);
      Serial.print("\n pino: ");
      Serial.print(botoesPinos[5]);
      ordem_selecionada[x] = botoesPinos[5] + 1;
      botao5Pressionado = true;
      x++;
    }  
    
  } while (x < 6);
  Serial.println("\n\n acabou \n\n");
  // mostrar ao jogador a sequencia que ele deve memorizar
  Serial.println("sequence selected");
  for (int i = 0; i < 6; i++) {
    Serial.print(ordem_selecionada[i]);
    Serial.print(",");
  }
  int verificacao = 0;
  // ordem_correta - ordem_selecionada 
  // pino - pino +  cts(normalizacao)
  // 13   - 2    +  11
  // 12   - 3    +   9
  // 11   - 4    +   7
  // 10   - 5    +   5
  //  9   - 6    +   3
  //  8   - 7    +   1 
  for(int j=0;j<6;j++){
    if(ordem_correta[j] == ordem_selecionada[j]){
    	verificacao++;
      	Serial.println("\n\n Verificacao: ");
      	Serial.println(verificacao);
        Serial.println("\n\n ");
    }
  }
  lcd_1.setCursor(0, 0);
  
  if(verificacao==6){
    lcd_1.print("Voceh ganhou!");
    delay(1000);
  }else{
    
    lcd_1.print("Game over!");
    delay(1000);
    
  }
  lcd_1.clear();
  resetar_game();
}
