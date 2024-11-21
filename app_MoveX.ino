/* ************************************************APP PARA CONTROLAR ROBÔS**************************************************
    Criado por: Elismar Silva
    Data: 14.10.2024
    Versão: 1.0

    Descrição:
    Este app permite o controle de robôs via uma interface web. O usuário pode mover o robô para frente,
    para trás, esquerda e direita, além de sliders para controlar garras ou velocidade dos motores.
    A comunicação é feita via Wi-Fi com um ESP8266, utilizando um servidor web integrado.


    links para Downloads:
    Plugin: plugin que permite fazer upload de arquivos para o sistema de arquivos SPIFFS na memória flash do ESP8266
    .(https://github.com/esp8266/arduino-esp8266fs-plugin/releases/tag/0.5.0)

    Urls adicionais para gerenciamento de placas:
    http://arduino.esp8266.com/stable/package_esp8266com_index.json  >> Não precisa fazer downloads, so precisa copiar e colar na
    IDE do Arduino:  Menu >> Arquivo >> Preferencias >> Urls adicionais para gerenciamento de placas >> cole a url dentro do campo input

**************************************************************************************************************************************** */

// Inclusão das bibliotecas
#include <ESP8266WiFi.h>   // Biblioteca para controle do Wi-Fi no ESP8266
#include <ESP8266WebServer.h> // Biblioteca para criar um servidor web
#include <FS.h>            // Biblioteca para acessar o sistema de arquivos SPIFFS
#include <Servo.h>  // Biblioteca para os servos motores
#include "html.h"          // Arquivo que contém o código HTML para a interface web

// Defina o nome da rede e a senha do ponto de acesso (modo AP)
const char* ssid = "MoveX";  // Nome da rede Wi-Fi
const char* password = "";    // Senha vazia (sem proteção, apenas para desenvolvimento)

// Cria objetos para os servos
Servo servoEsquerda, servoDireita, servoGarra;
// Cria uma instância do servidor web na porta 80
ESP8266WebServer server(80);

// Variáveis para armazenar valores dos sliders de controle
int valorSlider1 = 0;  // Valor para slider 1
int valorSlider2 = 0;  // Valor para slider 2

// Definição dos pinos dos motores (ajuste conforme o hardware)
const int PIN_SERVO_ESQUERDA = D5;  // Pino para o controle do servo esquerda
const int PIN_SERVO_DIREITA = D6;   // Pino para o controle do servo direita
const int PIN_SERVO_GARRA = D7;     // Pino para o controle do servo garra


// Variável para armazenar o comando
String comandoRecebido = "";

// Variável para controlar o estado de movimento
bool controlarMovimento = false;

