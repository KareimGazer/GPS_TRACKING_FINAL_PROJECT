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


float atof( char *str)
{

    sint32_t i,sum,total,index;
    float res;
    i=0;

    while(str[i])
    {

        if(str[i]=='.')
        {
            index=i;
            i++;
            continue;

        }
        total=str[i]-48;
        if(i==0)
        {
            sum=total;
            i++;
            continue;
        }
        sum=sum*10+total;
        i++;
    }

    index=(strlength(str)-1)-index;

    res=sum;
    for(i=1;i<=index;i++)
    {
        res=(float)res/10;
    }
    return res;
}


void strrcpy( char* destination, const char* source)
{
    if (destination == '\0')
    {
        return ;
    }
 while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 *destination = '\0';
 }
void readGPSModule(volatile float* ftemp,volatile float* stemp)
{
	int u = 1;
	int x = 0;
	int checkNum = 0;
	int counterNum = 0;
	int start = 0;
	
	char bufferCheck[7] = { 0 };
	char inputBuffer[50] = { 0 };
	int found;
	int k = 0;
	int i;
	char element;
	while (u)
	{
		if (!x)
		{
			element = UART1_getByte();
			if (element == '$')
			{
				if (counterNum > 0)
				{int count = 0;
					inputBuffer[counterNum] = '\0';
					found = 0;
					
					while (inputBuffer[count] != '\0')
					{
						if (inputBuffer[count++] == 'A')
							found = 1;
					}
					if (found)
						x = 1;
				}
				
				for ( i = 0; i < 7; i++)
				{
					bufferCheck[i] = '\0';
				}
				counterNum = 0;
				checkNum = 0;
			}

			if (checkNum < 7)
			{
				bufferCheck[checkNum++] = element;
			}
			else if (checkNum >= 7)
			{

				if (bufferCheck[0] == '$' && bufferCheck[1] == 'G' && bufferCheck[2] == 'P' && bufferCheck[3] == 'G' && bufferCheck[4] == 'L' && bufferCheck[5] == 'L' && bufferCheck[6] == ',')
				{
					inputBuffer[counterNum++] = element;
				}
			}
		}

		else
		{
			int b = 0;

			int i = 0;
			int j = 0;
			char firstnum[20] = { 0 };
			char secondnum[20] = { 0 };
			int startfirst = 1;
			int startSecond = 0;
			while (inputBuffer[b] != '\0')
			{

				if (startfirst)
				{
					if (inputBuffer[b] == ',' && inputBuffer[b + 1] == 'N' && inputBuffer[b + 2] == ',')
					{
						startfirst = 0;
					}
					else
					{
						firstnum[i++] = inputBuffer[b];
					}
				}
				if (startSecond)
				{
					if (inputBuffer[b] == ',' && inputBuffer[b + 1] == 'E' && inputBuffer[b + 2] == ',')
					{
						startSecond = 0;
					}
					else
					{
						secondnum[j++] = inputBuffer[b];
					}
				}
				if (b > 2)
				{
					if (inputBuffer[b] == ',' && inputBuffer[b - 1] == 'N' && inputBuffer[b - 2] == ',')
					{
						startSecond = 1;
						j = 0;
					}
				}
				b++;
			}

			*ftemp = atof(firstnum);
			*stemp = atof(secondnum);

			u = 0;
		}
	}
}


