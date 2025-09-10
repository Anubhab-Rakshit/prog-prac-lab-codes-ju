#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30
#define STACKS 3
#define STACK_SIZE (MAX / STACKS)

typedef struct {
    int arr[MAX];
    int top[STACKS];
} ThreeStacks;

void initStacks(ThreeStacks* s) {
    for (int i = 0; i < STACKS; i++)
        s->top[i] = -1;
}

int isFull(ThreeStacks* s, int stackNum) {
    return s->top[stackNum] == STACK_SIZE - 1;
}

int isEmpty(ThreeStacks* s, int stackNum) {
    return s->top[stackNum] == -1;
}

void push(ThreeStacks* s, int stackNum, int value) {
    if (isFull(s, stackNum)) {
        printf("Stack %d is full, cannot push %d\n", stackNum + 1, value);
        return;
    }
    int index = stackNum * STACK_SIZE + (++s->top[stackNum]);
    s->arr[index] = value;
    printf("Pushed %d into Stack %d\n", value, stackNum + 1);
}

int pop(ThreeStacks* s, int stackNum) {
    if (isEmpty(s, stackNum)) {
        printf("Stack %d is empty, cannot pop\n", stackNum + 1);
        return -1;
    }
    int index = stackNum * STACK_SIZE + (s->top[stackNum]--);
    int value = s->arr[index];
    printf("Popped %d from Stack %d\n", value, stackNum + 1);
    return value;
}

void display(ThreeStacks* s) {
    for (int i = 0; i < STACKS; i++) {
        printf("Stack %d: ", i + 1);
        if (isEmpty(s, i)) {
            printf("Empty");
        } else {
            for (int j = 0; j <= s->top[i]; j++)
                printf("%d ", s->arr[i * STACK_SIZE + j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    ThreeStacks s;
    initStacks(&s);
    srand(time(NULL));

    char op;
    int value;
    while (fscanf(fp, " %c", &op) != EOF) {
        int stackNum = rand() % STACKS; // randomly choose stack

        if (op == 'E') {
            fscanf(fp, "%d", &value); // read value for push
            push(&s, stackNum, value);
        } else if (op == 'D') {
            pop(&s, stackNum);
        } else {
            printf("Unknown operation: %c\n", op);
        }
    }

    fclose(fp);

    printf("\nFinal stacks state:\n");
    display(&s);

    return 0;
}
