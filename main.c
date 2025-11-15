#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <string.h>
#include "axes.h"
#include "led.h"

//#define DEBUG_PRINT
#define BUFSIZE 512

rgb_led_t led;

void setup();
void loop();

int main() {
    setup();

    while(1){
        loop();
    }
}

void setup() {
    stdio_init_all();

    adc_init();
    adc_gpio_init(AXIS_X_PIN);
    adc_gpio_init(AXIS_Y_PIN);
    adc_select_input(AXIS_X_ADC);

    gpio_init(AXIS_SEL_ADDR_A_PIN);
    gpio_set_dir(AXIS_SEL_ADDR_A_PIN, true);
    gpio_put(AXIS_SEL_ADDR_A_PIN, 0);
    gpio_init(AXIS_SEL_ADDR_B_PIN);
    gpio_set_dir(AXIS_SEL_ADDR_B_PIN, true);
    gpio_put(AXIS_SEL_ADDR_B_PIN, 0);

    rgb_led_init(&led, LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
    rgb_led_set_colour(&led, 150, 200, 100);
    rgb_led_set_enabled(&led, true);
}

void loop() {
    axes_raw_t axes_raw = read_axes();

    uint red = axes_raw.LT>>4;
    uint green = axes_raw.RT>>4;
    uint blue = axes_raw.LY>>4;
    rgb_led_set_colour(&led, red, green, blue);

    char buf[BUFSIZE];
    memset(buf, ' ', BUFSIZE);
    int len = sprint_axes_debug(buf, &axes_raw);
    printf("%s\n", buf);
    sleep_ms(100);
}
