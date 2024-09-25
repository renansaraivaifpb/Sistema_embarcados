#include <dht11.h>  // Biblioteca para o sensor DHT11 (umidade e temperatura)
#define DHT11PIN 7  // Define o pino 7 como o pino de dados do DHT11

#include <SPI.h>  // Biblioteca SPI para comunicação com o módulo MCP2515
#include <mcp2515.h>  // Biblioteca para controle do chip MCP2515 (Controlador CAN)



MCP2515 mcp2515(10);  // Instancia o objeto mcp2515 no pino 10 para CS (Chip Select)
dht11 DHT11;  // Instancia o objeto DHT11 para leitura do sensor

// Estruturas para armazenar os frames CAN que serão enviados
struct can_frame umidadeFrame;  // Frame CAN para enviar dados de umidade
struct can_frame temperaturaFrame;  // Frame CAN para enviar dados de temperatura

void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial com taxa de 9600 bps para debug
    mcp2515.reset();  // Reinicia o MCP2515 para garantir que ele está em um estado inicial limpo
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  // Configura a taxa de transmissão CAN para 500 Kbps e o oscilador do MCP para 8 MHz
    mcp2515.setNormalMode();  // Define o modo de operação normal no barramento CAN

    // Configura o frame de umidade
    umidadeFrame.can_id = 0x123;  // Define o ID do frame CAN (padrão de 11 bits, valor arbitrário 0x123)
    umidadeFrame.can_dlc = 1;  // Define o número de bytes de dados a serem enviados (1 byte neste caso)

    // Configura o frame de temperatura
    temperaturaFrame.can_id = 0x125;  // Define o ID do frame CAN para a temperatura (valor arbitrário 0x125)
    temperaturaFrame.can_dlc = 1;  // Define o número de bytes de dados a serem enviados (1 byte para temperatura)
}

void loop() {
    // Lê o valor do sensor DHT11 e armazena o resultado (chk) - usado para verificação, mas não no código atual
    int chk = DHT11.read(DHT11PIN);  

    // Armazena o valor da umidade e temperatura nos frames CAN como float (convertido para 1 byte)
    umidadeFrame.data[0] = (float)DHT11.humidity;  // Converte o valor de umidade do sensor em float e armazena no frame CAN
    temperaturaFrame.data[0] = (float)DHT11.temperature;  // Converte o valor da temperatura em float e armazena no frame CAN

    // Imprime os valores de umidade e temperatura no monitor serial para debug
    Serial.print(umidadeFrame.data[0]);  
    Serial.print(" ");
    Serial.println(temperaturaFrame.data[0]);

    // Envia os frames CAN para o barramento, um para temperatura e outro para umidade
    if (mcp2515.sendMessage(&temperaturaFrame) == MCP2515::ERROR_OK && mcp2515.sendMessage(&umidadeFrame) == MCP2515::ERROR_OK) {
        Serial.println("Mensagem enviada com sucesso");  // Mensagem de sucesso se ambos os frames forem enviados corretamente
    } else {
        Serial.println("Erro ao enviar mensagem");  // Mensagem de erro se falhar o envio de algum frame
    }

    delay(1000);  // Aguarda 1 segundo antes de realizar a próxima leitura e envio
}
