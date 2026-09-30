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

// prints 2 spaces for each level of recursion
void printIndent(int depth) {
    for (int s = 0; s < depth; s++) {
        cout << "  ";
    }
}

// puts the pivot (last value) in its final spot and returns that index
int partition(int arr[], int low, int high, bool showSteps, int &comparisons) {
    int pivot = arr[high];
    // i is the end of the part that is <= pivot, it starts empty
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons = comparisons + 1;
        // grow the <= pivot part and move arr[j] into it
        if (arr[j] <= pivot) {
            i = i + 1;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            // only print the steps for the first partition
            if (showSteps == true) {
                cout << "i = " << i << ", j = " << j << ": ";
                printArray(arr + low, high - low + 1);
            }
        }
    }
    // put the pivot right after the <= pivot part
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    if (showSteps == true) {
        cout << "pivot placed: ";
        printArray(arr + low, high - low + 1);
        cout << "pivot final position: " << i + 1 << endl;
    }
    return i + 1;
}

// sorts arr[low..high] with quick sort, depth is used for the indent
void quickSort(int arr[], int low, int high, int depth, int &comparisons) {
    // a part with 0 or 1 values is already sorted
    if (low < high) {
        printIndent(depth);
        cout << "pivot = " << arr[high] << ": ";
        printArray(arr + low, high - low + 1);
        // depth 0 is the first partition
        bool showSteps = (depth == 0);
        int p = partition(arr, low, high, showSteps, comparisons);
        // sort the left side and then the right side of the pivot
        quickSort(arr, low, p - 1, depth + 1, comparisons);
        quickSort(arr, p + 1, high, depth + 1, comparisons);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    comparisons = 0;
    quickSort(A, 0, n - 1, 0, comparisons);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << endl;
    // A is sorted now, so copying it gives a sorted copy of A
    int B[8];
    for (int k = 0; k < n; k++) {
        B[k] = A[k];
    }

    // Test 2: an already sorted copy of A (worst case)
    cout << endl << "Test 2: already sorted copy of A" << endl;
    cout << "Original: ";
    printArray(B, n);
    comparisons = 0;
    quickSort(B, 0, n - 1, 0, comparisons);
    cout << "Sorted: ";
    printArray(B, n);
    cout << "Comparisons: " << comparisons << endl;

    return 0;
}