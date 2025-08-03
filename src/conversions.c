#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exceptions.h"


void intToBinary(unsigned int l, char* bin, unsigned int integer){
    int i = l;
    bin[i--] = '\0'; 
    while(integer > 0 && i>=0){
        bin[i--] = (char) (integer%2 + '0');
        integer /= 2;
    }
}


char* intToBase(unsigned int integer, int base){
    unsigned int baseCount = ((int) (log(integer)/log(base)))+2;
    char* buffer = malloc(baseCount);

    switch(base){
        case 2:
            intToBinary(baseCount-1, buffer, integer);
            break;
        case 16:
            snprintf(buffer, baseCount,"%x", integer);
            break;
        default:
            throwException("Choose a base of 2 or 16");
            break;
    }
    return buffer;
}

