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

// moves arr[root] down until it is bigger than both children
void siftDown(int arr[], int root, int size, int &swaps) {
    int largest = root;
    // children of root in the array
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }
    // swap with the bigger child and keep going from there
    if (largest != root) {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        swaps = swaps + 1;
        siftDown(arr, largest, size, swaps);
    }
}

// sorts arr with heap sort and counts swaps inside siftDown
void heapSort(int arr[], int n, int &swaps) {
    swaps = 0;
    // build the max-heap starting from the last parent
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n, swaps);
    }
    cout << "Heap: ";
    printArray(arr, n);
    // move the root (the max) to the end and fix the heap that is left
    for (int end = n - 1; end >= 1; end--) {
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;
        siftDown(arr, 0, end, swaps);
        cout << "end = " << end << ": heap: ";
        printArray(arr, end);
        cout << "         sorted: ";
        printArray(arr + end, n - end);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int swaps = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    heapSort(A, n, swaps);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Swaps in siftDown: " << swaps << endl;

    return 0;
}