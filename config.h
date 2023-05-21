#ifndef __CONFIG__H__
#define __CONFIG__H__

#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define CORE_0 0
#define CORE_1 1
#define PIN_SWITCH 19
#define PIN_LED 2
#define PIN_LED_WIFI 18

#define WIFI_SSID "your wifi ssid"
#define WIFI_PASS "your wifi pass" // In this commit I almost leaked my wifi password xD

extern QueueHandle_t xQueueSwitch;

typedef struct {
    int led;
	bool status;
} info_led_t;

extern info_led_t info_led;
#endif