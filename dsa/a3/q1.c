#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long cmp = 0, swp = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    swp++;
}

// ---- Pivot = First element ----
int part_first(int a[], int l, int h) {
    int p = a[l];
    int i = l + 1, j = h;

    while (1) {
        while (i <= h && a[i] <= p) { cmp++; i++; }
        while (a[j] > p) { cmp++; j--; }

        if (i < j)
            swap(&a[i], &a[j]);
        else
            break;
    }
    swap(&a[l], &a[j]);
    return j;
}

// ---- Pivot = Random element ----
int part_rand(int a[], int l, int h) {
    int r = l + rand() % (h - l + 1);
    swap(&a[l], &a[r]);
    return part_first(a, l, h);
}

// ---- Pivot = Median of three ----
int part_med3(int a[], int l, int h) {
    int m = (l + h) / 2;
    if (a[m] < a[l]) swap(&a[m], &a[l]);
    if (a[h] < a[l]) swap(&a[h], &a[l]);
    if (a[m] < a[h]) swap(&a[m], &a[h]);
    swap(&a[l], &a[h]);  // put pivot at start
    return part_first(a, l, h);
}

// ---- QuickSort ----
void qsort_custom(int a[], int l, int h, int type) {
    if (l < h) {
        int p;
        if (type == 1) p = part_first(a, l, h);
        else if (type == 2) p = part_rand(a, l, h);
        else p = part_med3(a, l, h);

        qsort_custom(a, l, p - 1, type);
        qsort_custom(a, p + 1, h, type);
    }
}

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
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

    srand(time(0));

    printf("Original:\n");
    printArr(a, n);

    // ---- (i) First element ----
    int b[100];
    for (int i = 0; i < n; i++) b[i] = a[i];
    cmp = swp = 0;
    qsort_custom(b, 0, n - 1, 1);
    printf("\n(i) First pivot:\n");
    printArr(b, n);
    printf("Comparisons = %ld, Swaps = %ld\n", cmp, swp);

    // ---- (ii) Random element ----
    for (int i = 0; i < n; i++) b[i] = a[i];
    cmp = swp = 0;
    qsort_custom(b, 0, n - 1, 2);
    printf("\n(ii) Random pivot:\n");
    printArr(b, n);
    printf("Comparisons = %ld, Swaps = %ld\n", cmp, swp);

    // ---- (iii) Median of three ----
    for (int i = 0; i < n; i++) b[i] = a[i];
    cmp = swp = 0;
    qsort_custom(b, 0, n - 1, 3);
    printf("\n(iii) Median-of-three pivot:\n");
    printArr(b, n);
    printf("Comparisons = %ld, Swaps = %ld\n", cmp, swp);

    return 0;
}
