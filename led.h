#ifndef __RGB_LED_H__
#define __RGB_LED_H__

typedef struct {
    uint red_pin;
    uint green_pin;
    uint blue_pin;
    uint red_slice;
    uint green_slice;
    uint blue_slice;
} rgb_led_t;

void rgb_led_init(rgb_led_t *led, int red_pin, int green_pin, int blue_pin);
void rgb_led_set_colour(rgb_led_t *led, int r, int g, int b);
void rgb_led_set_enabled(rgb_led_t *led, bool enabled);

#endif //__RGB_LED_H__
