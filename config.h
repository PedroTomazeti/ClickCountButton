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

#define WIFI_SSID "WEBNET - AP104"
#define WIFI_PASS "#W3bD3v#"

#define MQTT_URI   "mqtt://34.229.145.165:1883"
#define MQTT_USER  "autohome"
#define MQTT_PASS  "comida05"

#define MQTT_CLIID "grupo1"

#define TOPIC1 "/engcomp/button/0101"

extern QueueHandle_t xQueueSwitch;

typedef struct {
    int led;
	bool status;
} info_led_t;

typedef struct {
    int count;
} info_count_t;

extern info_led_t info_led;
extern info_count_t info_count;

#endif