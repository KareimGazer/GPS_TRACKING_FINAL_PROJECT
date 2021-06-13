#ifndef GPS_H_
#define GPS_H_

#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "common_macros.h"

char * mystrtok( char * str, const  char *comp);
void strrcpy( char* destination, const  char* source);
sint32_t strcompare(  char* str1,  char str2);
sint32_t strlength( char str[]);
float atof( char *str);
void readGPSModule(volatile float *latitudeResult,volatile float *longitudeResult);





#endif