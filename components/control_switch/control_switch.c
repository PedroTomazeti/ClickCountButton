#include <stdio.h>
#include "control_switch.h"
#include "..\..\..\config.h"

info_led_t info_status_led;

int countClick(int count);
int count = 0;

void configureSwitch(int pin_switch) {
    gpio_reset_pin(pin_switch);
    gpio_set_direction(pin_switch, GPIO_MODE_INPUT);
}

void vTaskSwitch(void *pvParameters) {
    configureSwitch(PIN_SWITCH);

    bool status_led = false;
    int last_status = 1;

    while(true) {
        int status_switch = gpio_get_level(PIN_SWITCH);

        // printf("\nSwitch: %d", status_switch);
        if (status_switch != 1 && last_status != status_switch) {
            status_led = !status_led;
            info_status_led.led = PIN_LED;
            info_status_led.status = status_led;

            xQueueSend(xQueueSwitch, &info_status_led, portMAX_DELAY);
            count = countClick(count);
        }
        last_status = status_switch;
        vTaskDelay( 275 / portTICK_PERIOD_MS );
    }
}

int countClick (int count){
    if (info_status_led.status == true) {
        count++;
        printf("O LED acendeu %d vez(es).\n", count);
    }
    return count;
}