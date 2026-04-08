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
    // Outer loop: controls how many passes we make through the array
    for (int i = 0; i < n - 1; i++) {
        // Track if a swap happened to optimize for already sorted data
        int swapped = 0; 
        
        // Inner loop: compares adjacent elements
        for (int j = 0; j < n - i - 1; j++) {
            // If the current element is bigger than the next one, swap them
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];       // Store current value in a temporary variable
                arr[j] = arr[j + 1];     // Move the smaller value to the left
                arr[j + 1] = temp;       // Move the larger value to the right
                swapped = 1;             // Mark that we performed a swap
            }
        }
        
        // If no swaps happened in a full pass, the array is already sorted
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
        key = arr[i];        // Element to be inserted
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;   // Insert key at correct position
    }
}


//===========================================================================================
// Merge Sort Function
//===========================================================================================

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays
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

    // Copy remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

//===========================================================================================
// QUICK SORT
//===========================================================================================

// Partition helper: places the pivot in the correct spot and moves smaller items left
int partition(int arr[], int low, int high) {
    int pivot = arr[high];          // Pick the last element as our "pivot" point
    int i = (low - 1);              // Index of the smaller element

    // Loop through the array from the first to the second-to-last element
    for (int j = low; j <= high - 1; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++;                    // Move the "smaller element index" forward
            int temp = arr[i];      // Swap current element with the element at index i
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Final step: Put the pivot in its correct sorted position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);                 // Return the position where the pivot ended up
}

// Main Quick Sort Function
void quickSort(int arr[], int low, int high) {
    // Base case: if low is not less than high, the segment is sorted
    if (low < high) {
        // pi is the partitioning index, arr[pi] is now at the right place
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after the partition
        quickSort(arr, low, pi - 1);  // Sort the left side
        quickSort(arr, pi + 1, high); // Sort the right side
    }
}

//===========================================================================================
// HEAP SORT
//===========================================================================================

// Heapify function to maintain the heap property
void heapify(int arr[], int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // left child
    int right = 2 * i + 2;  // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Heapify reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    // MAX_RANGE must be an unsigned long int constant
    const unsigned long int MAX_RANGE = 1000000UL;
    int N, choice, X;
    
    // Performance measurement variables
    clock_t start, end;
    double cpu_time_used;

    // Prompt for the number of integers (N)
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

    // Data generation selection
    printf("Select Data Generation Method:\n1. Randomly Generated Integers\n2. Increasing Sequence\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Option 1: Random data
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            original[i] = rand() % (MAX_RANGE + 1);
        }
    } else if (choice == 2) {
        // Option 2: User provides starting number X for increasing sequence
        printf("Enter starting value X: ");
        scanf("%d", &X);
        for (int i = 0; i < N; i++) {
            original[i] = X + i;
        }
    } else {
        printf("Invalid choice.\n");
        free(original); free(temp);
        return 1;
    }

    // Execution of the six sorting algorithms
    
    // SELECTION SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    selectionSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort: %f seconds\n", cpu_time_used);

    // BUBBLE SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    bubbleSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort: %f seconds\n", cpu_time_used);

    // INSERTION SORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    insertionSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Insertion Sort: %f seconds\n", cpu_time_used);

    // MERGESORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    mergeSort(temp, 0, N - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Mergesort: %f seconds\n", cpu_time_used);

    // QUICKSORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    quickSort(temp, 0, N - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Quicksort: %f seconds\n", cpu_time_used);

    // HEAPSORT
    for (int i = 0; i < N; i++) temp[i] = original[i];
    start = clock();
    heapSort(temp, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Heapsort: %f seconds\n", cpu_time_used);

    // Output file generation
    FILE *fout = fopen("output.txt", "w");
    if (fout != NULL) {
        fprintf(fout, "Original values:\n");
        for (int i = 0; i < N; i++) fprintf(fout, "%d ", original[i]);
        fprintf(fout, "\n\nSorted values (Final Run):\n");
        for (int i = 0; i < N; i++) fprintf(fout, "%d ", temp[i]);
        fclose(fout);
        printf("\nOriginal and sorted lists saved to 'output.txt'.\n");
    }

    free(original);
    free(temp);
    return 0;
}