#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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
        case 10:
            snprintf(buffer,baseCount,"%d", integer);
            break;
        default:
            throwException("Choose a base of 2, 10 or 16");
            break;
    }
    return buffer;
}

int baseToInt(char* number, int base){
    char *eptr;
    long result = strtol(number, &eptr, base);

    if(strlen(eptr) > 0){
        throwException("Conversion error: invalid number %c\n",eptr[0]);

    }
    /* If the result is 0, test for an error */
    if (result == 0)
    {
        /* If a conversion error occurred, display a message and exit */
        if (errno == EINVAL)
        {
            throwException("Conversion error: %d\n", errno);
        }
    }

    /* If the result is equal to LONG_MIN or LONG_MAX, test for a range error */
    if (result < INT_MIN || result > INT_MAX)
    {
            throwException("Conversion error: The value provided was out of range\n");
    }
    return (int) result;
}


