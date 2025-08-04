#include <stdio.h>
#include <stdlib.h>

#include "exceptions.h"
#include "conversions.h"

void printBase(int number, int base){

    char* buffer = intToBase(number, base);

    printf("%d in base %d is %s\n", number, base, buffer );
    free(buffer);

}


int main(int argc, char* argv[]){
    
    if(argc < 3){
        throwException("You miss %d argument(s)!\n", 4 - argc);
    }

    int result_base = baseToInt(argv[1],10);
    int number = baseToInt(argv[2],result_base);
    printBase(number,10);
}


