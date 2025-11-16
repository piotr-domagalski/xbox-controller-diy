#ifndef __AXES_H__
#define __AXES_H__

#include "hardware_config.h"

typedef struct {
    uint16_t LX;
    uint16_t LY;
    uint16_t RX;
    uint16_t RY;
    uint16_t LT;
    uint16_t RT;
} axes_data_uint16_t;

typedef struct {
    double LX;
    double LY;
    double RX;
    double RY;
    double LT;
    double RT;
} axes_data_double_t;

axes_data_uint16_t read_axes();

inline double adc_i2d(uint16_t adc);
axes_data_double_t axes_uint16_to_double(axes_data_uint16_t *axes_raw);

void put_axis_addr(int addr);
inline void put_axis_addr_sleep(int addr);

int sprint_axes_raw(char *buf, axes_data_uint16_t *axes_raw);
int sprint_axes_scaled(char *buf, axes_data_double_t *axes);
int sprint_axis_bar(char *buf, uint16_t axis_raw, int total_width);
int sprint_axis_bar_label(char *buf, char* label, uint16_t axis_raw, int bar_width);
int sprint_axes_debug(char *buf, axes_data_uint16_t *axes_raw);

#endif //__AXES_H__
