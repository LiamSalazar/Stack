#include <stdio.h>
#include".\Elem\ElemChar.h"

int isOperator(Elem ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

void separarPorLinea(Elem *operacion){
    for(int i = 0; operacion[i] != '\0'; i++){
        if(!isOperator(operacion[i]))
            printf("%c", operacion[i]);
        else if(isOperator(operacion[i+1]))
            printf("\n%c", operacion[i]);
        else
            printf("\n%c\n", operacion[i]);
    }
    
    puts("");
}

int main(){
    Elem *operacion = "(base*altura)////222*y+c-3";
    separarPorLinea(operacion);
}