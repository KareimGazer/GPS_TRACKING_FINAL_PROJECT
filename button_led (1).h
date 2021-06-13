
#ifndef BUTTON_H_
#define BUTTON_H_

#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "common_macros.h"



void button_led_init(void);
void led_off(volatile uint8_t led);
void led_on(volatile uint8_t led);
bool button_is_pressed(void);
#endif