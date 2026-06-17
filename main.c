#include "adc_reader.h"
#include "leds.h"
#include "tasks.h"

void app_main(void)
{
    /* 1. Inicializar subsistema ADC (tres potenciometros) */
    adc_reader_init();
    
    /* 2. Inicializar subsistema LED PWM (tres canales LEDC) */
    leds_init();
    
    /* 3. Crear las tres tareas FreeRTOS e iniciar el scheduler */
    tasks_create_all();
}