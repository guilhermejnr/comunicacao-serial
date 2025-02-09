/**
 * Biblioteca para controle da matriz de LEDs
 */

 #ifndef LED_MATRIZ_H
 #define LED_MATRIZ_H
 
 #include "hardware/pio.h"
 
 // Definições
 #define NUM_PIXELS 25
 #define MATRIZ_5X5 7
 
 // Funções da biblioteca
 uint32_t matrix_rgb(double r, double g, double b);
 void apagar_leds(PIO pio, uint sm);
 void acender_leds(PIO pio, uint sm, double r, double g, double b);
 void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b);
 void imprimir_num(char caractere, PIO pio, uint sm);
 
 #endif // LED_MATRIZ_H