#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue operation
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued: %d\n", value);
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    printf("Dequeued: %d\n", value);
    return value;
}

// Display queue
void display(Queue* q) {
    printf("Queue: ");
    if (isEmpty(q)) {
        printf("Empty\n");
        return;
    }
    Node* temp = q->front;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Save queue to file
void saveQueueToFile(Queue* q, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    Node* temp = q->front;
    while (temp) {
        fprintf(fp, "%d\n", temp->data);
        temp = temp->next;
    }
    fclose(fp);
    printf("Queue saved to file %s\n", filename);
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

    Queue q;
    initQueue(&q);

    int num;
    while (fscanf(fp, "%d", &num) != EOF) {
        enqueue(&q, num); // Initially load all elements from file
    }
    fclose(fp);

    int choice, value;
    char saveFile[100];
    do {
        printf("\n--- Queue Menu ---\n");
        printf("1. Enter no into queue\n");
        printf("2. Delete no from queue\n");
        printf("3. Display Queue\n");
        printf("4. Save Queue to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Enter filename to save: ");
                scanf("%s", saveFile);
                saveQueueToFile(&q, saveFile);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
