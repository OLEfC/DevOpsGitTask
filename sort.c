#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void bubbleSort(int* arr, int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}





int main() {
    int n = 50000;
    int* arr = malloc(n * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    clock_t start, end;

    start = clock();
    bubbleSort(arr, n);
    end = clock();
    printf("Bubble Sort Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    printf("Merge Sort Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    
    free(arr);

    return 0;
}