// Protótipo das funções
void enviarArquivo(const char* caminho);
void ajustarSlider();
void moverRobo(int motor1, int motor2, String mensagem);
void frente();
void tras();
void esquerda();
void direita();
void parado();

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial para debug

  // Inicializa os pinos dos motores como saída
  servoEsquerda.attach(PIN_SERVO_ESQUERDA);
  servoDireita.attach(PIN_SERVO_DIREITA);
  servoGarra.attach(PIN_SERVO_GARRA);
  
  // Inicializa o sistema de arquivos SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Erro ao montar o SPIFFS");
    return;  // Sai da função se ocorrer erro na montagem do SPIFFS
  }

  // Configura o ESP8266 como um ponto de acesso (Access Point)
  WiFi.softAP(ssid, password);
  Serial.println("Ponto de Acesso iniciado");

  // Exibe o IP do ESP8266 no modo AP
  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP do ponto de acesso: ");
  Serial.println(IP);

  // Define as rotas do servidor web para controle do robô
  server.on("/F", []() {
    comandoRecebido = "F";
  });  // Comando para frente
  server.on("/E", []() {
    comandoRecebido = "E";
  });  // Comando para esquerda
  server.on("/D", []() {
    comandoRecebido = "D";
  });  // Comando para direita
  server.on("/T", []() {
    comandoRecebido = "T";
  });  // Comando para trás
  server.on("/P", []() {
    comandoRecebido = "P";
  });  // Comando para parado

  // Rota para controle dos sliders
  server.on("/slider", ajustarSlider);

  // Rota para servir a página HTML principal
  server.on("/app", []() {
    server.send(200, "text/html", htmlPage);
  });

  // Rotas para servir arquivos de imagem da interface (armazenados no SPIFFS)
  server.on("/icon01.png", []() {
    enviarArquivo("/icon01.png");
  });
  server.on("/frente.png", []() {
    enviarArquivo("/frente.png");
  });
  server.on("/esquerda.png", []() {
    enviarArquivo("/esquerda.png");
  });
  server.on("/direita.png", []() {
    enviarArquivo("/direita.png");
  });
  server.on("/tras.png", []() {
    enviarArquivo("/tras.png");
  });

  // Inicia o servidor web
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();  // Lida com as requisições dos clientes (navegador)

  /* ************************************** Processa comandos recebidos ************************************ */

  switch (comandoRecebido[0]) {
    case 'F':
      controlarMovimento = !controlarMovimento;  // Inverte o estado de movimento
      if (controlarMovimento) {
        frente();  // Move para frente
      } else {
        parado();  // Para o robô
      }
      comandoRecebido = "";  // Limpa o comando
      break;

    case 'T':
      controlarMovimento = !controlarMovimento;  // Inverte o estado de movimento
      if (controlarMovimento) {
        tras();  // Move para trás
      } else {
        parado();  // Para o robô
      }
      comandoRecebido = "";  // Limpa a variável comando
      break;

    case 'D':
      direita();             // Move para direita
      comandoRecebido = "";  // Limpa a variável comando
      break;

    case 'E':
      esquerda();            // Move para esquerda
      comandoRecebido = "";  // Limpa a variável comando
      break;
    default:
      break;
  }
}

/* ******************************************** FUNÇÕES PARA MOVIMENTAR O ROBÔ ******************************************* */

void moverRobo(int val1, int val2, String mensagem) {
  servoEsquerda.write(val1);
  servoDireita.write(val2);
  server.send(200, "text/plain", mensagem);
}

void frente() {
  Serial.println("Frente");
  moverRobo(180, 0, "Movendo para frente"); // O robô se movimenta para frente
}

void tras() {
  Serial.println("Trás");
  moverRobo(0, 180, "Movendo para trás"); // O robô se movimenta para trás
}

void esquerda() {
  Serial.println("Esquerda");
  moverRobo(0, 0, "");
  server.send(200, "text/plain", ""); // O robô se movimenta para esquerda
}

void direita() {
  Serial.println("Direita");
  moverRobo(180, 180, "");
  server.send(200, "text/plain", ""); // O robô se movimenta para direita
}

void parado() {
  Serial.println("Parado");
  moverRobo(90, 90, "Parado");
  server.send(200, "text/plain", "Parado"); // O robô fica parado
}

/* *************************************************************************************************************** */

// Função para lidar com sliders de controle
void ajustarSlider() {
  if (server.hasArg("slider1")) {                  // Verifica se o valor do slider 1 foi enviado
    valorSlider1 = server.arg("slider1").toInt();  // Converte o valor para inteiro
    Serial.print("Slider 1 ajustado para: ");
    Serial.println(valorSlider1);
    int mapServoGarra = map(valorSlider1, 0, 180, 90, 0);  // Mapeia o valor do slider (0-100) para o PWM (0-255)
    servoGarra.write(mapServoGarra);
   
    
  }

  if (server.hasArg("slider2")) {                  // Verifica se o valor do slider 2 foi enviado
    valorSlider2 = server.arg("slider2").toInt();  // Converte o valor para inteiro
    Serial.print("Slider 2 ajustado para: ");
    Serial.println(valorSlider2);
  }

  server.send(200, "text/plain", "Sliders atualizados");
}

// Função para servir arquivos do sistema de arquivos SPIFFS
void enviarArquivo(const char* caminho) {
  File file = SPIFFS.open(caminho, "r");  // Abre o arquivo para leitura
  if (!file) {
    server.send(404, "text/plain", "Arquivo não encontrado");  // Retorna erro se o arquivo não for encontrado
    return;
  }

  server.streamFile(file, "image/png");  // Envia o arquivo para o cliente (navegador)
  file.close();
}
