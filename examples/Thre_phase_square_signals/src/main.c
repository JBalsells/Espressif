#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Pines de salida
#define PHASE_A GPIO_NUM_0
#define PHASE_B GPIO_NUM_2
#define PHASE_C GPIO_NUM_4

// Duración total de un ciclo (en milisegundos)
#define CYCLE_TIME_MS 30  // 30ms = ~33.3Hz
#define PHASE_DELAY_MS (CYCLE_TIME_MS / 3)

// Función que genera 3 señales cuadradas desfasadas 120°
void generate_three_phase_signal(void)
{
    // Configurar los pines como salida
    gpio_set_direction(PHASE_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(PHASE_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(PHASE_C, GPIO_MODE_OUTPUT);

    while (1) {
        // Fase A ON, otras OFF
        gpio_set_level(PHASE_A, 1);
        gpio_set_level(PHASE_B, 0);
        gpio_set_level(PHASE_C, 0);
        vTaskDelay(pdMS_TO_TICKS(PHASE_DELAY_MS));

        // Fase B ON, otras OFF
        gpio_set_level(PHASE_A, 0);
        gpio_set_level(PHASE_B, 1);
        gpio_set_level(PHASE_C, 0);
        vTaskDelay(pdMS_TO_TICKS(PHASE_DELAY_MS));

        // Fase C ON, otras OFF
        gpio_set_level(PHASE_A, 0);
        gpio_set_level(PHASE_B, 0);
        gpio_set_level(PHASE_C, 1);
        vTaskDelay(pdMS_TO_TICKS(PHASE_DELAY_MS));
    }
}

void app_main(void)
{
    generate_three_phase_signal();
}
