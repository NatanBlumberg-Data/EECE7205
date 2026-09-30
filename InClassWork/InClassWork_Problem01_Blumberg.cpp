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

// sorts arr with bubble sort and counts passes, comparisons, and swaps
void bubbleSort(int arr[], int n, int &passes, int &comparisons, int &swaps) {
    passes = 0;
    comparisons = 0;
    swaps = 0;
    for (int pass = 0; pass < n - 1; pass++) {
        // swapped stays false if this pass makes no swaps
        bool swapped = false;
        // the last values are already in place so the pass stops before them
        for (int i = 0; i < n - pass - 1; i++) {
            comparisons = comparisons + 1;
            // swap the two neighbors if they are in the wrong order
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swaps = swaps + 1;
                swapped = true;
            }
        }
        passes = passes + 1;
        cout << "Pass " << passes << ": ";
        printArray(arr, n);
        // no swaps means the array is sorted so stop early
        if (swapped == false) {
            break;
        }
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int passes = 0;
    int comparisons = 0;
    int swaps = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    bubbleSort(A, n, passes, comparisons, swaps);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Passes: " << passes << " Comparisons: " << comparisons
         << " Swaps: " << swaps << endl;
    // A is sorted now, so copying it gives a sorted copy of A
    int B[8];
    for (int k = 0; k < n; k++) {
        B[k] = A[k];
    }

    // Test 2: an already sorted copy of A (best case)
    cout << endl << "Test 2: already sorted copy of A" << endl;
    cout << "Original: ";
    printArray(B, n);
    bubbleSort(B, n, passes, comparisons, swaps);
    cout << "Sorted: ";
    printArray(B, n);
    cout << "Passes: " << passes << " Comparisons: " << comparisons
         << " Swaps: " << swaps << endl;

    return 0;
}