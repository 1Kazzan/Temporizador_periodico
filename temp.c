#include <stdio.h>
#include "pico/stdlib.h" // biblioteca padrão para trabalhar com a raspberry pi pico
#include "hardware/timer.h" //biblioteca para gerenciamento de temporizadores de hardware.

// definir pinos GPIOs para os leds rgb
#define led_green 11
#define led_blue 12
#define led_red 13

// variável que indica o estado atual do semáforo
int estado = 1;

// função callback chamada automaticamente pelo temporizador para alternar o estado do semáforo
bool semaforo_callback(struct repeating_timer *t){

//switch para alternar entre os estados do semáforo
    switch (estado){

    case 1: // apenas o led vermelho ligado
        gpio_put(led_green, 0);
        gpio_put(led_blue, 0);
        gpio_put(led_red, 1);
        printf("Sinal vermelho ligado!");
        estado = 2; // deixa pronto o caso do proximo estado
        break;

     case 2: // apenas o led azul ligado
        gpio_put(led_green, 0);
        gpio_put(led_blue, 1);
        gpio_put(led_red, 0);
        printf("Sinal amarelo(led azul) ligado!");
        estado = 3; // deixa pronto o caso do proximo estado
        break;

    case 3: // apenas o led verde ligado
        gpio_put(led_green, 1);
        gpio_put(led_blue, 0);
        gpio_put(led_red, 0);
        printf("Sinal verde ligado!");
        estado = 1; // deixa pronto o caso do proximo estado
        break;
    
    default:
        break;
    }
    return 1; //retorna verdadeiro para manter o temporizador ativo
}
int main(){
// permite comuniação serial e uso de printf
    stdio_init_all();

// inicia os pinos GPIOs dos leds
    gpio_init(led_green);
    gpio_set_dir(led_green, GPIO_OUT);

    gpio_init(led_blue);
    gpio_set_dir(led_blue, GPIO_OUT);

    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);

    // Variável do timer
    repeating_timer_t timer;
    // a função callback é configurada para ser chamada a cada 3 segundos
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);
    // loop infinito que mantém o programa em execução.
    while (true) {
        // Pausa de 10 segundos para reduzir o uso da CPU.
        sleep_ms(10000);
    }
    return 0;
}
