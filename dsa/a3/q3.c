#include <stdio.h>
#include <stdlib.h>

long cmp = 0;  // count comparisons

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[50], R[50];

    // copy left and right halves
    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        cmp++;
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
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

    cmp = 0;
    mergeSort(a, 0, n - 1);

    printf("\nSorted array:\n");
    printArr(a, n);
    printf("Total comparisons: %ld\n", cmp);

    return 0;
}
