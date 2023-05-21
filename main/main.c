#include <stdio.h>
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "..\config.h"
#include "..\components\control_switch\include\control_switch.h"
#include "..\components\control_led\include\control_led.h"
#include "..\components\control_wifi\include\control_wifi.h"

QueueHandle_t xQueueSwitch;

void vTaskSwitch(void *pvParameters);
void vTaskLed(void *pvParameters);
int countClick(int count);
void init_app(void);

void app_main(void) {
    init_app();

    xTaskCreatePinnedToCore( vTaskSwitch, "TaskSwitch", configMINIMAL_STACK_SIZE + 2048, NULL, 4, NULL, CORE_0 );
    xTaskCreatePinnedToCore( vTaskLed, "TaskLed", configMINIMAL_STACK_SIZE + 2048, NULL, 4, NULL, CORE_0 );
    xTaskCreatePinnedToCore( vTaskWifi, "TaskWifi", configMINIMAL_STACK_SIZE + 2048, NULL, 5, NULL, CORE_1);
}

void init_app(void) {
    // initialize NVS
    ESP_ERROR_CHECK(nvs_flash_init());
    initWifi();
    xQueueSwitch = xQueueCreate( 5, sizeof(info_led) );
}