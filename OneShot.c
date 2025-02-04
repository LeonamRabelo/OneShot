#include <stdio.h>
#include "pico/stdlib.h"

#define PIN_BUTTON 5
#define PIN_LED_GREEN 11
#define PIN_LED_BLUE 12
#define PIN_LED_RED 13

volatile bool fila_leds_ativa = false;
volatile int estado = 0;

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

int64_t turn_off_callback(alarm_id_t id, void *user_data){
if(estado == 0){
    gpio_put(PIN_LED_BLUE, 0);
    estado++;
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);  //Agenda nova chamada para desligar o segundo led
}else if(estado == 1){
    gpio_put(PIN_LED_RED, 0);
    estado++;
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}else if(estado == 2){
    gpio_put(PIN_LED_GREEN, 0);
    fila_leds_ativa = false;
    estado = 0;
}
return 0;
}

void iniciar_fila_leds(){
if(fila_leds_ativa){
    return;  //Evita múltiplos acionamentos
}

fila_leds_ativa = true;
gpio_put(PIN_LED_BLUE, 1);
gpio_put(PIN_LED_RED, 1);
gpio_put(PIN_LED_GREEN, 1);

//Primeira chamada para desligar o primeiro led
add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}

bool debounce_button() {
static uint32_t last_press_time = 0;
uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if(current_time - last_press_time > 200){ // Debounce de 200ms
        last_press_time = current_time;
        return true;
    }
return false;
}

int main(){
inicializaPinos();

while(true){
    if(gpio_get(PIN_BUTTON)==0 && debounce_button()){
        iniciar_fila_leds();
    }

    sleep_ms(10);
}

}