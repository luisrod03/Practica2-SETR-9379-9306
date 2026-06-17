#include "tasks.h"
#include "adc_reader.h"
#include "leds.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TASKS";

static const task_params_t params_ch0 = {
    .adc_channel = 0,
    .led_channel = 0,
    .name        = "POT0-LED0",
};

static const task_params_t params_ch1 = {
    .adc_channel = 1,
    .led_channel = 1,
    .name        = "POT1-LED1",
};

static const task_params_t params_ch2 = {
    .adc_channel = 2,
    .led_channel = 2,
    .name        = "POT2-LED2",
};

static TaskHandle_t s_task_handles[3] = { NULL, NULL, NULL };

/* Funcion de tarea */
void vTaskPotLED(void *pvParameters)
{
    const task_params_t *cfg = (const task_params_t *)pvParameters;
    uint32_t cycle_count = 0U;

    ESP_LOGI(TAG, "[%s] Tarea iniciada (ADC ch%u -> LED ch%u)",
             cfg->name, cfg->adc_channel, cfg->led_channel);

    for (;;)
    {
        uint16_t raw = adc_reader_get_raw(cfg->adc_channel);

        uint8_t duty = (uint8_t)((raw * 255) / 4095);

        leds_set_duty(cfg->led_channel, duty);

        cycle_count++;
        if ((cycle_count % 20) == 0) {
            uint32_t heap_free = xPortGetFreeHeapSize();
            UBaseType_t wm = uxTaskGetStackHighWaterMark(NULL);
            
            ESP_LOGI(TAG, "[%s] raw=%u duty=%u heap=%lu wm=%u",
                     cfg->name, raw, duty, (unsigned long)heap_free, (unsigned int)wm);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }

    vTaskDelete(NULL);
}

void tasks_create_all(void)
{
    BaseType_t ret;

    ret = xTaskCreate(vTaskPotLED, "PotLED_0", 2048, (void *)&params_ch0, 1, &s_task_handles[0]);
    configASSERT(ret == pdPASS);

    ret = xTaskCreate(vTaskPotLED, "PotLED_1", 2048, (void *)&params_ch1, 2, &s_task_handles[1]);
    configASSERT(ret == pdPASS);

    ret = xTaskCreate(vTaskPotLED, "PotLED_2", 2048, (void *)&params_ch2, 3, &s_task_handles[2]);
    configASSERT(ret == pdPASS);

    ESP_LOGI(TAG, "Tres tareas creadas correctamente");
}