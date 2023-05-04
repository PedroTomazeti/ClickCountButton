#include <stdio.h>
#include "control_led.h"
#include "..\..\..\config.h"

info_led_t info_status_led;

void configureLed(int pin_led) {
    gpio_reset_pin(pin_led);
    gpio_set_direction(pin_led, GPIO_MODE_OUTPUT);
}

void vTaskLed(void *pvParameters) {

    while(true) {
        xQueueReceive(xQueueSwitch, &info_status_led, portMAX_DELAY);

        int led = info_status_led.led;
        bool status = info_status_led.status;

        configureLed(led);

        gpio_set_level(led, status);
        printf("Status Led: %d\n", status);
    }
}
