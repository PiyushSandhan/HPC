#include <iostream>
#include <omp.h>

using namespace std;

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        // Parallelize the outer loop
        #pragma omp parallel for shared(arr, swapped)
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

// Driver program to test above functions
int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int N = sizeof(arr) / sizeof(arr[0]);
    cout << "Original array: ";
    printArray(arr, N);
    bubbleSort(arr, N);
    cout << "\nSorted array: ";
    printArray(arr, N);
    return 0;
}
