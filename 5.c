#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>   // for strlen()

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void push(Stack* s, int val) {
    s->arr[++s->top] = val;
}

int pop(Stack* s) {
    return s->arr[s->top--];
}

int evaluatePostfix(char* exp) {
    Stack s;
    s.top = -1;

    for (int i = 0; exp[i]; i++) {
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');  // single digit operand
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            int b = pop(&s);
            int a = pop(&s);
            switch (exp[i]) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
                case '/': push(&s, a / b); break;
            }
        }
        // ignore other characters
    }
    return pop(&s);
}

int main() {
    char exp[MAX];

    printf("Enter postfix expression: ");
    fgets(exp, MAX, stdin);

    // remove newline if present
    size_t len = strlen(exp);
    if (len > 0 && exp[len - 1] == '\n') {
        exp[len - 1] = '\0';
    }

    printf("Postfix: %s\n", exp);
    printf("Evaluated result = %d\n", evaluatePostfix(exp));

    return 0;
}
