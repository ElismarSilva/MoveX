# App de Controle de Robôs com ESP32

## Visão Geral

Este projeto permite controlar robôs remotamente através de uma interface web usando um ESP32. A aplicação web possibilita o controle do movimento do robô (frente, trás, esquerda, direita) e também permite o ajuste de componentes específicos, como garras e velocidade de motores, utilizando sliders.

## Autor

- **Criado por:** Elismar Silva
- **Data:** 14 de outubro de 2024
- **Versão:** 1.0

## Funcionalidades

- Controle de movimento: Frente, Trás, Esquerda, Direita e Parado.
- Ajuste de parâmetros via sliders, como garras e velocidade.
- Interface web para controle do robô, acessada via um ponto de acesso Wi-Fi criado pelo ESP32.
- Controle via comandos HTTP, tornando o uso flexível e fácil de integrar com outros dispositivos.

## Imagem do App

<img src="images/app.jpg" alt="Interface de controle do robô" width="300">

## Estrutura do Projeto

- **Bibliotecas Utilizadas:**
  - `WiFi.h`: Para configuração da rede Wi-Fi.
  - `WebServer.h`: Para criação do servidor web.
  - `SPIFFS.h`: Para armazenamento e recuperação de arquivos SPIFFS.
  - `ESP32Servo.h`: Para controle dos servos motores.

- **Arquivos Importantes:**
  - `html.h`: Contém o código HTML para a interface web.
  - Imagens (ex: `frente.png`, `esquerda.png`, `direita.png`, `tras.png`) para os ícones da interface.

## Configuração do Hardware

- **ESP32** como servidor web.
- **Servos** para controle das rodas e garra.
- **Sistema de Arquivos SPIFFS** para armazenar e servir arquivos da interface.

## Instruções de Uso

1. **Conexão e Configuração Wi-Fi:**
   - O ESP32 cria uma rede chamada `MoveX` (senha vazia por padrão) para permitir acesso ao controle do robô.
   - O IP da rede Wi-Fi do ponto de acesso é exibido no monitor serial para fácil acesso.

2. **Controle via Interface Web:**
   - Conecte-se à rede `MoveX`.
   - Acesse o endereço `http://<IP_DO_ESP32>/app` no navegador para visualizar a interface de controle.

3. **Comandos de Controle:**
   - **Frente:** `/F`
   - **Trás:** `/T`
   - **Esquerda:** `/E`
   - **Direita:** `/D`
   - **Parado:** `/P`

4. **Controle dos Sliders:**
   - Envie valores para ajustar configurações específicas como garras e velocidade de motores.

## Exemplo de Código

```cpp
void frente() {
  Serial.println("Movendo para frente");
  moverRobo(180, 0, "Movendo para frente");
}

void tras() {
  Serial.println("Movendo para trás");
  moverRobo(0, 180, "Movendo para trás");
}
