#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <string.h>

#include "hardware_config.h"
#include "axes.h"
#include "led.h"

//#define DEBUG_PRINT
#define BUFSIZE 512

axes_conv_flags_t axes_conv_flags;
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
    axes_conv_flags = AXES_CONV_SWAP_L | AXES_CONV_INV_LX | AXES_CONV_INV_LY
                    | AXES_CONV_SWAP_R | AXES_CONV_INV_RX | AXES_CONV_INV_RY
                    | AXES_CONV_SWAP_T;

    rgb_led_init(&led, LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
    rgb_led_set_colour(&led, 150, 200, 100);
    rgb_led_set_enabled(&led, true);
}

void loop() {
    axes_data_uint16_t axes_raw = read_axes();
    axes_data_conv(&axes_raw, axes_conv_flags);

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
