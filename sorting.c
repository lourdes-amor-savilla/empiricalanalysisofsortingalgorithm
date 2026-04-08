#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//=========================================================================================
//Selection Sort Function
//========================================================================================

void selectionSort(int arr[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

//===========================================================================================
// Bubble Sort Function
//===========================================================================================

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0; 
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        if (swapped == 0) {
            break;
        }
    }
}

//===========================================================================================
//Insertion Sort Function
//===========================================================================================

void insertionSort(int arr[], int n) {
    int i, key, j;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

//===========================================================================================
// Merge Sort Function
//===========================================================================================

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

//===========================================================================================
// QUICK SORT
//===========================================================================================

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//===========================================================================================
// HEAP SORT
//===========================================================================================

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

//===========================================================================================
// Main Program
//===========================================================================================

int main() {
    const unsigned long int MAX_RANGE = 1000000UL;
    int N, choice, X;
    
    clock_t start, end;
    double cpu_time_used;

    printf("==============================================\n");
    printf("  SORTING ALGORITHM EMPIRICAL ANALYSIS\n");
    printf("==============================================\n\n");

    // USER INPUT: Get N
    printf("Enter the number of integers to be sorted (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Allocate memory for the arrays
    int *original = (int *)malloc(N * sizeof(int));
    int *temp = (int *)malloc(N * sizeof(int));
    if (original == NULL || temp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // USER INPUT: Data generation selection
    printf("\nSelect Data Generation Method:\n");
    printf("1. Randomly Generated Integers\n");
    printf("2. Increasing Sequence\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Option 1: Random data
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            original[i] = rand() % (MAX_RANGE + 1);
        }
        printf("\n[Data Generation] Random integers generated from [0, %lu]\n", MAX_RANGE);
    } else if (choice == 2) {
        // Option 2: Increasing sequence
        printf("Enter starting value X: ");
        scanf("%d", &X);
        for (int i = 0; i < N; i++) {
            original[i] = X + i;
        }
        printf("\n[Data Generation] Increasing sequence generated starting from %d\n", X);
    } else {
        printf("Invalid choice.\n");
        free(original); 
        free(temp);
        return 1;
    }

    printf("\n==============================================\n");
    printf("  SORTING AND TIMING RESULTS FOR N = %d\n", N);
    printf("==============================================\n");
    printf("%-20s %20s\n", "Algorithm", "Time (seconds)");
    printf("%-20s %20s\n", "----------", "--------------");

    // SELECTION SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    selectionSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Selection Sort", cpu_time_used);

    // BUBBLE SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    bubbleSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Bubble Sort", cpu_time_used);

    // INSERTION SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    insertionSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Insertion Sort", cpu_time_used);

    // MERGESORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    mergeSort(temp, 0, N - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Merge Sort", cpu_time_used);

    // QUICKSORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    quickSort(temp, 0, N - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Quick Sort", cpu_time_used);

    // HEAPSORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    heapSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%-20s %20.6f\n", "Heap Sort", cpu_time_used);

    printf("\n");

    // OUTPUT FILE: Write original and sorted values
    FILE *fout = fopen("output.txt", "w");
    if (fout != NULL) {
        fprintf(fout, "Original values:\n");
        for (int i = 0; i < N; i++) {
            fprintf(fout, "%d ", original[i]);
            if ((i + 1) % 20 == 0) fprintf(fout, "\n");
        }
        fprintf(fout, "\n\nSorted values (Final Run):\n");
        for (int i = 0; i < N; i++) {
            fprintf(fout, "%d ", temp[i]);
            if ((i + 1) % 20 == 0) fprintf(fout, "\n");
        }
        fprintf(fout, "\n");
        fclose(fout);
        printf("Original and sorted lists saved to 'output.txt'.\n");
    }

    free(original);
    free(temp);
    return 0;
}
