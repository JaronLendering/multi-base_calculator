#include <stdarg.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#include "exceptions.h"

void throwException(char input_s[], ... ){
    va_list args;
    va_start(args, input_s);
    
    size_t total_size = strlen("\033[31m") +strlen(input_s) + strlen("\033[0m") + 1;
    char* red_text = malloc(total_size);

    strcpy(red_text, "\033[31m");
    strcat(red_text, input_s);
    strcat(red_text, "\033[0m");

    vfprintf(stderr,red_text, args);

    va_end(args);

    free(red_text);
    
    exit(1);


}