/*
 * Example of using esp-homekit library to control
 * a simple $5 Sonoff Basic using HomeKit.
 * The esp-wifi-config library is also used in this
 * example. This means you don't have to specify
 * your network's SSID and password before building.
 *
 * In order to flash the sonoff basic you will have to
 * have a 3,3v (logic level) FTDI adapter.
 *
 * To flash this example connect 3,3v, TX, RX, GND
 * in this order, beginning in the (square) pin header
 * next to the button.
 * Next hold down the button and connect the FTDI adapter
 * to your computer. The sonoff is now in flash mode and
 * you can flash the custom firmware.
 *
 * WARNING: Do not connect the sonoff to AC while it's
 * connected to the FTDI adapter! This may fry your
 * computer and sonoff.
 *
 */

#include <stdio.h>
#include <espressif/esp_wifi.h>
#include <espressif/esp_sta.h>
#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi_config.h>

#include "button.h"

// The GPIO pin that is connected to the relay on the Sonoff Basic.
const int relay_gpio = 12;
// The GPIO pin that is connected to the LED on the Sonoff Basic.
const int led_gpio = 13;
// The GPIO pin that is oconnected to the button on the Sonoff Basic.
const int button_gpio = 0;

void switch_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context);
void button_callback(uint8_t gpio, button_event_t event);

void led_write(bool on) {
    gpio_write(led_gpio, on ? 0 : 1);
}

void relay_write(bool on) {
    gpio_write(relay_gpio, on ? 1 : 0);
    led_write(on);
}

bool led_read() {
    return gpio_read(led_gpio);
}

void led_blink(int times) {
    bool led_value = led_read();
    for (int i=0; i<times; i++) {
        led_write(true);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        led_write(false);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    led_write(led_value);
}

void reset_configuration_task() {
    //Flash the LED first before we start the reset
    led_blink(3);
    
    printf("Resetting HomeKit Config\n");
    
    homekit_server_reset();
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    printf("Resetting Wifi Config\n");
    
    wifi_config_reset();
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    printf("Restarting\n");
    
    sdk_system_restart();
    
    vTaskDelete(NULL);
}

void reset_configuration() {
    printf("Resetting Sonoff configuration\n");
    xTaskCreate(reset_configuration_task, "Reset configuration", 256, NULL, 2, NULL);
}

homekit_characteristic_t switch_on = HOMEKIT_CHARACTERISTIC_(
    ON, false, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(switch_on_callback)
);

void gpio_init() {
    gpio_enable(led_gpio, GPIO_OUTPUT);
    gpio_enable(relay_gpio, GPIO_OUTPUT);
    relay_write(switch_on.value.bool_value);
}

void switch_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context) {
    relay_write(switch_on.value.bool_value);
}

void set_relay_value(bool value) {
    printf("Relay Value: %d\n", value);
    switch_on.value.bool_value = value;
    relay_write(value);
    homekit_characteristic_notify(&switch_on, switch_on.value);
}

void button_callback(uint8_t gpio, button_event_t event) {
    switch (event) {
        case button_event_single_press:
            printf("Toggling relay\n");
            set_relay_value(!switch_on.value.bool_value);
            break;
        case button_event_long_press:
            reset_configuration();
            break;
        default:
            printf("Unknown button event: %d\n", event);
    }
}

void switch_identify_task(void *_args) {
    // We identify the Sonoff by Flashing it's LED.
    for (int i=0; i<3; i++) {
        led_blink(2);
    }

    vTaskDelete(NULL);
}

void switch_identify(homekit_value_t _value) {
    printf("Switch identify\n");
    xTaskCreate(switch_identify_task, "Switch identify", 128, NULL, 2, NULL);
}

homekit_characteristic_t name = HOMEKIT_CHARACTERISTIC_(NAME, "Sonoff Switch");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]){
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]){
            &name,
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Gruppio"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "037A2BABF19D"),
            HOMEKIT_CHARACTERISTIC(MODEL, "Basic"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, switch_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Sonoff Switch"),
            &switch_on,
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"
};

void on_wifi_ready() {
    homekit_server_init(&config);
}

void create_accessory_name() {
    uint8_t macaddr[6];
    sdk_wifi_get_macaddr(STATION_IF, macaddr);
    
    int name_len = snprintf(NULL, 0, "Sonoff Switch-%02X%02X%02X",
                            macaddr[3], macaddr[4], macaddr[5]);
    char *name_value = malloc(name_len+1);
    snprintf(name_value, name_len+1, "Sonoff Switch-%02X%02X%02X",
             macaddr[3], macaddr[4], macaddr[5]);
    
    name.value = HOMEKIT_STRING(name_value);
}

void user_init(void) {
    uart_set_baud(0, 115200);

    create_accessory_name();
    
    wifi_config_init("sonoff-switch", NULL, on_wifi_ready);
    gpio_init();

    if (button_create(button_gpio, 0, 4000, button_callback)) {
        printf("Failed to initialize button\n");
    }

    set_relay_value(true);
}
