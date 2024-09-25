# Projeto CAN Bus com Sensor DHT11 e Controle de Servo

Este projeto implementa a leitura de um sensor DHT11 (umidade e temperatura) e utiliza a comunicação via barramento CAN (Controller Area Network) para enviar e receber esses dados. Além disso, um servo motor é controlado com base nas leituras de umidade e temperatura.

## Descrição do Projeto

O sistema utiliza um sensor **DHT11** para capturar dados de **umidade** e **temperatura** e os envia para o barramento CAN utilizando o controlador **MCP2515**. O código também recebe mensagens via CAN e, com base nas informações recebidas, controla o movimento de um **servo motor**.

Se os valores de **umidade** e **temperatura** excederem 30, o servo motor é acionado, realizando movimentos entre 0 e 190 graus.

## Tecnologias Utilizadas

- **Arduino** ou outro microcontrolador compatível
- **Protocolo CAN Bus** para comunicação entre dispositivos
- **Sensor DHT11** para leitura de umidade e temperatura
- **Módulo MCP2515** para controle do barramento CAN
- **Servo Motor** controlado via mensagens recebidas
- **Bibliotecas**: SPI, MCP2515, Servo

## Componentes Necessários

- **Arduino** ou outro microcontrolador
- **Sensor DHT11**
- **Módulo MCP2515** para CAN
- **Servo motor**
- **Protoboard e cabos jumper**
- **Fonte de alimentação** compatível com os componentes

## Hardware
### CAN Shield

![Diagrama]([https://github.com/renansaraivaifpb/Sistema_embarcados/blob/main/output.png](https://github.com/renansaraivaifpb/Sistema_embarcados/blob/main/Comunicacao_CAN/wiring.png))

## Funcionalidades

1. **Leitura do Sensor DHT11**: Leitura de dados de umidade e temperatura.
2. **Envio de Dados via CAN**: Envio dos dados lidos pelo sensor ao barramento CAN.
3. **Recebimento de Dados via CAN**: Leitura de mensagens recebidas no barramento CAN.
4. **Controle de Servo Motor**: O servo é acionado quando a umidade e a temperatura excedem 30.
5. **Monitor Serial**: Exibe no monitor serial os dados recebidos e o status das mensagens CAN (sucesso/erro).

## Diagrama de Conexões

1. **Sensor DHT11**
   - VCC → 5V
   - GND → GND
   - Data → Pino 7 (Arduino)

2. **Módulo MCP2515**
   - VCC → 5V
   - GND → GND
   - SPI MOSI → Pino 11 (Arduino)
   - SPI MISO → Pino 12 (Arduino)
   - SPI SCK → Pino 13 (Arduino)
   - CS → Pino 10 (Arduino)

3. **Servo Motor**
   - VCC → 5V
   - GND → GND
   - Sinal → Pino 8 (Arduino)

## Como Usar

### 1. Instale as Bibliotecas Necessárias

Antes de começar, certifique-se de que as bibliotecas necessárias estão instaladas:

- **[SPI](https://www.arduino.cc/en/Reference/SPI)**: Comunicação SPI com o MCP2515.
- **[MCP2515](https://github.com/autowp/arduino-mcp2515)**: Controle do barramento CAN.
- **[Servo](https://www.arduino.cc/en/Reference/Servo)**: Controle do servo motor.

### 2. Configuração do Hardware

- Conecte o sensor **DHT11** ao pino 7 do Arduino.
- Conecte o **servo motor** ao pino 8 do Arduino.
- Conecte o módulo **MCP2515** ao Arduino utilizando os pinos SPI (10 para CS, 11 para MOSI, 12 para MISO e 13 para SCK).
- Assegure-se de que todos os componentes estão corretamente alimentados (5V/GND).

### 3. Carregar o Código no Arduino

Faça o upload do código para o Arduino utilizando a IDE do Arduino.

### 4. Verifique o Monitor Serial

Após o upload, abra o monitor serial na taxa de 9600 bps. Você verá as leituras de temperatura e umidade, além de mensagens de sucesso ou erro ao enviar dados via CAN.

### 5. Movimentação do Servo

Quando a umidade e a temperatura ultrapassarem 30 unidades, o servo se moverá para 190 graus e retornará a 0 graus com um pequeno atraso entre os movimentos.


## Exemplo de Saída no Monitor Serial
- ID: 123 Tamanho: 1 Leitura: 35
- ID: 125 Tamanho: 1 Leitura: 32

## Futuras Melhorias
- Implementar um sistema de monitoramento em tempo real utilizando uma interface gráfica.
- Adicionar suporte a múltiplos sensores e atuadores no barramento CAN.
- Testar diferentes taxas de bits para o barramento CAN.
- Incluir mais validações nas mensagens CAN recebidas para evitar possíveis erros.
