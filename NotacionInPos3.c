#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include".\Elem\ElemChar.h"
#include".\Pila\Pila.h"

int isOperator(Elem ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(Elem op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

void infixToPostfix(Elem *infix, Elem *postfix) {
    Pila stack = empty();
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        Elem ch = infix[i];
        if (!isOperator(ch) && ch != '(' && ch != ')') {
            postfix[k++] = ch;
        } else if (ch == '(') {
            stack = push(ch, stack);
        } else if (ch == ')') {
            while (!isempty(stack) && top(stack) != '(') {
                postfix[k++] = top(stack);
                stack = pop(stack);
            }
            stack = pop(stack); 
        } else if (isOperator(ch)) {
            while (!isempty(stack) && precedence(top(stack)) >= precedence(ch)) {
                postfix[k++] = top(stack);
                stack = pop(stack);
            }
            stack = push(ch, stack);
        }
    }
    while (!isempty(stack)) {
        postfix[k++] = top(stack);
        stack = pop(stack);
    }
    postfix[k] = '\0'; 
}
int main() {
    Elem *infix = "(A+B)*C+(D*4+2)";
    Elem postfix[100]; 
    infixToPostfix(infix, postfix);
    printf("Expresión infija: %s\n", infix);
    printf("Expresión postfija: %s\n", postfix);

    return 0;
}