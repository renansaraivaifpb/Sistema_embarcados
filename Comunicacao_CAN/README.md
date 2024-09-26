Instituição: IFPB - Cajazeiras
Disciplina: Sistema Embarcados
Acadêmicos: Henrique Sobral e Renan Saraiva 
Orientador: prof. Dr. Leando Honorato

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

![MCP 2515](https://how2electronics.com/wp-content/uploads/2022/07/MCP2515-Parts.jpg)

## Protocolo CAN

Dispositivos em um barramento CAN são chamados de "nós". Cada nó consiste em uma CPU, controlador CAN e um transceptor, que adapta os níveis de sinal dos dados enviados e recebidos pelo nó. Todos os nós podem enviar e receber dados, mas não ao mesmo tempo.

Os nós não podem enviar dados diretamente entre si. Em vez disso, eles enviam seus dados para a rede, onde ficam disponíveis para qualquer nó ao qual foram endereçados.

![Rede CAN](https://gallery3.otenko.com/rest/data/10657?size=full)

O sinal da CANL tem o mesmo nível lógico do dado e o da CANH tem o nível lógico complementar, portanto, fica fácil de entender a figura a seguir. Observe que um nível lógico ‘1’, do dado, representa um bit recessivo porque CANL vai para nível lógico ‘1’ e CANH para nível lógico complementar ‘0’.

![ddp](https://raw.githubusercontent.com/renansaraivaifpb/Sistema_embarcados/refs/heads/main/Comunicacao_CAN/ddp.png)

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

### 3. Explicação do código

Para realizar o controle do Servo-Motor, é necessário incluir a biblioteca e criar um objeto para o mesmo:

```C
#include <Servo.h>  // Biblioteca para controle de servos
Servo myservo;  // Cria um objeto para o servo motor
```

Por padrão, a conexão CS do mcp2515 é conectado no pino 10, além de que a frequência oscilatória padrão é de 16 MHz, entretanto pode-se variar de 8 MHz e 20 MHz. Inicialmente, é necessário fazer algumas configurações no objeto criado do mcp2515. Assim, na função setup deve configurar para:

```C
MCP2515 mcp2515(10);
mcp2515.reset();
mcp2515.setBitrate(CAN_500KBPS, 8MHZ);
mcp2515.setNormalMode();

myservo.attach(8);  // Conecta o servo ao pino 8 do Arduino
```


#### 3.1 Estrutura da mensagem transmitida
No protocolo CAN existe dois tipos de quadros base e o extendido, na biblioteca utilizada para este projeto, usa-se o quadro base. Veja na figura abaixo que, que os quadros são divididos em campos
as quais realizam tarefas especificas. Porém, a biblioteca "MCP2515 CAN interface library" enfatiza, para pequenos projetos, os campos ID - identificador do frame -, DLC - tamanho do dado a ser transmitido (4 bit) - e Data field - tamanho do dado (8 bytes).

![Estrutura do frame](https://raw.githubusercontent.com/renansaraivaifpb/Sistema_embarcados/refs/heads/main/Comunicacao_CAN/Standard-and-extended-CAN-frames.png)

```C
// Configura o frame de umidade
umidadeFrame.can_id = 0x123;  // Define o ID do frame CAN (padrão de 11 bits, valor arbitrário 0x123)
umidadeFrame.can_dlc = 1;  // Define o número de bytes de dados a serem enviados (1 byte neste caso)

// Configura o frame de temperatura
temperaturaFrame.can_id = 0x125;  // Define o ID do frame CAN para a temperatura (valor arbitrário 0x125)
temperaturaFrame.can_dlc = 1;  // Define o número de bytes de dados a serem enviados (1 byte para temperatura)

umidadeFrame.data[0] = (float)DHT11.humidity;  // Converte o valor de umidade do sensor em float e armazena no frame CAN
temperaturaFrame.data[0] = (float)DHT11.temperature;  // Converte o valor da temperatura em float e armazena no frame CAN
```
#### 3.2 Envio da Mensagem

O envio da mensagem, deve ser utilizando a função da classe mcp2515, de acordo com a linha do código abaixo:

```C
mcp2515.sendMessage(&temperaturaFrame)
mcp2515.sendMessage(&umidadeFrame)
```

Para verificar o envio da mensagem para o barramento, é possível verificar os sinais correspondentes às mensagens transmitidos, no osciloscópio.

![Visualização transmissão da mensagem no barramento](https://raw.githubusercontent.com/renansaraivaifpb/Sistema_embarcados/refs/heads/main/Comunicacao_CAN/visualizacao%20msg%20can.jpg)


#### 3.3 Leitura da Mensagem

Para fazer a leitura, segue a mesma lógica, usa-se uma função da classe:

```C
mcp2515.readMessage(&umidadeFrame)
mcp2515.readMessage(&temperaturaFrame)

// Para verificar se há alguma mensagem transmitida no barramento CAN, usa-se  MCP2515::ERROR_OK.
// Então é possível fazer uma estrutura de condição e comparar o valor lido com  MCP2515::ERROR_OK, se for verdade, é porquê chegou a mensagem com sucesso.
```

#### 3.4 Controle do Servo-Motor

Assim, para simular o acionamento de um Ar-Condicionado baseado na umidade e temperatura, foi utilizado um Servo-Motor:

```C
if (umidadeFrame.data[0] > 30 && temperaturaFrame.data[0] > 30) {
        // Se os valores forem maiores que 30, movimenta o servo para a posição 190 graus
        myservo.write(190);  
        delay(500);  // Aguarda 500 ms
        myservo.write(0);  // Retorna o servo à posição inicial (0 graus)
        delay(500);  // Aguarda mais 500 ms
}
```



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
