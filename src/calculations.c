#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "exceptions.h"
#include "conversions.h"
#include "calculations.h"


typedef struct {
    const char* input;  // the string to parse
    int pos;            // current position in the string
} Parser;


typedef int (*Operator)(int, int);

int add(int a, int b)    { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b)   { return b != 0 ? a / b : 0; }
int power(int a, int b) { int result = 1; for(int i = 0; i < b; i++){ result = result*a;} return result;}

Operator get_operator(char op) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        case 'p': return power;
        default: return NULL;
    }
}

int parse_number(Parser* p){
    int size = 10;
    char* number = malloc(size);
    char c;
    int number_i = 0;
    int base_size = 3;
    char* base_string = malloc(base_size);
    int base;
    int base_i = 0;
    bool is_base = true;
    while(true){
        c = p->input[p->pos];
        switch(c){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                p->pos++;

                if(is_base){
                    if(base_i >= base_size -1){
                        throwException("Parsing error: Base can only be %d digits long\n", base_size-1);
                    }
                    base_string[base_i++] = c; 
                    break;
                }

                if(number_i >= size-1){
                    size += 10;
                    char* temp = realloc(number,size);
                    if (temp == NULL) {
                        throwException("Parsing error: Memory allocation failed\n");
                    } else {
                        number = temp;  
                    }
                }
                number[number_i++] = c;
                break;
            case 'x':
                p->pos++;
                if(is_base){
                    is_base = false;
                    base_string[base_i] = '\0';
                    base = baseToInt(base_string,10);
                    break;
                }
                throwException("Parsing error: Base is already set\n");
            default:
                if(is_base){
                    char* total = malloc(size+base_size-1);
                    if (total == NULL) {
                        throwException("Parsing error: Memory allocation failed\n");
                    } 
                    strcpy(total,base_string);
                    strcat(total,number);
                    free(number);
                    number_i += number_i + base_i;
                    number = total;  
                    base = 10;
                }
                size_t l = strlen(number);
                number[number_i] = '\0';
                printf("number parsed: %s with length: %ld \n", number,l);

                int n = baseToInt(number,base);
                free(number);
                return n;
        }
        
    }


}

int calculate(char* calculation){
    Parser parser = {calculation, 0};
    size_t length = strlen(calculation);
    char c;
    int prenum;
    Operator op;
    bool is_pre = true;
    bool was_operator = true;
    while(parser.pos < length){
        c = parser.input[parser.pos];
        switch(c){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                was_operator = false;
                if(is_pre){
                    prenum = parse_number(&parser);
                    is_pre = false;
                    break;
                }
                prenum = op(prenum,parse_number(&parser));
                break;
            case '*':

                if(was_operator){
                    throwException("Parsing error: A number has to be infront an operator\n");
                }
                if(parser.pos < length-1 && parser.input[parser.pos+1] == '*'){
                    op = get_operator('p');
                    parser.pos += 2;
                }
                else{
                        op = get_operator('*');
                        parser.pos++;
                }
                was_operator = true;
                break;
            case '/':
            case '+':
            case '-':
                if(was_operator){
                    throwException("Parsing error: A number has to be infront an operator\n");
                }
                op = get_operator(c);
                parser.pos++;
                was_operator = true;
                break;
            default:
                throwException("Parsing error: Use only operators or numbers\n");
        }   
    }
    if(was_operator){
        throwException("Parsing error: A number has to be after an operator\n");
    }
    return prenum;

}
