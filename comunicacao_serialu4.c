/**
 * Programa principal para controle de LEDs, Display e Comunicação Serial
 * Projeto: Comunicação Serial - Unidade 4
 */

 #include <stdio.h>
 #include <ctype.h>
 #include "pico/stdlib.h"
 #include "hardware/pio.h"
 #include "hardware/i2c.h"
 #include "pio_matrix.pio.h"
 #include "Bibliotecas/led_matriz.h"
 #include "Bibliotecas/ssd1306.h"
 #include "Bibliotecas/font.h"
 #include "hardware/clocks.h"
 
 // Definições dos pinos
 #define LED_VERDE 11    // LED RGB - Verde
 #define LED_AZUL 12     // LED RGB - Azul
 #define BOTAO_A 5       // Botão A
 #define BOTAO_B 6       // Botão B
 #define MATRIZ_PIN 7    // Matriz de LEDs 5x5
 #define I2C_SDA 14      // Display - SDA
 #define I2C_SCL 15      // Display - SCL
 
 // Configurações do Display
 #define I2C_PORT i2c1
 #define DISPLAY_ADDR 0x3C
 
 // Variáveis Globais
 volatile bool led_verde_estado = false;
 volatile bool led_azul_estado = false;
 ssd1306_t display;
 
 // Função para tratar o debounce dos botões
 void tratamento_botao(uint gpio, uint32_t eventos) {
     static absolute_time_t ultimo_pressionar = 0;
     absolute_time_t tempo_atual = get_absolute_time();
 
     // Debounce de 200ms
     if (absolute_time_diff_us(ultimo_pressionar, tempo_atual) > 200000) {
         if (gpio == BOTAO_A) {
             led_verde_estado = !led_verde_estado;
             gpio_put(LED_VERDE, led_verde_estado);
             
             // Atualiza display e Serial
             ssd1306_fill(&display, false);
             if (led_verde_estado) {
                 ssd1306_draw_string(&display, "LED Verde LIGADO", 20, 28);
                 printf("LED Verde foi ligado!\n");
             } else {
                 ssd1306_draw_string(&display, "LED Verde DESLIGADO", 15, 28);
                 printf("LED Verde foi desligado!\n");
             }
             ssd1306_send_data(&display);
         }
         
         if (gpio == BOTAO_B) {
             led_azul_estado = !led_azul_estado;
             gpio_put(LED_AZUL, led_azul_estado);
             
             // Atualiza display e Serial
             ssd1306_fill(&display, false);
             if (led_azul_estado) {
                 ssd1306_draw_string(&display, "LED Azul LIGADO", 20, 28);
                 printf("LED Azul foi ligado!\n");
             } else {
                 ssd1306_draw_string(&display, "LED Azul DESLIGADO", 15, 28);
                 printf("LED Azul foi desligado!\n");
             }
             ssd1306_send_data(&display);
         }
         
         ultimo_pressionar = tempo_atual;
     }
 }
 
 // Função de inicialização
 void inicializar() {
     // Configura LEDs
     gpio_init(LED_VERDE);
     gpio_init(LED_AZUL);
     gpio_set_dir(LED_VERDE, GPIO_OUT);
     gpio_set_dir(LED_AZUL, GPIO_OUT);
     
     // Configura Botões
     gpio_init(BOTAO_A);
     gpio_init(BOTAO_B);
     gpio_set_dir(BOTAO_A, GPIO_IN);
     gpio_set_dir(BOTAO_B, GPIO_IN);
     gpio_pull_up(BOTAO_A);
     gpio_pull_up(BOTAO_B);
     
     // Configura interrupções dos botões
     gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &tratamento_botao);
     gpio_set_irq_enabled(BOTAO_B, GPIO_IRQ_EDGE_FALL, true);
 
     // Configura I2C para o Display
     i2c_init(I2C_PORT, 400000);
     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
     gpio_pull_up(I2C_SDA);
     gpio_pull_up(I2C_SCL);
 
     // Inicializa Display
     ssd1306_init(&display, WIDTH, HEIGHT, false, DISPLAY_ADDR, I2C_PORT);
     ssd1306_config(&display);
     ssd1306_fill(&display, false);
     ssd1306_draw_string(&display, "Sistema Iniciado!", 20, 28);
     ssd1306_send_data(&display);
 }
 
 int main() {
     // Inicializa PIO para matriz
     PIO pio = pio0;
     uint sm = 0;
     uint offset = pio_add_program(pio, &pio_matrix_program);
     pio_matrix_program_init(pio, sm, offset, MATRIZ_PIN);
 
     // Inicialização geral
     inicializar();
     stdio_init_all();
 
     printf("Sistema Iniciado - Aguardando comandos...\n");
 
     while (true) {
         if (stdio_usb_connected()) {
             char caractere = getchar();
             
             ssd1306_fill(&display, false);
 
             if (isdigit(caractere)) {
                 // Se for número, mostra na matriz e no display
                 imprimir_num(caractere, pio, sm);
                 ssd1306_draw_char(&display, caractere, 60, 28);
                 printf("Numero recebido: %c\n", caractere);
             } else if (isalpha(caractere)) {
                 // Se for letra, limpa matriz e mostra no display
                 apagar_leds(pio, sm);
                 ssd1306_draw_char(&display, caractere, 60, 28);
                 printf("Letra recebida: %c\n", caractere);
             }
             
             ssd1306_send_data(&display);
         }
         sleep_ms(10);
     }
 }