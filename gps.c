#include "gps.h"
#include "math.h"
#include "uart.h"
#include "string.h"


extern volatile float start_latitude;
extern volatile float start_longitude;	
extern volatile float current_latitude;
extern volatile float current_longitude;



sint32_t strlength(char str[])
{
	sint32_t i;
	/* count the string start from element 0 until the element before the NULL terminator */
	for(i = 0; str[i] != '\0'; ++i);
	return i;
}


 char * mystrtok( char * str, const char *comp)
{
	static sint32_t pos;
	static  char *s;
	sint32_t i =0, start = pos;
sint32_t j = 0;
	
	// Copying the string for further calls of strtok
	if(str!='\0')
		s = str;

	i = 0;
	
	//While not end of string
	while(s[pos] != '\0')
	{
		j = 0;
		//Comparing of one of the delimiter matches the character in the string
		while(comp[j] != '\0')
		{
			//Pos point to the next location in the string that we have to read
			if(s[pos] == comp[j])
			{
				//Replace the delimter by \0 to break the string
				s[pos] = '\0';
				pos = pos+1;
				//Checking for the case where there is no relevant string before the delimeter.
				//start specifies the location from where we have to start reading the next character
				if(s[start] != '\0')
					return (&s[start]);
				else
				{
					// Move to the next string after the delimiter
					start = pos;
					// Decrementing as it will be incremented at the end of the while loop
					pos--;
					break;
				}
			}
			j++;
		}
		pos++;
	}//End of Outer while
	s[pos] = '\0';
	if(s[start] == '\0')
		return '\0';
	else
		return &s[start];
}




sint32_t strcompare(  char* str1,  char str2)
{ sint32_t i=0;
while(*(str1+i)!='\0'  )
{
	
if(*(str1+i)!=str2){return 0;}

}

return 1;
}













