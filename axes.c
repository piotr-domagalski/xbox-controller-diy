#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <string.h>

#include "axes.h"
#include "hardware_config.h"

inline double _adc_i2d(uint16_t adc);
void _put_axis_addr(int addr);
inline void _put_axis_addr_sleep(int addr);
void _axes_swap(uint16_t *a, uint16_t *b);
void _axes_invert(uint16_t *a);

void axes_init() {
    adc_init();
    adc_gpio_init(AXIS_X_PIN);
    adc_gpio_init(AXIS_Y_PIN);
    adc_select_input(AXIS_X_ADC);

    gpio_init(AXIS_SEL_ADDR_A_PIN);
    gpio_set_dir(AXIS_SEL_ADDR_A_PIN, true);
    gpio_init(AXIS_SEL_ADDR_B_PIN);
    gpio_set_dir(AXIS_SEL_ADDR_B_PIN, true);
    _put_axis_addr(NOTHING_ADDR);
}

axes_data_uint16_t read_axes() {
    axes_data_uint16_t raw = { 0 };

    _put_axis_addr_sleep(JOY_LEFT_ADDR);
    adc_select_input(AXIS_X_ADC);
    raw.LX = adc_read();
    adc_select_input(AXIS_Y_ADC);
    raw.LY = adc_read();

    _put_axis_addr_sleep(JOY_RIGHT_ADDR);
    adc_select_input(AXIS_X_ADC);
    raw.RX = adc_read();
    adc_select_input(AXIS_Y_ADC);
    raw.RY = adc_read();

    _put_axis_addr_sleep(TRIGGERS_ADDR);
    adc_select_input(AXIS_X_ADC);
    raw.LT = adc_read();
    adc_select_input(AXIS_Y_ADC);
    raw.RT = adc_read();

    _put_axis_addr(NOTHING_ADDR);

    return raw;
}

void axes_data_conv(axes_data_uint16_t *axes_data, axes_conv_flags_t flags) {
    if (flags & AXES_CONV_SWAP_L) { _axes_swap(&axes_data->LX, &axes_data->LY); }
    if (flags & AXES_CONV_INV_LX) { _axes_invert(&axes_data->LX); }
    if (flags & AXES_CONV_INV_LY) { _axes_invert(&axes_data->LY); }
    if (flags & AXES_CONV_SWAP_R) { _axes_swap(&axes_data->RX, &axes_data->RY); }
    if (flags & AXES_CONV_INV_RX) { _axes_invert(&axes_data->RX); }
    if (flags & AXES_CONV_INV_RY) { _axes_invert(&axes_data->RY); }
    if (flags & AXES_CONV_SWAP_T) { _axes_swap(&axes_data->LT, &axes_data->RT); }
    if (flags & AXES_CONV_INV_LT) { _axes_invert(&axes_data->LT); }
    if (flags & AXES_CONV_INV_RT) { _axes_invert(&axes_data->RT); }
}

axes_data_double_t axes_uint16_to_double(axes_data_uint16_t *axes_raw) {
    axes_data_double_t axes;
    axes.LX = _adc_i2d(axes_raw->LX);
    axes.LY = _adc_i2d(axes_raw->LY);
    axes.RX = _adc_i2d(axes_raw->RX);
    axes.RY = _adc_i2d(axes_raw->RY);
    axes.LT = _adc_i2d(axes_raw->LT);
    axes.RT = _adc_i2d(axes_raw->RT);
    return axes;
}

inline double _adc_i2d(uint16_t adc) {
    return ((double)(adc-(ADC_MAX/2)))/(ADC_MAX/2);
}

void _put_axis_addr(int addr) {
    gpio_put(AXIS_SEL_ADDR_A_PIN, 0 != (addr & 1));
    gpio_put(AXIS_SEL_ADDR_B_PIN, 0 != (addr & 2));
}

inline void _put_axis_addr_sleep(int addr) {
    _put_axis_addr(addr);
    sleep_us(AXIS_SEL_ADDR_DELAY_US);
}

inline void _axes_swap(uint16_t *a, uint16_t *b) {
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}
inline void _axes_invert(uint16_t *a) {
    *a = ADC_MAX-(*a);
}

int sprint_axes_raw(char *buf, axes_data_uint16_t *axes_raw) {
    return sprintf(buf, "LX=%5d LY=%5d RX=%5d RY=%5d LT=%5d RT=%5d",
            axes_raw->LX, axes_raw->LY,
            axes_raw->RX, axes_raw->RY,
            axes_raw->LT, axes_raw->RT
    );
}

int sprint_axes_scaled(char *buf, axes_data_double_t *axes) {
    return sprintf(buf, "LX=% 5.2f LY=% 5.2f RX=% 5.2f RY=% 5.2f LT=% 5.2f RT=% 5.2f",
            axes->LX, axes->LY,
            axes->RX, axes->RY,
            axes->LT, axes->RT
    );
}

int sprint_axis_bar(char *buf, uint16_t axis_raw, int total_width) {
  int bar_width = total_width-2;
  int half_char = ADC_MAX/(bar_width-1)/2;
  int low, high;
  if (axis_raw < ADC_HALF) { low = axis_raw-ADC_HALF; high = 0; }
  else { low = 0; high = axis_raw-ADC_HALF; }

  buf[0] = '[';
  buf[total_width-1] = ']';
  memset(buf+1, '-', bar_width);
  int begin=(low*bar_width+half_char)/ADC_MAX+bar_width/2;
  int end=(high*bar_width+half_char)/ADC_MAX+bar_width/2;
  if(axis_raw > ADC_HALF) { begin += 1; end += 1; }
  memset(buf+begin+1, '#', end-begin);
  buf[total_width/2] = '|';
  return total_width;
}

int sprint_axis_bar_label(char *buf, char* label, uint16_t axis_raw, int bar_width) {
    char *bar = strcpy(buf, label);
    return strlen(label) + sprint_axis_bar(buf+strlen(label), axis_raw, bar_width);
}

int sprint_axes_debug(char *buf, axes_data_uint16_t *axes_raw) {
    axes_data_double_t axes = axes_uint16_to_double(axes_raw);
    const int BAR_WIDTH = 21;
    int offset = 0;
    offset += sprint_axis_bar_label(buf+offset, "LX: ", axes_raw->LX, BAR_WIDTH);
    offset += sprint_axis_bar_label(buf+offset, "  LY: ", axes_raw->LY, BAR_WIDTH);
    offset += sprint_axis_bar_label(buf+offset, "\nRX: ", axes_raw->RX, BAR_WIDTH);
    offset += sprint_axis_bar_label(buf+offset, "  RY: ", axes_raw->RY, BAR_WIDTH);
    offset += sprint_axis_bar_label(buf+offset, "\nLT: ", axes_raw->LT, BAR_WIDTH);
    offset += sprint_axis_bar_label(buf+offset, "  RT: ", axes_raw->RT, BAR_WIDTH);
    buf[offset++] = '\n';
    offset += sprint_axes_raw(buf+offset, axes_raw);
    buf[offset++] = '\n';
    offset += sprint_axes_scaled(buf+offset, &axes);
    return offset;
}
