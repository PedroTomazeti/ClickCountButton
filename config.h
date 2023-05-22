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
#define PIN_LED 18
#define PIN_LED_WIFI 2

#define WIFI_SSID "your wifi ssid"
#define WIFI_PASS "your wifi pass"

#define MQTT_URI   "mqtt://your mqtt uri"
#define MQTT_USER  "your user mqtt"
#define MQTT_PASS  "your pass mqtt"

#define MQTT_CLIID "your client id mqtt"

#define TOPIC1 "your topic"

extern QueueHandle_t xQueueSwitch;
extern QueueHandle_t xQueueClicks;

typedef struct {
    int led;
	bool status;
} info_led_t;

typedef struct {
    int clicks;
} info_count_t;

extern info_led_t info_led;
extern info_count_t info_count;

#endif