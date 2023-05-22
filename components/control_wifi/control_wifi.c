#include <stdio.h>
#include "control_wifi.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "..\..\config.h"
#include "..\control_led\include\control_led.h"
#include "..\control_mqtt\include\control_mqtt.h"

#include "lwip/err.h"
#include "lwip/sys.h"

// configure the wifi connection and start the interface
wifi_config_t wifi_config = {
    .sta = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASS,
    },
};

void startWifi();

// Event group
static EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;

// led
info_led_t info_status_led;

// Wifi event handler
static esp_err_t event_handler(void *ctx, system_event_t *event) {
  switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
      	esp_wifi_connect();
      	break;

    case SYSTEM_EVENT_STA_GOT_IP:
      	xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        mqtt_app_start();
      	break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
      	xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        printf("[DESCONNECTED] %s!\n", WIFI_SSID);
        configureLed(PIN_LED_WIFI);
        gpio_set_level(PIN_LED_WIFI, false);
      	break;

    default:
      	break;
  }

  return ESP_OK;
}

void vTaskWifi(void *pvParameter) {
    tcpip_adapter_ip_info_t ip_info;

    // wait for connection
    startWifi();
    printf("[CONNECTING] Wait to connect wifi network...\n");

    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    printf("[CONNECTED] %s!\n", WIFI_SSID);

    // red led on when wifi connected
    configureLed(PIN_LED_WIFI);
    gpio_set_level(PIN_LED_WIFI, true);

    // print the local IP address
    ESP_ERROR_CHECK(tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info));
    printf("[IP]      %s\n", ip4addr_ntoa(&ip_info.ip));
    printf("[MASK]    %s\n", ip4addr_ntoa(&ip_info.netmask));
    printf("[GATEWAY] %s\n", ip4addr_ntoa(&ip_info.gw));

    while (true) {
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}

void startWifi(){
    // start the main task
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    printf("[CONNECTING] %s\n", WIFI_SSID);
}

void initWifi() {
    printf("ESP-IDF version used: ");
    printf(IDF_VER"\n");
    // disable the default wifi logging
    esp_log_level_set("wifi", ESP_LOG_NONE);

    // create the event group to handle wifi events
    wifi_event_group = xEventGroupCreate();

    // initialize the tcp stack
    tcpip_adapter_init();

    // initialize the wifi event handler
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    // initialize the wifi stack in STAtion mode with config in RAM
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
}