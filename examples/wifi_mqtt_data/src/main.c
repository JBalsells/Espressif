#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "mqtt_client.h"

#define WIFI_SSID      "NoSeaShute"
#define WIFI_PASS      "JoyMa@2605!"
#define MQTT_BROKER    "mqtt://192.168.0.49:1883"

static const char *TAG = "APP";
static EventGroupHandle_t s_wifi_evt;
static const int WIFI_OK = BIT0;
static esp_mqtt_client_handle_t client;

static void on_events(void *arg, esp_event_base_t base, int32_t id, void *data) {
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
        ESP_LOGI(TAG, "WiFi START -> connect()");
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "WiFi DISCONNECTED -> retry");
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_evt, WIFI_OK);
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *e = (ip_event_got_ip_t *)data;
        ESP_LOGI(TAG, "Got IP: " IPSTR "  GW: " IPSTR,
                 IP2STR(&e->ip_info.ip), IP2STR(&e->ip_info.gw));
        xEventGroupSetBits(s_wifi_evt, WIFI_OK);
    }
}

static void mqtt_evt(void *h, esp_event_base_t b, int32_t id, void *edata) {
    (void)h; (void)b; (void)edata; // evita warnings si no usas 'edata'
    switch (id) {
        case MQTT_EVENT_CONNECTED:    ESP_LOGI(TAG, "MQTT CONNECTED");    break;
        case MQTT_EVENT_DISCONNECTED: ESP_LOGW(TAG, "MQTT DISCONNECTED"); break;
        case MQTT_EVENT_ERROR:        ESP_LOGE(TAG, "MQTT ERROR");        break;
        default: break;
    }
}

static void wifi_start(void) {
    s_wifi_evt = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &on_events, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &on_events, NULL));

    wifi_config_t wc = {0};
    strncpy((char*)wc.sta.ssid, WIFI_SSID, sizeof(wc.sta.ssid));
    strncpy((char*)wc.sta.password, WIFI_PASS, sizeof(wc.sta.password));
    wc.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wc));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void mqtt_start(void) {
    esp_mqtt_client_config_t cfg = (esp_mqtt_client_config_t){0};
    cfg.broker.address.uri = MQTT_BROKER;
    cfg.session.keepalive = 30;

    client = esp_mqtt_client_init(&cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_evt, NULL);
    ESP_ERROR_CHECK(esp_mqtt_client_start(client));
}


void app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_start();

    xEventGroupWaitBits(s_wifi_evt, WIFI_OK, pdFALSE, pdTRUE, portMAX_DELAY);

    mqtt_start();

    int n = 0;
    while (1) {
        char msg[16];
        snprintf(msg, sizeof msg, "%d", n++);
        int mid = esp_mqtt_client_publish(client, "sensor/contador", msg, 0, 0, 0);
        ESP_LOGI(TAG, "Pub (%d): %s", mid, msg);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
