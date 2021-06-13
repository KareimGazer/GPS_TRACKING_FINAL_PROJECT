
#include "button_led.h"

void button_led_init()
{
SYSCTL_RCGCGPIO_R |= 0x00000020;	// activate Port F
	 GPIO_PORTF_LOCK_R = 0x4C4F434B; 

   GPIO_PORTF_CR_R = 0x01;           // Enable GPIOPUR register enable to commit

	GPIO_PORTF_DIR_R = 0x0E; //set PF1,PF2,PF3 as an output and PF4 as an input pin
	
	GPIO_PORTF_PUR_R = 0x10;        // Enable Pull Up resistor PF4

	GPIO_PORTF_DEN_R = 0x1F;         // Enable PF1 and PF4 as a digital GPIO pins 
}

void led_on(volatile uint8_t led)
{
SET_BIT(GPIO_PORTF_DATA_R,led);
}

void led_off(volatile uint8_t led)
{
CLEAR_BIT(GPIO_PORTF_DATA_R,led);
}

bool button_is_pressed()
{
if(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,4)){return 1;}
else {return 0;}

}	


