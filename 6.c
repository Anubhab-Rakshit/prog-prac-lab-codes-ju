#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char* arr[MAX];
    int top;
} Stack;

void push(Stack* s, char* str) {
    s->arr[++s->top] = str;
}

char* pop(Stack* s) {
    return s->arr[s->top--];
}

char* postfixToInfix(char* exp) {
    Stack s; 
    s.top = -1;

    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            char* op = (char*)malloc(2);
            op[0] = exp[i];
            op[1] = '\0';
            push(&s, op);
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            char* b = pop(&s);
            char* a = pop(&s);
            char* newExp = (char*)malloc(strlen(a) + strlen(b) + 4);
            sprintf(newExp, "(%s%c%s)", a, exp[i], b);
            push(&s, newExp);
        }
        // ignore spaces/newlines
    }
    return pop(&s);
}

int main() {
    char exp[MAX];

    printf("Enter postfix expression: ");
    fgets(exp, MAX, stdin);

    // remove newline at the end
    size_t len = strlen(exp);
    if (len > 0 && exp[len - 1] == '\n') {
        exp[len - 1] = '\0';
    }

    printf("Postfix: %s\n", exp);
    char* infix = postfixToInfix(exp);
    printf("Infix: %s\n", infix);

    return 0;
}
