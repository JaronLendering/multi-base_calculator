#include <stdio.h>
#include <stdlib.h>

#include "exceptions.h"
#include "conversions.h"

void printNewBase(int number, int base){
    char* buffer = intToBase(number, base);

    printf("%d in base %d is %s\n", number, base, buffer );
    free(buffer);

}

int main(int argc, char* argv[]){
    
    if(argc < 4){
        throwException("You miss %d argument(s)!\n", 4 - argc);
    }
    if(argc > 4){
        throwException("You have given %d argument(s) too many!\n", argc-4);
    }

    int base = atoi(argv[1]);
    int number = atoi(argv[2]);
    printNewBase(number,base);

    
}


