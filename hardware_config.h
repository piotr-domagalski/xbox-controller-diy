#ifndef __HARDWARE_CONFIG_H__
#define __HARDWARE_CONFIG_H__

#define ADC_MAX 0xFFF
#define ADC_HALF (ADC_MAX>>1)

#define AXIS_X_PIN 26
#define AXIS_X_ADC 0
#define AXIS_Y_PIN 27
#define AXIS_Y_ADC 1

#define AXIS_SEL_ADDR_A_PIN 2
#define AXIS_SEL_ADDR_B_PIN 3
#define AXIS_SEL_ADDR_DELAY_US (10*1000)

#define JOY_LEFT_ADDR 0
#define JOY_RIGHT_ADDR 1
#define TRIGGERS_ADDR 2
#define NOTHING_ADDR 3

#endif //__HARDWARE_CONFIG_H__
