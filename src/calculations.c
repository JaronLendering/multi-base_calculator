#include <string.h>
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
int power(int a, int b) {return a ** b;}

Operator get_operator(char op) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        case '**': return power;
        default: return NULL;
    }
}

int parse_number(Parser* p){
    int size = 10;
    char* number = malloc(size);
    char c = p->input[p->pos++];
    int i = 0;
    number[i++] = c;
    while(true){
        c = p->input[p->pos];
        switch(c){
            case "0":
            case "1":
            case "2":
            case "3":
            case "4":
            case "5":
            case "6":
            case "7":
            case "8":
            case "9":
                p->pos++
                if(i >= size){
                    size += 10
                    char* temp = realloc(number,size);
                    if (temp == NULL) {
                        throwException("Memory allocation failed\n");
                    } else {
                        number = temp;  
                    }
                }
                number[i++] = c;
                break;
            default:
                int n = baseToInt(number,10);
                free(number);
                return n;
        }
        
    }


}

int calculate(char* calculation){
    Parser parser = {calculation, 0}
    size_t length = strlen(calculation);
    char c;
    int prenum;
    Operator op;
    bool is_pre = true;
    bool was_operator = true;
    while(parser.pos < length-1){
        c = parser.input[parser.pos];
        switch(c){
            case "0":
            case "1":
            case "2":
            case "3":
            case "4":
            case "5":
            case "6":
            case "7":
            case "8":
            case "9":
                if(is_pre){
                    prenum = parse_number(parser*);
                    is_pre = false;
                    break;
                }
                prenum = op(prenum,parse_number(parser*));
                was_operator = false;
                break;
            case "*":

                if(was_operator){
                    throwException("A number has to be infront and before an operator")
                }
                if(parser.pos < length-2 && parser.input[parser.pos+1] == "*"){
                    op = get_operator("**");
                    parser.pos += 2;
                }
                else{
                    op = get_operator("*")
                }
                was_operator = true;
                break;
            case "/":
            case "+":
            case "-":
                if(was_operator){
                    throwException("A number has to be infront and before an operator")
                }
                op = get_operator(c);
                parser.pos++;
                was_operator = true;
            default:
                throwException("Use only operators or numbers")
    }
        
    }

}
