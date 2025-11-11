#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1

// Node for chaining
struct node {
    int data;
    struct node *next;
};

// ---------------- SEPARATE CHAINING ----------------
void insert_chain(struct node *ht[], int key) {
    int h = key % SIZE;
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->next = ht[h];
    ht[h] = newNode;
}

void display_chain(struct node *ht[]) {
    printf("\n(i) Separate Chaining:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("[%d] -> ", i);
        struct node *temp = ht[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ---------------- LINEAR PROBING ----------------
void insert_linear(int ht[], int key) {
    int h = key % SIZE;
    int i = 0;
    while (ht[(h + i) % SIZE] != EMPTY)
        i++;
    ht[(h + i) % SIZE] = key;
}

void display_linear(int ht[]) {
    printf("\n(ii) Open Addressing (Linear Probing):\n");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] -> %d\n", i, ht[i]);
}

// ---------------- QUADRATIC PROBING ----------------
void insert_quad(int ht[], int key) {
    int h = key % SIZE;
    int i = 0;
    while (ht[(h + i * i) % SIZE] != EMPTY)
        i++;
    ht[(h + i * i) % SIZE] = key;
}

void display_quad(int ht[]) {
    printf("\n(iii) Open Addressing (Quadratic Probing):\n");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] -> %d\n", i, ht[i]);
}

// ---------------- DOUBLE HASHING ----------------
int h2(int x) {
    return 7 - (x % 7);
}

void insert_double(int ht[], int key) {
    int h1 = key % SIZE;
    int h = h1;
    int step = h2(key);
    int i = 0;
    while (ht[h] != EMPTY) {
        i++;
        h = (h1 + i * step) % SIZE;
    }
    ht[h] = key;
}

void display_double(int ht[]) {
    printf("\n(iv) Open Addressing (Double Hashing):\n");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] -> %d\n", i, ht[i]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 0;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("File not found.\n");
        return 0;
    }

    int arr[50], n = 0;
    while (fscanf(fp, "%d", &arr[n]) == 1) n++;
    fclose(fp);

    printf("Input values:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // ----- Separate Chaining -----
    struct node *chain[SIZE] = {NULL};
    for (int i = 0; i < n; i++)
        insert_chain(chain, arr[i]);
    display_chain(chain);

    // ----- Linear Probing -----
    int linear[SIZE];
    for (int i = 0; i < SIZE; i++) linear[i] = EMPTY;
    for (int i = 0; i < n; i++)
        insert_linear(linear, arr[i]);
    display_linear(linear);

    // ----- Quadratic Probing -----
    int quad[SIZE];
    for (int i = 0; i < SIZE; i++) quad[i] = EMPTY;
    for (int i = 0; i < n; i++)
        insert_quad(quad, arr[i]);
    display_quad(quad);

    // ----- Double Hashing -----
    int dbl[SIZE];
    for (int i = 0; i < SIZE; i++) dbl[i] = EMPTY;
    for (int i = 0; i < n; i++)
        insert_double(dbl, arr[i]);
    display_double(dbl);

    return 0;
}
