#include <iostream>
#include <vector>
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

// merges the sorted parts arr[low..mid] and arr[mid+1..high]
void merge(int arr[], int low, int mid, int high, int &comparisons) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    // copy the two halves into L and R
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
    // take the smaller front value, <= keeps equal values in order
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
    // copy whatever is left, no comparisons needed
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
    cout << "merged: ";
    printArray(arr + low, high - low + 1);
}

// sorts arr[low..high] with merge sort, depth 0 is the top call
void mergeSort(int arr[], int low, int high, int depth, int &comparisons, int &finalMerge) {
    if (low < high) {
        cout << "split: ";
        printArray(arr + low, high - low + 1);
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid, depth + 1, comparisons, finalMerge);
        mergeSort(arr, mid + 1, high, depth + 1, comparisons, finalMerge);
        // save the count so the final merge can be counted alone
        int before = comparisons;
        merge(arr, low, mid, high, comparisons);
        if (depth == 0) {
            finalMerge = comparisons - before;
        }
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;
    int finalMerge = 0;

    // Test 1: the original array A
    cout << "Test 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(A, 0, n - 1, 0, comparisons, finalMerge);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << " (final merge: "
         << finalMerge << ")" << endl;
    // A is sorted now, so B is a sorted copy and C is a reversed copy
    int B[8];
    int C[8];
    for (int k = 0; k < n; k++) {
        B[k] = A[k];
        C[k] = A[n - 1 - k];
    }

    // Test 2: a sorted copy of A
    cout << endl << "Test 2: sorted copy of A" << endl;
    cout << "Original: ";
    printArray(B, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(B, 0, n - 1, 0, comparisons, finalMerge);
    cout << "Sorted: ";
    printArray(B, n);
    cout << "Comparisons: " << comparisons << " (final merge: "
         << finalMerge << ")" << endl;

    // Test 3: a reversed copy of A
    cout << endl << "Test 3: reversed copy of A" << endl;
    cout << "Original: ";
    printArray(C, n);
    comparisons = 0;
    finalMerge = 0;
    mergeSort(C, 0, n - 1, 0, comparisons, finalMerge);
    cout << "Sorted: ";
    printArray(C, n);
    cout << "Comparisons: " << comparisons << " (final merge: "
         << finalMerge << ")" << endl;

    return 0;
}