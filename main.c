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

    axes_init();

    rgb_led_init(&led, LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
    rgb_led_set_colour(&led, 150, 200, 100);
    rgb_led_set_enabled(&led, true);
}

void loop() {
    axes_data_uint16_t axes_raw = read_axes();

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
