#include <iostream>
using namespace std;

// prints the n values of arr on one line with spaces between them
void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        // no space after the last value
        if (k < n - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

// sorts arr with selection sort and counts comparisons and swaps
void selectionSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        // start with the first unsorted value as the smallest
        int minIdx = i;
        // look through the rest of the unsorted part for a smaller value
        for (int j = i + 1; j < n; j++) {
            comparisons = comparisons + 1;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // only swap if the minimum is not already in place
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            swaps = swaps + 1;
        }
        cout << "Pass " << i + 1 << ": min = " << arr[i]
             << " at index " << minIdx << " -> ";
        printArray(arr, n);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;
    int swaps = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    selectionSort(A, n, comparisons, swaps);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << " Swaps: " << swaps << endl;

    return 0;
}