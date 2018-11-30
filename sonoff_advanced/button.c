#include <string.h>
#include <esplibs/libmain.h>
#include "button.h"

typedef struct _button {
    uint8_t gpio_num;
    button_callback_fn callback;

    uint16_t debounce_time;
    uint16_t long_press_time;

    bool pressed_value;

    uint32_t last_press_time;
    uint32_t last_event_time;

    struct _button *next;
} button_t;


button_t *buttons = NULL;


static button_t *button_find_by_gpio(const uint8_t gpio_num) {
    button_t *button = buttons;
    while (button && button->gpio_num != gpio_num)
        button = button->next;

    return button;
}


void button_intr_callback(uint8_t gpio) {
    button_t *button = button_find_by_gpio(gpio);
    if (!button)
        return;

    uint32_t now = xTaskGetTickCountFromISR();
    if ((now - button->last_event_time)*portTICK_PERIOD_MS < button->debounce_time) {
        // debounce time, ignore events
        button->last_press_time = 0;
        return;
    }
    button->last_event_time = now;
    if (gpio_read(button->gpio_num) == button->pressed_value) {
        // Record when the button is pressed down.
        button->last_press_time = now;
    } else {
        // The button is released. Handle the use cases.
        if ((now - button->last_press_time) * portTICK_PERIOD_MS > button->long_press_time) {
         	if (button->last_press_time > 0)
            	{
            	button->callback(button->gpio_num, button_event_long_press);
            	button->last_press_time = 0;
            	}
        } else {
            if (button->last_press_time > 0)
            	{
            	button->callback(button->gpio_num, button_event_single_press);
            	button->last_press_time = 0;
            	}
        }
    }
}

int button_create(const uint8_t gpio_num, bool pressed_value, uint16_t long_press_time, button_callback_fn callback) {
    button_t *button = button_find_by_gpio(gpio_num);
    if (button)
        return -1;

    button = malloc(sizeof(button_t));
    memset(button, 0, sizeof(*button));
    button->gpio_num = gpio_num;
    button->callback = callback;
    button->pressed_value = pressed_value;

    // times in milliseconds
    button->debounce_time = 50;
    button->long_press_time = long_press_time;

    uint32_t now = xTaskGetTickCountFromISR();
    button->last_event_time = now;
    button->last_press_time = 0;

    button->next = buttons;
    buttons = button;

    gpio_set_pullup(button->gpio_num, true, true);
    gpio_set_interrupt(button->gpio_num, GPIO_INTTYPE_EDGE_ANY, button_intr_callback);

    return 0;
}


void button_delete(const uint8_t gpio_num) {
    if (!buttons)
        return;

    button_t *button = NULL;
    if (buttons->gpio_num == gpio_num) {
        button = buttons;
        buttons = buttons->next;
    } else {
        button_t *b = buttons;
        while (b->next) {
            if (b->next->gpio_num == gpio_num) {
                button = b->next;
                b->next = b->next->next;
                break;
            }
        }
    }

    if (button) {
        gpio_set_interrupt(gpio_num, GPIO_INTTYPE_EDGE_ANY, NULL);
    }
}

