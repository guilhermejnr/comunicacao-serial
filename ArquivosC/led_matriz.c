#include "led_matriz.h"

// Número 0 - Formato de O mais claro
double num0[25] = {
    0,1,1,1,0,
    0,1,0,1,0,
    0,1,0,1,0,
    0,1,0,1,0,
    0,1,1,1,0
};

// Número 1 - Barra central mais grossa
double num1[25] = {
    0,0,1,0,0,
    0,1,1,0,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,1,1,1,0
};

// Número 2 - Forma mais clara
double num2[25] = {
    0,1,1,1,0,
    0,0,0,1,0,
    0,1,1,1,0,
    0,1,0,0,0,
    0,1,1,1,0
};

// Número 3 - Três traços mais visíveis
double num3[25] = {
    0,1,1,1,0,
    0,0,0,1,0,
    0,1,1,1,0,
    0,0,0,1,0,
    0,1,1,1,0
};

// Número 4 - Formato mais legível
double num4[25] = {
    0,1,0,1,0,
    0,1,0,1,0,
    0,1,1,1,0,
    0,0,0,1,0,
    0,0,0,1,0
};

// Número 5 - S mais claro
double num5[25] = {
    0,1,1,1,0,
    0,1,0,0,0,
    0,1,1,1,0,
    0,0,0,1,0,
    0,1,1,1,0
};

// Número 6
double num6[25] = {
    0,1,1,1,0,
    0,1,0,0,0,
    0,1,1,1,0,
    0,1,0,1,0,
    0,1,1,1,0
};

// Número 7 - Mais legível
double num7[25] = {
    0,1,1,1,0,
    0,0,0,1,0,
    0,0,1,0,0,
    0,1,0,0,0,
    0,1,0,0,0
};

// Número 8 - Formato de 8 mais claro
double num8[25] = {
    0,1,1,1,0,
    0,1,0,1,0,
    0,1,1,1,0,
    0,1,0,1,0,
    0,1,1,1,0
};

// Número 9
double num9[25] = {
    0,1,1,1,0,
    0,1,0,1,0,
    0,1,1,1,0,
    0,0,0,1,0,
    0,1,1,1,0
};

// Função para converter valores RGB
uint32_t matrix_rgb(double r, double g, double b) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para apagar todos os LEDs
void apagar_leds(PIO pio, uint sm) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(0, 0, 0));
    }
}

// Função para acender todos os LEDs
void acender_leds(PIO pio, uint sm, double r, double g, double b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(r, g, b));
    }
}

// Função para desenhar na matriz
void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b) {
    for(int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(desenho[i] * r, desenho[i] * g, desenho[i] * b));
    }
}

// Função para mostrar número
void imprimir_num(char caractere, PIO pio, uint sm) {
    // Verde com intensidade reduzida
    double r = 0.0;
    double g = 0.3; // Reduzido de 1.0 para 0.3 (30% do brilho máximo)
    double b = 0.0;
    
    switch(caractere) {
        case '0': desenho_pio(num0, pio, sm, r, g, b); break;
        case '1': desenho_pio(num1, pio, sm, r, g, b); break;
        case '2': desenho_pio(num2, pio, sm, r, g, b); break;
        case '3': desenho_pio(num3, pio, sm, r, g, b); break;
        case '4': desenho_pio(num4, pio, sm, r, g, b); break;
        case '5': desenho_pio(num5, pio, sm, r, g, b); break;
        case '6': desenho_pio(num6, pio, sm, r, g, b); break;
        case '7': desenho_pio(num7, pio, sm, r, g, b); break;
        case '8': desenho_pio(num8, pio, sm, r, g, b); break;
        case '9': desenho_pio(num9, pio, sm, r, g, b); break;
        default: break;
    }
}