/*
 * Nombres de los integrantes: Rodríguez Barrera Luis Manuel 9379, Rico Zuñiga Jair 9306
 * * Conclusión de la práctica:
El uso avanzado de punteros y pvParameters en FreeRTOS transforma el desarrollo de sistemas embebidos, 
permitiendo crear codigo altamente escalable, limpio y seguro. La modularidad alcanzada facilita el
 mantenimiento, protege los recursos de memoria y valida que un diseño bien estructurado elimina la 
 necesidad de redundancia funcional en sistemas multicanal.
 */
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