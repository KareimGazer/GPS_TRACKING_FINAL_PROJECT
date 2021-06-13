#include "lcd.h"
#include "button_led.h"
#include "gps.h"
#include "uart.h"
#include "math.h"

void SystemInit(){}

volatile uint8_t button_flag=0;
volatile float start_latitude=0.0;
volatile float start_longitude=0.0;	
volatile float current_latitude=0.0;
volatile float current_longitude=0.0;		
float distance=0;
char distance_str[4];	

void modify_lat_long(volatile float*latitude, volatile float*longitude )
{
	float seconds=0.0,result=0.0,minutes=0.0;
	sint32_t degrees;
	                                  //latitude calculation
                                    degrees=(*latitude)/100;
                                    minutes=(*latitude)-(float)(degrees*100);
                                    seconds=minutes/60.00;
                                    result=degrees+seconds;
																		*latitude= result;


                                    //longitude calculation
                                    degrees=(*longitude)/100;
                                    minutes=(*longitude)-(float)(degrees*100);
                                    seconds=minutes/60.00;
                                    result=degrees+seconds;
                                    *longitude= result;	
	
}
	
	
	float degtorad(float deg)
{
  return deg * ((22/7)/180);
}
	
	


float getDistanceFromLatLonInKm(volatile float *lat1,volatile float *lon1,volatile float *lat2,volatile float *lon2)
{

	if(*lat1==*lat2 &&*lon1==*lon2){return 0;}
	else
	{
  float R = 6371; // Radius of the earth in km
  float dLat = degtorad((*lat2)-(*lat1));  // deg2rad below
  float dLon = degtorad((*lon2)-(*lon1)); 
  float a = (sin(dLat/2) * sin(dLat/2)) +(cos(degtorad((*lat1))) *cos(degtorad(*(lat2))) * sin(dLon/2) * sin(dLon/2)); 
  float c = 2 * atan2(sqrt(a),sqrt(1-a)); 
   float d = R * c; // Distance in km
	d=d*1000; // distance in meter
	
  return d;
}
}







void itoa(char c[],int a,int base)
{
  int i=0;
int str_length=0;
while(a!=0)
{int temp;
temp=a%base;
c[i]=temp+48;
i++;
a=a/base;
}
i=0;
while(*(c+i)!='\0')
{
i++;
}
str_length=i;
i=0;


for(i=0;i<str_length/2;i++)
{int temp;
temp=c[i];
c[i]=c[str_length-i-1];
c[str_length-i-1]=temp;

}
}


























int main()
{
	
LCD_init();

	UART1_init();

	button_led_init();	
	
readGPSModule(&start_latitude,&start_longitude);

modify_lat_long(&start_latitude,&start_longitude);
	
	
	delay_ms(200);
	
	while(1)
{
	
if(button_is_pressed()){button_flag=1;led_on(1);}
if(button_flag==1)
{	
	
	
readGPSModule(&current_latitude,&current_longitude);
	
modify_lat_long(&current_latitude,&current_longitude);	
	
distance=getDistanceFromLatLonInKm(&start_latitude,&start_longitude,&current_latitude,&current_longitude);
	
if(!distance)
{
LCD_Write_Char ('0');
delay_ms(500);
LCD_Cmd(0x01);	
}
else
{
itoa(distance_str,distance,10);

	delay_ms(500);
LCD_String (distance_str);

delay_ms(500);	
LCD_Cmd(0x01);
}

}
	
	}

}







