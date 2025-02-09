# Projeto de Comunicação Serial - Embarcatech

Projeto desenvolvido para a disciplina de Sistemas Embarcados do curso Embarcatech, utilizando a placa BitDogLab.

## 📝 Descrição

Este projeto implementa um sistema de comunicação serial que integra diversos componentes:
- Matriz de LEDs WS2812 5x5
- Display OLED SSD1306
- LED RGB
- Botões de controle

### Funcionalidades

- ✨ Exibição de números (0-9) na matriz de LEDs e no display OLED
- 📝 Exibição de letras no display OLED
- 🎮 Controle de LEDs RGB através de botões
- 🔄 Comunicação serial via USB

## 🛠️ Componentes Utilizados

- Placa BitDogLab (Raspberry Pi Pico W)
- Matriz 5x5 WS2812 (GPIO 7)
- Display OLED SSD1306 via I2C (GPIO 14 e 15)
- LED RGB (GPIOs 11, 12 e 13)
- 2 Botões (GPIOs 5 e 6)

## Vídeo demonstrativo:

https://drive.google.com/uc?id=1ypUMNau5cq5APxYjEs_AwDcalmjkqLnI&export=download

## 🔧 Instalação

1. Clone o repositório:
\`\`\`bash
git clone https://github.com/guilhermejnr/comunicacao-serial.git
\`\`\`

2. Configure o ambiente de desenvolvimento:
   - Instale o VS Code
   - Instale a extensão "Raspberry Pi Pico W"
   - Configure o SDK do Pico

3. Compile o projeto:
\`\`\`bash
mkdir build
cd build
cmake ..
make
\`\`\`

## 📊 Uso

1. Conecte a placa BitDogLab ao computador via USB
2. Carregue o programa compilado
3. Abra o Serial Monitor (115200 baud)
4. Interaja com o sistema:
   - Digite números (0-9) para ver na matriz LED e display
   - Digite letras para ver no display
   - Use os botões para controlar o LED RGB

## 🎮 Controles

- **Botão A (GPIO 5)**: Controla o LED Verde
- **Botão B (GPIO 6)**: Controla o LED Azul

## 🤝 Contribuição

Contribuições são bem-vindas! Para contribuir:
1. Faça um Fork do projeto
2. Crie uma Branch para sua Feature (\`git checkout -b feature/MinhaFeature\`)
3. Commit suas mudanças (\`git commit -m 'Adicionando nova feature'\`)
4. Push para a Branch (\`git push origin feature/MinhaFeature\`)
5. Abra um Pull Request

## ✍️ Autor

Guilherme Jr. - [Github](https://github.com/guilhermejnr)



