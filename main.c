#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <string.h>
#include "axes.h"

//#define DEBUG_PRINT
#define BUFSIZE 512

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
}

void loop() {
    axes_raw_t axes_raw = read_axes();

    char buf[BUFSIZE];
    memset(buf, ' ', BUFSIZE);
    int len = sprint_axes_debug(buf, &axes_raw);
    printf("%s\n", buf);
    sleep_ms(100);
}
