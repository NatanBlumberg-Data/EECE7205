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

// sorts arr with insertion sort and counts comparisons and shifts
void insertionSort(int arr[], int n, int &comparisons, int &shifts) {
    comparisons = 0;
    shifts = 0;
    for (int i = 1; i < n; i++) {
        // key is the value being inserted into the sorted part on the left
        int key = arr[i];
        int j = i - 1;
        // the value test is inside the loop so the test that fails is counted too
        while (j >= 0) {
            comparisons = comparisons + 1;
            if (arr[j] > key) {
                // move the bigger value one spot to the right
                arr[j + 1] = arr[j];
                shifts = shifts + 1;
                j = j - 1;
            } else {
                break;
            }
        }
        // put key in the gap
        arr[j + 1] = key;
        cout << "i = " << i << ", key = " << key << ": ";
        printArray(arr, n);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;
    int shifts = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    insertionSort(A, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl;
    // A is sorted now, so B gets increasing order and C gets decreasing order
    int B[8];
    int C[8];
    for (int k = 0; k < n; k++) {
        B[k] = A[k];
        C[k] = A[n - 1 - k];
    }

    // Test 2: increasing order (fewest shifts)
    cout << endl << "Test 2: increasing order" << endl;
    cout << "Original: ";
    printArray(B, n);
    insertionSort(B, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(B, n);
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl;

    // Test 3: decreasing order (most shifts)
    cout << endl << "Test 3: decreasing order" << endl;
    cout << "Original: ";
    printArray(C, n);
    insertionSort(C, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(C, n);
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl;

    return 0;
}