#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO para cada LED
#define LED_VERDE_GPIO   11
#define LED_VERMELHO_GPIO 13
#define LED_AZUL_GPIO    12

// Estados possíveis para a máquina de estados dos LEDs
typedef enum {
    ESTADO_LED_VERMELHO,
    ESTADO_LED_AZUL,
    ESTADO_LED_VERDE
} EstadoLed;

// Variável global para armazenar o estado atual do ciclo de LEDs
volatile EstadoLed estado_led_atual = ESTADO_LED_VERMELHO;

// Função para configurar a inicialização dos GPIOs
void inicializar_gpios() {
    gpio_init(LED_VERDE_GPIO);
    gpio_init(LED_VERMELHO_GPIO);
    gpio_init(LED_AZUL_GPIO);
    
    gpio_set_dir(LED_VERDE_GPIO, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO_GPIO, GPIO_OUT);
    gpio_set_dir(LED_AZUL_GPIO, GPIO_OUT);
}

// Função de callback para o temporizador repetitivo
bool callback_temporizador(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(LED_VERDE_GPIO, 0);
    gpio_put(LED_VERMELHO_GPIO, 0);
    gpio_put(LED_AZUL_GPIO, 0);

    // Lógica da máquina de estados para controle dos LEDs
    switch(estado_led_atual) {
        case ESTADO_LED_VERMELHO:
            gpio_put(LED_VERMELHO_GPIO, 1);
            printf("LED VERMELHO ativado\n");
            estado_led_atual = ESTADO_LED_AZUL;
            break;
            
        case ESTADO_LED_AZUL:
            gpio_put(LED_AZUL_GPIO, 1);
            printf("LED AZUL ativado\n");
            estado_led_atual = ESTADO_LED_VERDE;
            break;
            
        case ESTADO_LED_VERDE:
            gpio_put(LED_VERDE_GPIO, 1);
            printf("LED VERDE ativado\n");
            estado_led_atual = ESTADO_LED_VERMELHO;
            break;
    }
    return true;
}

int main() {
    stdio_init_all(); // Inicializa comunicação serial
    inicializar_gpios(); // Configura os pinos dos LEDs

    // Configura o temporizador repetitivo para 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, callback_temporizador, NULL, &timer);

    // Loop principal com mensagem periódica
    while(true) {
        sleep_ms(1000);
        
    }

    return 0;
}