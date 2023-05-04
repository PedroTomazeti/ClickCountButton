#include <stdio.h>
#include "..\config.h"
#include "..\components\control_switch\include\control_switch.h"
#include "..\components\control_led\include\control_led.h"

QueueHandle_t xQueueSwitch;

void vTaskSwitch(void *pvParameters);
void vTaskLed(void *pvParameters);
int countClick(int count);

void init_app(void) {
    xQueueSwitch = xQueueCreate( 5, sizeof(info_led) );
}

void app_main(void) {
    init_app();

    xTaskCreatePinnedToCore( vTaskSwitch, "TaskSwitch", configMINIMAL_STACK_SIZE + 2048, NULL, 4, NULL, CORE_0 );
    xTaskCreatePinnedToCore( vTaskLed, "TaskLed", configMINIMAL_STACK_SIZE + 2048, NULL, 4, NULL, CORE_0 );
}

