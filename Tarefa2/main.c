#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos GPIO
#define LED_VERDE_GPIO     11
#define LED_VERMELHO_GPIO  13
#define LED_AZUL_GPIO      12
#define BOTAO_GPIO         5

// Estados da máquina de estados
typedef enum {
    STATE_LED_AZUL,
    STATE_LED_VERMELHO,
    STATE_LED_VERDE,
    STATE_INICIAL
} EstadoRotina;

// Variáveis de controle
volatile EstadoRotina estado_atual = STATE_INICIAL;
volatile bool rotina_ativa = false;

// Função para configuração inicial dos GPIOs
void inicializar_gpios() {
    // Configuração dos LEDs como saída
    gpio_init(LED_VERDE_GPIO);
    gpio_set_dir(LED_VERDE_GPIO, GPIO_OUT);
    gpio_init(LED_VERMELHO_GPIO);
    gpio_set_dir(LED_VERMELHO_GPIO, GPIO_OUT);
    gpio_init(LED_AZUL_GPIO);
    gpio_set_dir(LED_AZUL_GPIO, GPIO_OUT);

    // Configuração do botão com pull-up
    gpio_init(BOTAO_GPIO);
    gpio_set_dir(BOTAO_GPIO, GPIO_IN);
    gpio_pull_up(BOTAO_GPIO);
}

// Callback para tratamento da rotina de temporização
int64_t tratar_rotina(alarm_id_t id, void *user_data) {
    switch(estado_atual) {
        case STATE_LED_AZUL:
            gpio_put(LED_AZUL_GPIO, false);
            printf("Estado 1: LED Azul desligado\n");
            estado_atual = STATE_LED_VERMELHO;
            add_alarm_in_ms(3000, tratar_rotina, NULL, false);
            break;

        case STATE_LED_VERMELHO:
            gpio_put(LED_VERMELHO_GPIO, false);
            printf("Estado 2: LED Vermelho desligado\n");
            estado_atual = STATE_LED_VERDE;
            add_alarm_in_ms(3000, tratar_rotina, NULL, false);
            break;

        case STATE_LED_VERDE:
            gpio_put(LED_VERDE_GPIO, false);
            printf("Estado 3: LED Verde desligado\n");
            rotina_ativa = false;
            estado_atual = STATE_INICIAL;
            break;

        default:
            break;
    }
    return 0;
}

int main() {
    stdio_init_all();
    inicializar_gpios();

    while(true) {
        // Verifica pressionamento do botão com debounce
        if(gpio_get(BOTAO_GPIO) == 0 && !rotina_ativa) {
            sleep_ms(50); // Debounce
            if(gpio_get(BOTAO_GPIO) == 0) {
                // Inicia sequência de LEDs
                gpio_put(LED_VERDE_GPIO, true);
                gpio_put(LED_VERMELHO_GPIO, true);
                gpio_put(LED_AZUL_GPIO, true);
                
                printf("Botão pressionado: Iniciando sequência\n");
                
                rotina_ativa = true;
                estado_atual = STATE_LED_AZUL;
                add_alarm_in_ms(3000, tratar_rotina, NULL, false);
            }
        }
        sleep_ms(10); // Reduz consumo de CPU
    }
    return 0;
}