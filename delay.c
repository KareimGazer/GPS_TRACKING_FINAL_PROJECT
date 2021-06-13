
#include "delay.h"



void delayInit()
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x00000005;
}

void Delay(uint32_t delay)
{
	delayInit();
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){};
}

void delay_ms(uint32_t delay)
{
	unsigned long i; 
	for(i=0; i<delay; i++){
		Delay(16000); 
	}
}



