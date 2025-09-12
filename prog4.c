#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THRESHOLD 1000  // Minimum size to trigger parallelism

// Merge Function
void merge(int arr[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *temp = (int *)malloc((r - l + 1) * sizeof(int));

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (i = l, k = 0; i <= r; i++, k++)
        arr[i] = temp[k];

    free(temp);
}

// Sequential Merge Sort
void sequentialMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort using OpenMP Sections
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        if (r - l + 1 <= THRESHOLD) {
            sequentialMergeSort(arr, l, r);
            return;
        }

        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main() {
    int n = 100000;
    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc(n * sizeof(int));

    // Seed and generate random array
    srand(42); // Fixed seed for consistent results
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % 10000;
        arr2[i] = arr1[i];  // Copy for fair comparison
    }

    double start, end;

    // Sequential Sort Timing
    start = omp_get_wtime();
    sequentialMergeSort(arr1, 0, n - 1);
    end = omp_get_wtime();
    printf("Sequential Merge Sort Time: %f seconds\n", end - start);

    // Parallel Sort Timing
    start = omp_get_wtime();
    parallelMergeSort(arr2, 0, n - 1);
    end = omp_get_wtime();
    printf("Parallel Merge Sort Time: %f seconds\n", end - start);

    free(arr1);
    free(arr2);

    return 0;
}
