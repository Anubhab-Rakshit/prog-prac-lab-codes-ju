#include <stdio.h>
#include <stdlib.h>

long swp = 0;

// swap two elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    swp++;
}

// heapify a subtree rooted at i
void heapify(int a[], int n, int i) {
    int largest = i;  
    int l = 2 * i + 1;  
    int r = 2 * i + 2;  

    if (l < n && a[l] > a[largest])
        largest = l;

    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

// heap sort function
void heapSort(int a[], int n) {
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
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

    int a[100], n = 0;
    while (fscanf(fp, "%d", &a[n]) == 1) n++;
    fclose(fp);

    printf("Original array:\n");
    printArr(a, n);

    swp = 0;
    heapSort(a, n);

    printf("\nSorted array:\n");
    printArr(a, n);
    printf("Total swaps: %ld\n", swp);

    return 0;
}
