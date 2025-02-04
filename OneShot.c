#include <stdio.h>         //Biblioteca padrão do C.
#include "pico/stdlib.h"  //Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   //Biblioteca para gerenciamento de temporizadores e alarmes.

//Definiçãos de pinos
#define PIN_BUTTON 5
#define PIN_LED_GREEN 11
#define PIN_LED_BLUE 12
#define PIN_LED_RED 13

//Variáveis globais
volatile bool fila_leds_ativa = false;
volatile int estado = 0;

//Função para inicializar os pinos dos leds e botão, além da comunicação serial caso necessário
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

//Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_callback(alarm_id_t id, void *user_data){
    if(estado == 0){
        gpio_put(PIN_LED_BLUE, 0);  //Desliga primeiro led
        estado++;       //Incrementa valor do estado para proxima chamada
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);  //Agenda nova chamada para desligar o segundo led
    }else if(estado == 1){
        gpio_put(PIN_LED_RED, 0);   //Desliga segundo led
        estado++;       //Incrementa valor do estado para proxima chamada
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);  //Agenda nova chamada para desligar o terceiro led
    }else if(estado == 2){
        gpio_put(PIN_LED_GREEN, 0);  //Desliga terceiro e último led
        fila_leds_ativa = false;    //Após todos leds desligados, define a fila de leds ativa como falsa
        estado = 0;     //Define ao valor inicial
    }
return 0;
}

//Função para iniciar a fila de leds e agendar a primeira chamada
void iniciar_fila_leds(){
if(fila_leds_ativa){
    return;  //Evita múltiplos acionamentos em caso dos leds já estarem ligados
}

fila_leds_ativa = true; //Define a fila de leds ativa como verdadeira
//Ativa todos leds
gpio_put(PIN_LED_BLUE, 1);
gpio_put(PIN_LED_RED, 1);
gpio_put(PIN_LED_GREEN, 1);

//Primeiro agendamento para desligar o primeiro led
add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}

bool debounce_button(){
static uint32_t last_press_time = 0;    //Ultimo evento em ms
uint32_t current_time = to_us_since_boot(get_absolute_time());  //Obtém o tempo atual em microssegundos
    if(current_time - last_press_time > 200000){ //Debounce de 200ms
        last_press_time = current_time;
        return true;
    }
return false;
}

int main(){
inicializaPinos();  //Inicializa os pinos e comunicação serial, se necessário

while(true){
    if(gpio_get(PIN_BUTTON)==0 && debounce_button()){   //Verifica se o botão foi pressionado com debounce
        iniciar_fila_leds();    //Inicia a fila de leds
    }

    // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
    // Isso evita que o loop seja executado muito rapidamente e consuma recursos desnecessários.
    sleep_ms(10);
}

}