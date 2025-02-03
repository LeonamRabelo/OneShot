#include <stdio.h>
#include "pico/stdlib.h"

#define PIN_BUTTON 5
#define PIN_LED_BLUE 12
#define PIN_LED_RED 13
#define PIN_LED_GREEN 11

void inicializaPinos(){
    stdio_init_all();

    //BOTAO
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_up(PIN_BUTTON);

    //LEDS
    gpio_init(PIN_LED_BLUE);
    gpio_set_dir(PIN_LED_BLUE, GPIO_OUT);
    gpio_put(PIN_LED_BLUE, 0);

    gpio_init(PIN_LED_GREEN);
    gpio_set_dir(PIN_LED_GREEN, GPIO_OUT);
    gpio_put(PIN_LED_GREEN, 0);

    gpio_init(PIN_LED_RED);
    gpio_set_dir(PIN_LED_RED, GPIO_OUT);
    gpio_put(PIN_LED_RED, 0);
}

int main()
{
    inicializaPinos();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
