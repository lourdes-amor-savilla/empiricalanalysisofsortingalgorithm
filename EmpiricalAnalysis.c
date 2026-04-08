#include <stdio.h>

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



// Bubble Sort Function
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

// Function to heapify a subtree rooted at index i
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

 int main()
 {

 }