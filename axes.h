#ifndef __AXES_H__
#define __AXES_H__

typedef uint16_t axes_conv_flags_t;
#define AXES_CONV_SWAP_L 0x1
#define AXES_CONV_INV_LX 0x2
#define AXES_CONV_INV_LY 0x4
#define AXES_CONV_SWAP_R 0x8
#define AXES_CONV_INV_RX 0x10
#define AXES_CONV_INV_RY 0x20
#define AXES_CONV_SWAP_T 0x40
#define AXES_CONV_INV_LT 0x80
#define AXES_CONV_INV_RT 0x100

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

void axes_init();

axes_data_uint16_t read_axes();

void axes_data_conv(axes_data_uint16_t *axes_data, axes_conv_flags_t flags);

axes_data_double_t axes_uint16_to_double(axes_data_uint16_t *axes_raw);

int sprint_axes_raw(char *buf, axes_data_uint16_t *axes_raw);
int sprint_axes_scaled(char *buf, axes_data_double_t *axes);
int sprint_axis_bar(char *buf, uint16_t axis_raw, int total_width);
int sprint_axis_bar_label(char *buf, char* label, uint16_t axis_raw, int bar_width);
int sprint_axes_debug(char *buf, axes_data_uint16_t *axes_raw);

#endif //__AXES_H__
