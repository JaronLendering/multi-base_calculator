#include <stdio.h>
#include <stdlib.h>

#include "exceptions.h"
#include "conversions.h"
#include "calculations.h"

void printCalcInBase(char* calc, int number, int base){
    char* buffer = intToBase(number, base);
    printf("%s in base %d is %s\n", calc, base, buffer );
    free(buffer);

}


int main(int argc, char* argv[]){
    
    if(argc < 3){
        throwException("You miss %d argument(s)!\n", 3 - argc);
    }

    int result_base = baseToInt(argv[1],10);
    char* calculation = argv[2];
    int number = calculate(argv[2]);
    printCalcInBase(calculation,number,result_base);
}


