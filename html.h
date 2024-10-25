#ifndef HTML_H
#define HTML_H

// Código da página HTML
// htmlPage variável que armazena o texto html
const char* htmlPage = R"rawliteral(
   <!DOCTYPE html>
<html lang="pt-BR">

<!--Início do head-->
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Movex</title>
    <link rel="icon" href="/icon01.png" type="image/png">

    <!-- Início do CSS-->
    <style>
        body {
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #FF3F00; /*#FF3F00(Fundo laranja)  #007bff(Fundo azul)*/
            font-family: Arial, sans-serif;
            overflow: hidden; /* Evitar a barra de rolagem padrão */
        }

        .container {
            width: 100%;
            height: 100%;
            display: flex;
            justify-content: center; /* Centraliza o conteúdo */
            align-items: center;
            padding: 20px;
            flex-wrap: wrap; /* Permite que os elementos quebrem linha em telas pequenas */
        }

        .arrows {
            display: grid;
            grid-template-columns: repeat(3, 150px); /* Tamanho uniforme para as colunas */
            grid-template-rows: repeat(4, 150px); /* Tamanho uniforme para as linhas */
            gap: 40px; /* Aumentado o espaçamento entre botões */
            justify-items: center;
            align-items: center;
            margin-right: 50px; /* Aumentado o espaço à direita para maior distância horizontal */
        }

        .arrows button {
            background-color: transparent;
            border: none;
            font-size: 140px; /* Aumentado o tamanho dos símbolos */
            font-weight: bold; /* Tornar as setas mais grossas */
            cursor: pointer;
            color: white;
            text-align: center;
            width: 150px; /* Largura maior */
            height: 150px; /* Altura maior */
            display: flex;
            justify-content: center;
            align-items: center;
            user-select: none;
            margin-top: 170px;
            transition: transform 0.1s ease; /* Transição suave para a transformação */
        }

        .arrows button:focus {
            outline: none;
        }

        /* Efeito ao pressionar o botão */
        .arrows button:active {
            transform: scale(0.7); 
        }

        .sliders {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: flex-start;
            width: 100%;
            max-width: 400px; /* Largura máxima dos sliders */
            margin-top: 10px; /* Espaçamento entre os botões e sliders */
            margin-left: 300px; 
            gap: 20px; /* Espaçamento entre os sliders */
        }

        .sliders label {
            color: white;
            font-size: 20px; /* Tamanho do texto */
            margin-bottom: 10px;
        }

        .sliders input[type="range"] {
            -webkit-appearance: none;
            appearance: none;
            width: 100%;
            height: 15px; /* Espessura dos sliders */
            border-radius: 10px;
            background: white;
            outline: none;
            opacity: 0.8;
            transition: opacity .15s ease-in-out;
        }

        .sliders input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 30px; /* Tamanho do polegar (thumb) */
            height: 30px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
        }

        .sliders input[type="range"]:hover {
            opacity: 1;
        }

        /* Responsividade para dispositivos móveis */
        @media (max-width: 768px) {
            body {
                overflow: hidden; /* Remove a barra lateral em dispositivos móveis */
            }

            .arrows {
                grid-template-columns: repeat(3, 100px); /* Reduz tamanho em telas menores */
                grid-template-rows: repeat(4, 100px);
                gap: 20px; /* Reduz o espaço entre os botões */
                margin-right: 0; /* Remove o espaço à direita em telas pequenas */
            }

            .arrows button {
                font-size: 80px; /* Diminui o tamanho dos botões para telas menores */
                width: 100px;
                height: 100px;
                margin-top: 10px;
            }

            .sliders {
                margin-top: 10px; /* Mantido um espaçamento maior entre botões e sliders */
                gap: 15px; /* Reduz o espaçamento entre os sliders */
                margin-left: 20px; /* Mantido um espaço menor à esquerda em telas pequenas */
                margin-bottom: 100px;
            }
        }

        @media (orientation: landscape) {
            .container {
                flex-direction: row; /* Mantém a direção em linha em telas grandes */
            }
        }
    </style> 
    <!--Fim do CSS-->

    <!--Início do JavaScript-->
    <script>
        const ESP_IP = 'http://192.168.4.1'; // Endereço IP do ESP32

        // Função para enviar comandos de movimento e vibrar
        const sendCommand = (command) => {
            if (navigator.vibrate) {
                navigator.vibrate(100); // Vibra por 100 milissegundos
            }

            fetch(`${ESP_IP}/${command}`)
                .then(response => response.text()) // Resposta do ESP32
                .then(data => {
                    console.log('Response:', data);
                })
                .catch(error => console.error('Error:', error));
        };

        // Função para atualizar sliders
        const updateSlider = (sliderId, value) => {
            fetch(`${ESP_IP}/slider?${sliderId}=${value}`)
                .then(response => response.text()) // Resposta do ESP32
                .then(data => {
                    console.log(`Slider ${sliderId} updated to: ${value}`);
                })
                .catch(error => console.error('Error:', error));
        };
    </script>
   <!--Fim do JavaScript-->

</head>
<!--Fim do head-->

<!--Início do body-->
<body>
    <div class="container">
        <div class="arrows">
            <div></div>
            <button onmousedown="sendCommand('F')"> <!--onmouseup="sendCommand('P')"-->
                <img src="/frente.png" alt="">
            </button> <!-- Seta para cima -->
            <div></div>
            <button onmousedown="sendCommand('E')">
                <img src="/esquerda.png" alt="">
            </button> <!-- Seta para esquerda -->
            <div></div>
            <button onmousedown="sendCommand('D')">
                <img src="/direita.png" alt="">
            </button> <!-- Seta para direita -->
            <div></div>
            <button onmousedown="sendCommand('T')">
                <img src="/tras.png" alt="">
            </button> <!-- Seta para baixo -->
            <div></div>
        </div>

        <div class="sliders">
            <label for="slider1"></label>
            <input id="slider1" type="range" min="0" max="180" value="90" oninput="updateSlider('slider1', this.value)">
            <label for="slider2"></label>
            <input id="slider2" type="range" min="0" max="180" value="90" oninput="updateSlider('slider2', this.value)">
        </div>
    </div>
</body>
<!--Fim do body-->

</html>
<!--Fim do html-->

)rawliteral";
#endif
