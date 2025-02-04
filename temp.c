#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define led_green 11
#define led_blue 12
#define led_red 13

int estado = 1;
bool semaforo_callback(struct repeating_timer *t){

    gpio_put(led_green, 0);
    gpio_put(led_blue, 0);
    gpio_put(led_red, 0);

    switch (estado){

    case 1:
        gpio_put(led_red, 1);
        printf("Sinal vermelho ligado!");
        estado = 2;
        break;

     case 2:
        gpio_put(led_blue, 1);
        printf("Sinal amarelo(led azul) ligado!");
        estado = 3;
        break;

    case 3:
        gpio_put(led_green, 1);
        printf("Sinal verde ligado!");
        estado = 1;
        break;
    
    default:
        break;
    }
    return 1;
}
int main()
{
    stdio_init_all();

    gpio_init(led_green);
    gpio_set_dir(led_green, GPIO_OUT);

    gpio_init(led_blue);
    gpio_set_dir(led_blue, GPIO_OUT);

    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);

    // Variável do timer
    repeating_timer_t timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    while (true) {
        // Pausa de 10 segundos para reduzir o uso da CPU.
        sleep_ms(10000);
    }
}
