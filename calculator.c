#include <stdio.h> 
#include "exceptions.h"

int main(int argc, char* argv[]){
    if(argc < 4){
        throwException("You miss %d argument(s)!\n", 4 - argc);
    }
    if(argc > 4){
        throwException("You have given %d argument(s) too many!\n", argc-4);
    }
}