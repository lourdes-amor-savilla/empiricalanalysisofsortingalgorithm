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
    int N, choice, X, fileChoice;
    char filename[100];
    char continueChoice;
    char *mode;
    
    clock_t start, end;
    double timeTaken;
    const char* algNames[] = {"Selection Sort", "Bubble Sort", "Insertion Sort", 
                              "Merge Sort", "Quick Sort", "Heap Sort"};

    printf("==============================================\n");
    printf("  SORTING ALGORITHM EMPIRICAL ANALYSIS\n");
    printf("==============================================\n\n");

    // Ask for filename once at the start of the session
    printf("Enter the name for your output file (e.g., Results_Log.txt): ");
    scanf("%s", filename);

    do {
        printf("\n--- NEW TEST RUN ---\n");
        printf("File Options for '%s':\n", filename);
        printf("1. Create New / Overwrite\n");
        printf("2. Append to Existing\n");
        printf("Enter choice (1 or 2): ");
        scanf("%d", &fileChoice);

        mode = (fileChoice == 2) ? "a" : "w";

        printf("\nEnter the number of integers to be sorted (N): ");
        if (scanf("%d", &N) != 1 || N <= 0) {
            printf("Invalid input. Ending run.\n");
            break;
        }

        int *original = (int *)malloc(N * sizeof(int));
        int *temp = (int *)malloc(N * sizeof(int));
        if (original == NULL || temp == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("\nSelect Data Generation Method:\n");
        printf("1. Randomly Generated Integers\n");
        printf("2. Increasing Sequence\n");
        printf("Enter choice (1 or 2): ");
        scanf("%d", &choice);

        if (choice == 1) {
            srand(time(NULL));
            for (int i = 0; i < N; i++) {
                original[i] = rand() % (MAX_RANGE + 1);
            }
            printf("\n[Data Generation] Random integers generated from [0, %lu]\n", MAX_RANGE);
        } else if (choice == 2) {
            printf("Enter starting value X: ");
            scanf("%d", &X);
            for (int i = 0; i < N; i++) {
                original[i] = X + i;
            }
            printf("\n[Data Generation] Increasing sequence starting from %d\n", X);
        }

        // Open file to log the Unsorted Array first
        FILE *fout = fopen(filename, mode);
        if (fout != NULL) {
            fprintf(fout, "========================================================\n");
            fprintf(fout, "TEST RUN: N = %d | Mode: %s\n", N, (choice == 1 ? "Random" : "Increasing"));
            fprintf(fout, "========================================================\n\n");
            fprintf(fout, "UNSORTED ORIGINAL ARRAY:\n");
            for (int i = 0; i < N; i++) {
                fprintf(fout, "%d ", original[i]);
                if ((i + 1) % 20 == 0) fprintf(fout, "\n");
            }
            fprintf(fout, "\n\n--------------------------------------------------------\n");
        }

        printf("\n%-20s %20s\n", "Algorithm", "Time (seconds)");
        printf("%-20s %20s\n", "----------", "--------------");

        // --- SORTING AND INDIVIDUAL LOGGING ---

        // 1. Selection Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); selectionSort(temp, N); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[0], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[0]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        // 2. Bubble Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); bubbleSort(temp, N); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[1], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[1]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        // 3. Insertion Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); insertionSort(temp, N); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[2], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[2]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        // 4. Merge Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); mergeSort(temp, 0, N - 1); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[3], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[3]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        // 5. Quick Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); quickSort(temp, 0, N - 1); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[4], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[4]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        // 6. Heap Sort
        for (int i = 0; i < N; i++) temp[i] = original[i];
        start = clock(); heapSort(temp, N); end = clock();
        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %20.6f\n", algNames[5], timeTaken);
        if (fout) {
            fprintf(fout, ">>> ALGORITHM: %s\n", algNames[5]);
            fprintf(fout, "TIME TAKEN: %.6f seconds\n", timeTaken);
            fprintf(fout, "SORTED ARRAY:\n");
            for (int i = 0; i < N; i++) { fprintf(fout, "%d ", temp[i]); if ((i + 1) % 20 == 0) fprintf(fout, "\n"); }
            fprintf(fout, "\n\n");
        }

        if (fout) {
            fprintf(fout, "--- END OF RUN ---\n\n\n");
            fclose(fout);
            printf("\nResults logged to '%s'.\n", filename);
        }

        free(original);
        free(temp);

        printf("\nWould you like to perform another run? (y/n): ");
        scanf(" %c", &continueChoice);

    } while (continueChoice == 'y' || continueChoice == 'Y');

    printf("\nExiting. GGWP!\n");
    return 0;
}
