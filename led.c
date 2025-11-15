#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include "led.h"
#define PWM_WRAP 255

uint _init_led_pin(int pin) {
    gpio_set_dir(pin, true);
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, PWM_WRAP);
    return slice_num;
}

void rgb_led_init(rgb_led_t *led, int red_pin, int green_pin, int blue_pin) {
    //memset(led, 0, sizeof rgb_led_t);?
    led->red_pin = red_pin;
    led->green_pin = green_pin;
    led->blue_pin = blue_pin;

    led->red_slice = _init_led_pin(led->red_pin);
    led->green_slice = _init_led_pin(led->green_pin);
    led->blue_slice = _init_led_pin(led->blue_pin);
}

void rgb_led_set_colour(rgb_led_t *led, int r, int g, int b) {
    pwm_set_gpio_level(led->red_pin, r);
    pwm_set_gpio_level(led->green_pin, g);
    pwm_set_gpio_level(led->blue_pin, b);
}

void rgb_led_set_enabled(rgb_led_t *led, bool enabled) {
    pwm_set_enabled(led->red_slice, enabled);
    pwm_set_enabled(led->green_slice, enabled);
    pwm_set_enabled(led->blue_slice, enabled);
}
