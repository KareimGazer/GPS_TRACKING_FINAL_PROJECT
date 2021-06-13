#include <stdio.h>
#include <stdlib.h>

int main()
{
    float longitude[] = {1.1, 2.2, 3.2};
    FILE *flong = fopen("longitude.txt", "wb");

    for (unsigned i = 0; i < 3; i++) 
        fprintf(flong, "%f\n", longitude[i]);
    // check for error here too
    //fwrite(longitude, sizeof(float), sizeof(longitude), flong);
    fclose(flong);

    float lattiude[]  = {3.4, 5.6, 7.8}; 
    FILE *flatt = fopen("lattiude.txt", "wb");

    for (unsigned i = 0; i < 3; i++) 
        fprintf(flatt, "%f\n", lattiude[i]);
    //fwrite(lattiude, sizeof(float), sizeof(lattiude), flatt);
    fclose(flatt);
}