

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"





#define RS 0x10   //PE4
#define RW 0x08  //PE3
#define E 0x04  //PE2


/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80
#define Function_set_8bit_1line 0x30



/* prototypes of LCD functions */
void LCD_init(void);  /* LCD initialization function */

void LCD_Cmd(unsigned char command); /*Used to send commands to LCD */

void LCD_Write_Char (char data); /* Writes ASCII character */

void LCD_String (char *str);	/* Send string to LCD function */







#endif /* LCD_H_ */
