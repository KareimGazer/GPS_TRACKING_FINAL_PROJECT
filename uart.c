#include "uart.h"

void UART1_init(void)
{
	SYSCTL_RCGCUART_R |= 0x00000002; // activate UART1
	SYSCTL_RCGCGPIO_R |= 0x00000004; // activate port C
	//next steps requires UART to be disabled for proper confg
	UART1_CTL_R &= ~0x00000001; // disable UART
	UART1_CTL_R=0;
	
	// Desired Baud Rate = sys CLK / (16 * clock divison)
	
	//integer part of clock division
	UART1_IBRD_R = 104;
	UART1_FBRD_R = 11;
	
	UART1_LCRH_R = 0x00000070;    // 8 bits, no parity bits, one stop, FIFOs
	UART1_CC_R=0x0;
	UART1_CTL_R |= 0x301;   //enable UART
	
	GPIO_PORTC_AFSEL_R |= 0x030; //enable alt funct on PC5-4
	GPIO_PORTC_DEN_R |=0x30;    // configure PC5-4 as UART1
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF) + 0x00220000;
	GPIO_PORTC_AMSEL_R &= ~0x30; // disable analog on PC5-4
}



uint8_t UART1_getByte(void)
{
	while((UART1_FR_R&0x0010) != 0); 
	return (uint8_t)(UART1_DR_R&0xFF);
}


void UART1_sendByte(uint8_t data)
{
	while((UART1_FR_R&0x0020) != 0); 
	UART1_DR_R = data;
}
