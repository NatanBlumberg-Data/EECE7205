#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
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

// copies n values from source into target
void copyArray(int source[], int target[], int n) {
    for (int k = 0; k < n; k++) {
        target[k] = source[k];
    }
}

// the six sorts from Problems 1 to 6 with the printing taken out
void bubbleSort(int arr[], int n, int &comparisons) {
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
        for (int i = 0; i < n - pass - 1; i++) {
            comparisons = comparisons + 1;
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
}

void insertionSort(int arr[], int n, int &comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons = comparisons + 1;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n, int &comparisons) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons = comparisons + 1;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

int partition(int arr[], int low, int high, int &comparisons) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons = comparisons + 1;
        if (arr[j] <= pivot) {
            i = i + 1;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high, int &comparisons) {
    if (low < high) {
        int p = partition(arr, low, high, comparisons);
        quickSort(arr, low, p - 1, comparisons);
        quickSort(arr, p + 1, high, comparisons);
    }
}

void merge(int arr[], int low, int mid, int high, int &comparisons) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    vector<int> L(n1);
    vector<int> R(n2);
    for (int a = 0; a < n1; a++) {
        L[a] = arr[low + a];
    }
    for (int b = 0; b < n2; b++) {
        R[b] = arr[mid + 1 + b];
    }
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2) {
        comparisons = comparisons + 1;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i = i + 1;
        } else {
            arr[k] = R[j];
            j = j + 1;
        }
        k = k + 1;
    }
    while (i < n1) {
        arr[k] = L[i];
        i = i + 1;
        k = k + 1;
    }
    while (j < n2) {
        arr[k] = R[j];
        j = j + 1;
        k = k + 1;
    }
}

void mergeSort(int arr[], int low, int high, int &comparisons) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid, comparisons);
        mergeSort(arr, mid + 1, high, comparisons);
        merge(arr, low, mid, high, comparisons);
    }
}

// this siftDown counts comparisons instead of swaps
void siftDown(int arr[], int root, int size, int &comparisons) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if (left < size) {
        comparisons = comparisons + 1;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }
    if (right < size) {
        comparisons = comparisons + 1;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }
    if (largest != root) {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        siftDown(arr, largest, size, comparisons);
    }
}

void heapSort(int arr[], int n, int &comparisons) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n, comparisons);
    }
    for (int end = n - 1; end >= 1; end--) {
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;
        siftDown(arr, 0, end, comparisons);
    }
}

// runs sort number which (0 to 5) on arr
void runSort(int which, int arr[], int n, int &comparisons) {
    if (which == 0) {
        bubbleSort(arr, n, comparisons);
    } else if (which == 1) {
        insertionSort(arr, n, comparisons);
    } else if (which == 2) {
        selectionSort(arr, n, comparisons);
    } else if (which == 3) {
        quickSort(arr, 0, n - 1, comparisons);
    } else if (which == 4) {
        mergeSort(arr, 0, n - 1, comparisons);
    } else {
        heapSort(arr, n, comparisons);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    // S is A in sorted order and R is A in reversed order
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int R[8];
    for (int k = 0; k < n; k++) {
        R[k] = S[n - 1 - k];
    }

    string names[6] = {"Bubble   ", "Insertion", "Selection",
                       "Quick    ", "Merge    ", "Heap     "};
    // Part 1
    cout << "Part 1: comparisons on A, sorted A, and reversed A" << endl;
    cout << "Algorithm\tA\tSorted\tReversed" << endl;
    int B[8];
    for (int w = 0; w < 6; w++) {
        int comparisons = 0;
        cout << names[w];

        // Test 1: the original array A
        copyArray(A, B, n);
        comparisons = 0;
        runSort(w, B, n, comparisons);
        cout << "\t" << comparisons;

        // Test 2: a sorted copy of A
        copyArray(S, B, n);
        comparisons = 0;
        runSort(w, B, n, comparisons);
        cout << "\t" << comparisons;

        // Test 3: a reversed copy of A
        copyArray(R, B, n);
        comparisons = 0;
        runSort(w, B, n, comparisons);
        cout << "\t" << comparisons << endl;
    }

    // Part 2
    // Part 2: fixed seed so the random data is the same every run
    mt19937 generator(7205);
    uniform_int_distribution<int> distribution(1, 100000);
    int sizes[3] = {1000, 5000, 10000};
    int randomData[10000];
    int work[10000];
    cout << endl << "Part 2: running time on random arrays" << endl;
    for (int s = 0; s < 3; s++) {
        int m = sizes[s];
        for (int k = 0; k < m; k++) {
            // make the random data once so all six sorts get the same input
            randomData[k] = distribution(generator);
        }
        cout << endl << "n = " << m << endl;
        for (int w = 0; w < 6; w++) {
            // fresh copy for every sort
            copyArray(randomData, work, m);
            int comparisons = 0;
            chrono::steady_clock::time_point start;
            chrono::steady_clock::time_point stop;
            // only the sort is timed, not the copy
            start = chrono::steady_clock::now();
            runSort(w, work, m, comparisons);
            stop = chrono::steady_clock::now();
            double ms = chrono::duration<double, milli>(stop - start).count();
            cout << names[w] << "  time: " << ms << " ms  comparisons: "
                 << comparisons << endl;
            cout << "  first 10: ";
            // print the first 10 values to check the sort
            printArray(work, 10);
        }
    }

    return 0;
}