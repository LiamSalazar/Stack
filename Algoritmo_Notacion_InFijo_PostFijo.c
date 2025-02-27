#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include".\Elem\ElemStr.h"
#include".\Pila\Pila.h"

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}
void infixToPostfix(Elem infix, Elem postfix) {
    Pila stack = empty();  
    int i = 0, k = 0;
    char ch;
    
    while ((ch = infix[i++]) != '\0') {
        if (!isOperator(ch) && ch != '(' && ch != ')') {  
            postfix[k++] = ch;
        } 
        else if (ch == '(') {  
            Elem temp = (Elem)malloc(sizeof(char));
            *temp = ch;
            stack = push(temp, stack);
        } 
        else if (ch == ')') {  
            while (!isempty(stack) && *(char*)top(stack) != '(') {
                postfix[k++] = *(char*)top(stack);
                stack = pop(stack);
            }
            if (!isempty(stack) && *(char*)top(stack) == '(') { 
                stack = pop(stack);
            }
        } 
        else if (isOperator(ch)) {
            while (!isempty(stack) && precedence(*(char*)top(stack)) >= precedence(ch)) {
                postfix[k++] = *(char*)top(stack);
                stack = pop(stack);
            }
            Elem temp = (Elem)malloc(sizeof(char));
            *temp = ch;
            stack = push(temp, stack);
        }
    }
    
    while (!isempty(stack)) {
        postfix[k++] = *(char*)top(stack);
        stack = pop(stack);
    }
    
    postfix[k] = '\0';  
}
int main() {
    printf("Introduce la expresión infija: ");
    Elem infix = LeeElem(100); 
    Elem postfix = (Elem)malloc(100 * sizeof(char));
    infixToPostfix(infix, postfix);
    printf("Expresión postfija: ");
    ImpElem(postfix); 
    return 0;
}
// (a+b)*c+(d*4+2)