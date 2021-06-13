
#include "lcd.h"


/* LCD and GPIOB initialization Function */ 


void LCD_Cmd (unsigned char command)
{
	GPIO_PORTB_DATA_R = command ;	
	GPIO_PORTE_DATA_R = E ;
	delay_ms(2);
	GPIO_PORTE_DATA_R = 0 ;
}



void LCD_Write_Char (char data)
{
	GPIO_PORTB_DATA_R = data ;
	GPIO_PORTE_DATA_R |= (0x14) ;
	delay_ms(2);
	GPIO_PORTE_DATA_R = !(0x10) ;
}


void LCD_String (char * str)
{
	int count = 0;
	while(*str != '\0')
	{
		LCD_Write_Char(*str);
		count ++ ;
		str++;
		if(count==15)
		{
			LCD_Cmd(0xC0);
		}
	
		}
	
}




void LCD_init()
{
	delay_ms(50);	
	
	//activate clock for portB and portE 
	
	SYSCTL_RCGCGPIO_R |= 0x12;  
	while((SYSCTL_PRGPIO_R&0x00000012)==0){} 
	
	// configure control pins RS,R/W,E	
	
	GPIO_PORTE_LOCK_R	= 0x4C4F434B ;
	GPIO_PORTE_CR_R |= 0x1C;   // PE2,PE3,PE4
	GPIO_PORTE_DIR_R |= 0x1C; // PE2,PE3,PE4
	GPIO_PORTE_DEN_R |= 0x1C; // PE2,PE3,PE4 
	GPIO_PORTE_AFSEL_R = 0;
	GPIO_PORTE_PUR_R = 0;
  GPIO_PORTE_AMSEL_R = 0;
	GPIO_PORTE_PCTL_R = 0;

	// configure data pins 	D0-D7
	GPIO_PORTB_LOCK_R	= 0x4C4F434B ;
	GPIO_PORTB_CR_R |= 0xFF;  // PB0-PB7
	GPIO_PORTB_DIR_R |= 0xFF; // PB0-PB7
	GPIO_PORTB_DEN_R |= 0xFF; // PB0-PB7
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_PUR_R = 0;
  GPIO_PORTB_AMSEL_R = 0;  
	GPIO_PORTB_PCTL_R = 0;

	
  LCD_Cmd(Function_set_8bit_1line); 
	delay_ms(1);	
	
	LCD_Cmd(Function_set_8bit);
	delay_ms(1);	
	LCD_Cmd(cursorOn);         
	delay_ms(1);	
	LCD_Cmd(clear_display );     
	delay_ms(2);	
	LCD_Cmd(cursorBlink);       
	delay_ms(2);
	LCD_Cmd(returnHome); 
	delay_ms(1);
}






















