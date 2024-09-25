#include <SPI.h>  // Biblioteca SPI para comunicação com o módulo MCP2515
#include <mcp2515.h>  // Biblioteca para o controle do chip MCP2515 (Controlador CAN)
#include <Servo.h>  // Biblioteca para controle de servos

Servo myservo;  // Cria um objeto para o servo motor
MCP2515 mcp2515(10);  // Instancia o objeto MCP2515 usando o pino 10 como CS (Chip Select)

// Estruturas para armazenar os frames CAN recebidos
struct can_frame umidadeFrame;  // Frame CAN para dados de umidade
struct can_frame temperaturaFrame;  // Frame CAN para dados de temperatura

void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial com taxa de 9600 bps para debug
    mcp2515.reset();  // Reinicia o MCP2515 para garantir que ele está em um estado inicial limpo
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  // Configura a taxa de transmissão CAN para 500 Kbps e o oscilador para 8 MHz
    mcp2515.setNormalMode();  // Define o modo de operação normal no barramento CAN

    myservo.attach(8);  // Conecta o servo ao pino 8 do Arduino
}

// Função para imprimir no monitor serial os dados CAN recebidos
int printar_no_monitor(int id, int dlc, int data){
    Serial.print("ID: ");
    Serial.print(id, HEX);  // Exibe o ID da mensagem CAN recebida em hexadecimal
    Serial.print(" ");
    Serial.print("Tamanho: ");
    Serial.print(dlc);  // Exibe o número de bytes de dados (DLC)
    Serial.print(" ");
    Serial.print("Leitura: ");
    Serial.println(data);  // Exibe o dado contido no frame CAN
}

void loop() {
    // Verifica se há mensagens CAN recebidas para umidade e temperatura
    if (mcp2515.readMessage(&umidadeFrame) == MCP2515::ERROR_OK && mcp2515.readMessage(&temperaturaFrame) == MCP2515::ERROR_OK) {
        // Se houver mensagens válidas, exibe no monitor serial os dados
        printar_no_monitor(umidadeFrame.can_id, umidadeFrame.can_dlc, umidadeFrame.data[0]);
        printar_no_monitor(temperaturaFrame.can_id, temperaturaFrame.can_dlc, temperaturaFrame.data[0]);
        Serial.println();  // Adiciona uma linha em branco para separar as leituras
    } else {
        // Se não houver mensagens, exibe uma mensagem de erro no monitor serial
        Serial.println("Nenhuma mensagem recebida");
    }

    // Verifica se os valores de umidade e temperatura excedem 30
    if (umidadeFrame.data[0] > 30 && temperaturaFrame.data[0] > 30) {
        // Se os valores forem maiores que 30, movimenta o servo para a posição 190 graus
        myservo.write(190);  
        delay(500);  // Aguarda 500 ms
        myservo.write(0);  // Retorna o servo à posição inicial (0 graus)
        delay(500);  // Aguarda mais 500 ms
    }

    delay(1000);  // Atraso de 1 segundo antes de verificar novamente o barramento CAN
}
