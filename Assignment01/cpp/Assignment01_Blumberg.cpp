#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Problem 1: Merge Overlapping Intervals
// Interval is also used by Problem 5
struct Interval {
    int start;
    int end;
};

vector<Interval> mergeIntervalHalves(vector<Interval> left, vector<Interval> right) {
    vector<Interval> result;
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        // <= keeps intervals with equal starts in their original order
        if (left[i].start <= right[j].start) {
            result.push_back(left[i]); i++;
        } else {
            result.push_back(right[j]); j++;
        }
    }
    while (i < leftSize) {
        result.push_back(left[i]); i++;
    }
    while (j < rightSize) {
        result.push_back(right[j]); j++;
    }
    return result;
}

vector<Interval> mergeSortIntervals(vector<Interval> items) {
    int n = items.size();
    if (n <= 1) {
        return items;
    }
    int middle = n / 2;
    vector<Interval> left;
    vector<Interval> right;
    for (int i = 0; i < middle; i++) {
        left.push_back(items[i]);
    }
    for (int i = middle; i < n; i++) {
        right.push_back(items[i]);
    }
    left = mergeSortIntervals(left);
    right = mergeSortIntervals(right);
    return mergeIntervalHalves(left, right);
}

vector<Interval> mergeOverlappingIntervals(vector<Interval> intervals) {
    vector<Interval> result;
    int n = intervals.size();
    if (n == 0) {
        return result;
    }
    intervals = mergeSortIntervals(intervals);
    result.push_back(intervals[0]);
    for (int i = 1; i < n; i++) {
        int lastIndex = result.size() - 1;
        if (intervals[i].start <= result[lastIndex].end) {
            if (intervals[i].end > result[lastIndex].end) {
                result[lastIndex].end = intervals[i].end;
            }
        } else {
            result.push_back(intervals[i]);
        }
    }
    return result;
}

// Problem 2: Sort an array of 0s, 1s, and 2s
vector<int> sortColorsCounting(vector<int> nums) {
    int n = nums.size();
    int countZero = 0;
    int countOne = 0;
    int countTwo = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            countZero++;
        } else if (nums[i] == 1) {
            countOne++;
        } else {
            countTwo++;
        }
    }
    int index = 0;
    for (int i = 0; i < countZero; i++) {
        nums[index] = 0; index++;
    }
    for (int i = 0; i < countOne; i++) {
        nums[index] = 1; index++;
    }
    for (int i = 0; i < countTwo; i++) {
        nums[index] = 2; index++;
    }
    return nums;
}

vector<int> sortColorsDutchFlag(vector<int> nums) {
    int n = nums.size();
    int low = 0;
    int mid = 0;
    int high = n - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            int temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            int temp = nums[mid];
            nums[mid] = nums[high];
            nums[high] = temp;
            high--;
        }
    }
    return nums;
}

// Problem 3: Largest Number from Concatenation
bool numberGoesFirst(string a, string b) {
    return (a + b) >= (b + a);
}

vector<string> mergeStringHalves(vector<string> left, vector<string> right) {
    vector<string> result;
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        if (numberGoesFirst(left[i], right[j])) {
            result.push_back(left[i]); i++;
        } else {
            result.push_back(right[j]); j++;
        }
    }
    while (i < leftSize) {
        result.push_back(left[i]); i++;
    }
    while (j < rightSize) {
        result.push_back(right[j]); j++;
    }
    return result;
}

vector<string> mergeSortNumberStrings(vector<string> words) {
    int n = words.size();
    if (n <= 1) {
        return words;
    }
    int middle = n / 2;
    vector<string> left;
    vector<string> right;
    for (int i = 0; i < middle; i++) {
        left.push_back(words[i]);
    }
    for (int i = middle; i < n; i++) {
        right.push_back(words[i]);
    }
    left = mergeSortNumberStrings(left);
    right = mergeSortNumberStrings(right);
    return mergeStringHalves(left, right);
}

string largestNumber(vector<int> nums) {
    int n = nums.size();
    if (n == 0) {
        return "0";
    }
    vector<string> texts;
    for (int i = 0; i < n; i++) {
        texts.push_back(to_string(nums[i]));
    }
    texts = mergeSortNumberStrings(texts);
    string result = "";
    for (int i = 0; i < n; i++) {
        // += adds to the end in place instead of copying the whole string each time
        result += texts[i];
    }
    // if the biggest value is a zero then every value was a zero,
    // so the answer is one plain "0" instead of something like "00"
    if (result[0] == '0') {
        return "0";
    }
    return result;
}

// Problem 4: Group Anagrams
string mergeLetterHalves(string left, string right) {
    string result = "";
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            result += left[i]; i++;
        } else {
            result += right[j]; j++;
        }
    }
    while (i < leftSize) {
        result += left[i]; i++;
    }
    while (j < rightSize) {
        result += right[j]; j++;
    }
    return result;
}

string sortLetters(string word) {
    // merge sort on the letters of one word
    int n = word.size();
    if (n <= 1) {
        return word;
    }
    int middle = n / 2;
    string left = "";
    string right = "";
    for (int i = 0; i < middle; i++) {
        left += word[i];
    }
    for (int i = middle; i < n; i++) {
        right += word[i];
    }
    left = sortLetters(left);
    right = sortLetters(right);
    return mergeLetterHalves(left, right);
}

int hashOfText(string key) {
    // adds up the letter codes and keeps the result between 0 and 100
    int total = 0;
    int n = key.size();
    for (int i = 0; i < n; i++) {
        total = total + (int)key[i];
    }
    if (total < 0) {
        total = -total;
    }
    return total % 101;
}

vector<vector<string>> groupAnagrams(vector<string> words) {
    vector<string> keys;                 // the sorted letters of each group
    vector<vector<string>> groups;       // the words belonging to each group
    vector<vector<int>> buckets;         // hand built hash table of group numbers

    for (int i = 0; i < 101; i++) {
        vector<int> emptyBucket;
        buckets.push_back(emptyBucket);
    }

    int n = words.size();
    for (int i = 0; i < n; i++) {
        string key = sortLetters(words[i]);
        int bucket = hashOfText(key);
        int groupNumber = -1;
        int bucketSize = buckets[bucket].size();
        for (int j = 0; j < bucketSize; j++) {
            int candidate = buckets[bucket][j];
            if (keys[candidate] == key) {
                groupNumber = candidate;
                break;
            }
        }
        if (groupNumber == -1) {
            vector<string> newGroup;
            keys.push_back(key);
            groups.push_back(newGroup);
            groupNumber = groups.size() - 1;
            buckets[bucket].push_back(groupNumber);
        }
        groups[groupNumber].push_back(words[i]);
    }
    return groups;
}

// Problem 5: Meeting Rooms
bool canAttendAllMeetings(vector<Interval> meetings) {
    int n = meetings.size();
    if (n <= 1) {
        return true;
    }
    meetings = mergeSortIntervals(meetings);
    for (int i = 1; i < n; i++) {
        // a meeting starting exactly when the last one ended is allowed,
        // so this test uses < instead of <=
        if (meetings[i].start < meetings[i - 1].end) {
            return false;
        }
    }
    return true;
}

// Problem 6: K Closest Points to Origin
struct Point {
    int x;
    int y;
};

long long distanceSquared(Point p) {
    long long x = p.x;
    long long y = p.y;
    return x * x + y * y;
}

vector<Point> mergePointHalves(vector<Point> left, vector<Point> right) {
    vector<Point> result;
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        if (distanceSquared(left[i]) <= distanceSquared(right[j])) {
            result.push_back(left[i]); i++;
        } else {
            result.push_back(right[j]); j++;
        }
    }
    while (i < leftSize) {
        result.push_back(left[i]); i++;
    }
    while (j < rightSize) {
        result.push_back(right[j]); j++;
    }
    return result;
}

vector<Point> mergeSortPoints(vector<Point> points) {
    int n = points.size();
    if (n <= 1) {
        return points;
    }
    int middle = n / 2;
    vector<Point> left;
    vector<Point> right;
    for (int i = 0; i < middle; i++) {
        left.push_back(points[i]);
    }
    for (int i = middle; i < n; i++) {
        right.push_back(points[i]);
    }
    left = mergeSortPoints(left);
    right = mergeSortPoints(right);
    return mergePointHalves(left, right);
}

vector<Point> kClosestBySorting(vector<Point> points, int k) {
    vector<Point> result;
    int n = points.size();
    if (k <= 0) {
        return result;
    }
    if (k > n) {
        k = n;
    }
    points = mergeSortPoints(points);
    for (int i = 0; i < k; i++) {
        result.push_back(points[i]);
    }
    return result;
}

// The heap helpers take the heap with & so they change the real heap
// instead of making a full copy every time, which would be slow.
void insertIntoPointHeap(vector<Point>& heap, Point p) {
    // add at the bottom, then move up while it is farther than its parent
    heap.push_back(p);
    int child = heap.size() - 1;
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (distanceSquared(heap[child]) <= distanceSquared(heap[parent])) {
            break;
        }
        Point temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;
        child = parent;
    }
}

void siftDownPointHeap(vector<Point>& heap) {
    // move the top down while one of its children is farther away
    int parent = 0;
    int heapSize = heap.size();
    while (true) {
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        int largest = parent;
        if (left < heapSize && distanceSquared(heap[left]) > distanceSquared(heap[largest])) {
            largest = left;
        }
        if (right < heapSize && distanceSquared(heap[right]) > distanceSquared(heap[largest])) {
            largest = right;
        }
        if (largest == parent) {
            break;
        }
        Point temp = heap[parent];
        heap[parent] = heap[largest];
        heap[largest] = temp;
        parent = largest;
    }
}

vector<Point> kClosestByHeap(vector<Point> points, int k) {
    // max heap, so the farthest of the k closest so far is always on top
    vector<Point> heap;
    if (k <= 0) {
        return heap;
    }
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int heapSize = heap.size();
        if (heapSize < k) {
            insertIntoPointHeap(heap, points[i]);
        } else if (distanceSquared(points[i]) < distanceSquared(heap[0])) {
            // the new point is closer than the farthest one kept, so it replaces it
            heap[0] = points[i];
            siftDownPointHeap(heap);
        }
    }
    return heap;
}

// Problem 7: Top K Frequent Elements
struct ValueCount {
    int value;
    int count;
};

vector<ValueCount> countFrequencies(vector<int> nums) {
    vector<ValueCount> counts;
    vector<vector<int>> buckets;

    for (int i = 0; i < 101; i++) {
        vector<int> emptyBucket;
        buckets.push_back(emptyBucket);
    }

    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int bucket = nums[i] % 101;
        if (bucket < 0) {
            bucket = bucket + 101;
        }
        int found = -1;
        int bucketSize = buckets[bucket].size();
        for (int j = 0; j < bucketSize; j++) {
            int candidate = buckets[bucket][j];
            if (counts[candidate].value == nums[i]) {
                found = candidate;
                break;
            }
        }
        if (found == -1) {
            ValueCount fresh;
            fresh.value = nums[i];
            fresh.count = 1;
            counts.push_back(fresh);
            buckets[bucket].push_back(counts.size() - 1);
        } else {
            counts[found].count = counts[found].count + 1;
        }
    }
    return counts;
}

bool countGoesFirst(ValueCount a, ValueCount b) {
    // higher count comes first, and if the counts tie the smaller value comes first
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.value <= b.value;
}

vector<ValueCount> mergeCountHalves(vector<ValueCount> left, vector<ValueCount> right) {
    vector<ValueCount> result;
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        if (countGoesFirst(left[i], right[j])) {
            result.push_back(left[i]); i++;
        } else {
            result.push_back(right[j]); j++;
        }
    }
    while (i < leftSize) {
        result.push_back(left[i]); i++;
    }
    while (j < rightSize) {
        result.push_back(right[j]); j++;
    }
    return result;
}

vector<ValueCount> mergeSortCounts(vector<ValueCount> counts) {
    int n = counts.size();
    if (n <= 1) {
        return counts;
    }
    int middle = n / 2;
    vector<ValueCount> left;
    vector<ValueCount> right;
    for (int i = 0; i < middle; i++) {
        left.push_back(counts[i]);
    }
    for (int i = middle; i < n; i++) {
        right.push_back(counts[i]);
    }
    left = mergeSortCounts(left);
    right = mergeSortCounts(right);
    return mergeCountHalves(left, right);
}

bool isValidTopK(vector<int> nums, int k) {
    // k cannot ask for more values than there are distinct values
    vector<ValueCount> counts = countFrequencies(nums);
    int distinct = counts.size();
    if (k > distinct) {
        return false;
    }
    return true;
}

vector<int> topKFrequent(vector<int> nums, int k) {
    vector<int> result;
    if (k <= 0) {
        return result;
    }
    vector<ValueCount> counts = countFrequencies(nums);
    int distinct = counts.size();
    if (k > distinct) {
        return result;
    }
    counts = mergeSortCounts(counts);
    for (int i = 0; i < k; i++) {
        result.push_back(counts[i].value);
    }
    return result;
}

// Problem 8: Merge K Sorted Arrays
struct HeapItem {
    int value;
    int arrayIndex;
    int position;
};

void insertIntoItemHeap(vector<HeapItem>& heap, HeapItem item) {
    // add at the bottom, then move up while it is smaller than its parent
    heap.push_back(item);
    int child = heap.size() - 1;
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (heap[child].value >= heap[parent].value) {
            break;
        }
        HeapItem temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;
        child = parent;
    }
}

void siftDownItemHeap(vector<HeapItem>& heap) {
    // move the top down while one of its children is smaller
    int parent = 0;
    int heapSize = heap.size();
    while (true) {
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        int smallest = parent;
        if (left < heapSize && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < heapSize && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == parent) {
            break;
        }
        HeapItem temp = heap[parent];
        heap[parent] = heap[smallest];
        heap[smallest] = temp;
        parent = smallest;
    }
}

vector<int> mergeKSortedArrays(vector<vector<int>> arrays) {
    vector<int> result;
    vector<HeapItem> heap;
    int k = arrays.size();
    // start the heap with the first value of every array that is not empty
    for (int a = 0; a < k; a++) {
        int arraySize = arrays[a].size();
        if (arraySize > 0) {
            HeapItem item;
            item.value = arrays[a][0];
            item.arrayIndex = a;
            item.position = 0;
            insertIntoItemHeap(heap, item);
        }
    }
    while (heap.size() > 0) {
        HeapItem smallest = heap[0];
        result.push_back(smallest.value);
        int nextPosition = smallest.position + 1;
        int sourceSize = arrays[smallest.arrayIndex].size();
        if (nextPosition < sourceSize) {
            // the next value from the same array takes the top spot
            HeapItem item;
            item.value = arrays[smallest.arrayIndex][nextPosition];
            item.arrayIndex = smallest.arrayIndex;
            item.position = nextPosition;
            heap[0] = item;
        } else {
            // that array is used up, so the last item moves to the top
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
        }
        siftDownItemHeap(heap);
    }
    return result;
}

// Problem 9: Kth Largest Element
bool isValidK(vector<int> nums, int k) {
    int n = nums.size();
    if (k <= 0) {
        return false;
    }
    if (k > n) {
        return false;
    }
    return true;
}

void insertIntoIntHeap(vector<int>& heap, int value) {
    // add at the bottom, then move up while it is smaller than its parent
    heap.push_back(value);
    int child = heap.size() - 1;
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (heap[child] >= heap[parent]) {
            break;
        }
        int temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;
        child = parent;
    }
}

void siftDownIntHeap(vector<int>& heap) {
    // move the top down while one of its children is smaller
    int parent = 0;
    int heapSize = heap.size();
    while (true) {
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        int smallest = parent;
        if (left < heapSize && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heapSize && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == parent) {
            break;
        }
        int temp = heap[parent];
        heap[parent] = heap[smallest];
        heap[smallest] = temp;
        parent = smallest;
    }
}

int kthLargest(vector<int> nums, int k) {
    // the heap is a min heap holding the k largest values seen so far,
    // so after every value is read the top of the heap is the answer
    vector<int> heap;
    if (isValidK(nums, k) == false) {
        return 0;
    }
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int heapSize = heap.size();
        if (heapSize < k) {
            insertIntoIntHeap(heap, nums[i]);
        } else if (nums[i] > heap[0]) {
            // the smallest value in the heap cannot be one of the k largest
            heap[0] = nums[i];
            siftDownIntHeap(heap);
        }
    }
    return heap[0];
}

// Problem 10: Count Inversions
// countAndSort returns two things at once, so they are bundled together
struct SortOutcome {
    vector<int> values;
    long long inversions;
};

SortOutcome mergeAndCount(SortOutcome left, SortOutcome right) {
    SortOutcome outcome;
    outcome.inversions = left.inversions + right.inversions;
    int leftSize = left.values.size();
    int rightSize = right.values.size();
    int i = 0;
    int j = 0;
    while (i < leftSize && j < rightSize) {
        if (left.values[i] <= right.values[j]) {
            // <= is used so equal values are never counted as inversions
            outcome.values.push_back(left.values[i]);
            i++;
        } else {
            outcome.values.push_back(right.values[j]);
            outcome.inversions = outcome.inversions + (leftSize - i); j++;
        }
    }
    while (i < leftSize) {
        outcome.values.push_back(left.values[i]); i++;
    }
    while (j < rightSize) {
        outcome.values.push_back(right.values[j]); j++;
    }
    return outcome;
}

SortOutcome countAndSort(vector<int> nums) {
    SortOutcome outcome;
    int n = nums.size();
    if (n <= 1) {
        outcome.values = nums;
        outcome.inversions = 0;
        return outcome;
    }
    int middle = n / 2;
    vector<int> left;
    vector<int> right;
    for (int i = 0; i < middle; i++) {
        left.push_back(nums[i]);
    }
    for (int i = middle; i < n; i++) {
        right.push_back(nums[i]);
    }
    return mergeAndCount(countAndSort(left), countAndSort(right));
}

long long countInversions(vector<int> nums) {
    SortOutcome outcome = countAndSort(nums);
    return outcome.inversions;
}

long long countInversionsBruteForce(vector<int> nums) {
    // slow O(n^2) version, used only to double check the fast version
    long long total = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] > nums[j]) {
                total++;
            }
        }
    }
    return total;
}

// Printing helpers
void printInts(vector<int> nums) {
    int n = nums.size();
    if (n == 0) {
        cout << "(empty)";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << nums[i];
        if (i < n - 1) {
            cout << " ";
        }
    }
}

void printIntervals(vector<Interval> items) {
    int n = items.size();
    if (n == 0) {
        cout << "(empty)";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "[" << items[i].start << "," << items[i].end << "]";
        if (i < n - 1) {
            cout << " ";
        }
    }
}

void printPoints(vector<Point> points) {
    int n = points.size();
    if (n == 0) {
        cout << "(empty)";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "(" << points[i].x << "," << points[i].y << ")";
        if (i < n - 1) {
            cout << " ";
        }
    }
}

void printStrings(vector<string> words) {
    int n = words.size();
    if (n == 0) {
        cout << "(empty)";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "\"" << words[i] << "\"";
        if (i < n - 1) {
            cout << " ";
        }
    }
}

void printGroups(vector<vector<string>> groups) {
    int n = groups.size();
    if (n == 0) {
        cout << "(empty)";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "{";
        printStrings(groups[i]);
        cout << "}";
        if (i < n - 1) {
            cout << " ";
        }
    }
}

// Test runners
// Each problem has one helper that runs a single test, so the test data below is just a list of inputs.
void runIntervalMergeTest(int number, vector<Interval> intervals) {
    cout << "Test " << number << " input:  ";
    printIntervals(intervals);
    cout << endl << "Test " << number << " output: ";
    printIntervals(mergeOverlappingIntervals(intervals));
    cout << endl << endl;
}

void runProblem1() {
    cout << "Problem 1: Merge Overlapping Intervals" << endl;
    runIntervalMergeTest(1, {{1, 3}, {2, 6}, {8, 10}, {15, 18}});
    runIntervalMergeTest(2, {{1, 4}, {4, 5}});          // touching endpoints
    runIntervalMergeTest(3, {});                        // empty input
}

void runColorTest(int number, vector<int> nums) {
    cout << "Test " << number << " input:      ";
    printInts(nums);
    cout << endl << "Test " << number << " counting:   ";
    printInts(sortColorsCounting(nums));
    cout << endl << "Test " << number << " dutch flag: ";
    printInts(sortColorsDutchFlag(nums));
    cout << endl << endl;
}

void runProblem2() {
    cout << "Problem 2: Sort Array of 0s, 1s, and 2s" << endl;
    runColorTest(1, {2, 0, 2, 1, 1, 0});
    runColorTest(2, {0, 0, 1, 1, 2, 2});         // already sorted
    runColorTest(3, {});                         // empty array
    runColorTest(4, {1, 1, 1, 1});               // all one value
}

void runLargestNumberTest(int number, vector<int> nums) {
    cout << "Test " << number << " input:  ";
    printInts(nums);
    cout << endl << "Test " << number << " output: " << largestNumber(nums) << endl << endl;
}

void runProblem3() {
    cout << "Problem 3: Largest Number from Concatenation" << endl;
    runLargestNumberTest(1, {3, 30, 34, 5, 9});
    runLargestNumberTest(2, {0, 0});          // all zeros
    runLargestNumberTest(3, {5});             // single value
}

void runAnagramTest(int number, vector<string> words) {
    cout << "Test " << number << " input:  ";
    printStrings(words);
    cout << endl << "Test " << number << " output: ";
    printGroups(groupAnagrams(words));
    cout << endl << endl;
}

void runProblem4() {
    cout << "Problem 4: Group Anagrams" << endl;
    runAnagramTest(1, {"eat", "tea", "tan", "ate", "nat", "bat"});
    runAnagramTest(2, {"", ""});                        // empty strings
    runAnagramTest(3, {"abc", "def", "ghi"});           // no anagrams
}

void runMeetingTest(int number, vector<Interval> meetings) {
    cout << "Test " << number << " input:  ";
    printIntervals(meetings);
    cout << endl << "Test " << number << " output: ";
    if (canAttendAllMeetings(meetings)) {
        cout << "true" << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }
}

void runProblem5() {
    cout << "Problem 5: Meeting Rooms" << endl;
    runMeetingTest(1, {{0, 30}, {5, 10}, {15, 20}});
    runMeetingTest(2, {{1, 4}, {4, 5}});                // touching endpoints
    runMeetingTest(3, {});                              // empty input
}

void runKClosestTest(int number, vector<Point> points, int k) {
    cout << "Test " << number << " input:   ";
    printPoints(points);
    cout << "  k = " << k << endl;
    int n = points.size();
    if (k > n) {
        cout << "Test " << number << " output:  invalid, k is larger than the number of points" << endl << endl;
        return;
    }
    cout << "Test " << number << " sorting: ";
    printPoints(kClosestBySorting(points, k));
    cout << endl << "Test " << number << " heap:    ";
    printPoints(kClosestByHeap(points, k));
    cout << endl << endl;
}

void runProblem6() {
    cout << "Problem 6: K Closest Points to Origin" << endl;
    runKClosestTest(1, {{1, 3}, {-2, 2}, {5, 8}, {0, 1}}, 2);
    runKClosestTest(2, {{1, 1}, {2, 2}}, 2);            // k equals n
    runKClosestTest(3, {{1, 1}, {2, 2}}, 0);            // k is zero
}

void runTopKTest(int number, vector<int> nums, int k) {
    cout << "Test " << number << " input:  ";
    printInts(nums);
    cout << "  k = " << k << endl << "Test " << number << " output: ";
    if (isValidTopK(nums, k) == false) {
        cout << "invalid k" << endl << endl;
    } else {
        printInts(topKFrequent(nums, k));
        cout << endl << endl;
    }
}

void runProblem7() {
    cout << "Problem 7: Top K Frequent Elements" << endl;
    runTopKTest(1, {1, 1, 1, 2, 2, 3}, 2);
    runTopKTest(2, {3, 1, 2}, 2);                 // every value tied
    runTopKTest(3, {5, 5, 6}, 2);                 // k equals distinct count
}

void runMergeArraysTest(int number, vector<vector<int>> arrays) {
    cout << "Test " << number << " input:" << endl;
    int k = arrays.size();
    if (k == 0) {
        cout << "  no arrays" << endl;
    }
    for (int i = 0; i < k; i++) {
        cout << "  array " << (i + 1) << ": ";
        printInts(arrays[i]);
        cout << endl;
    }
    cout << "Test " << number << " output: ";
    printInts(mergeKSortedArrays(arrays));
    cout << endl << endl;
}

void runProblem8() {
    cout << "Problem 8: Merge K Sorted Arrays" << endl;
    runMergeArraysTest(1, {{1, 4, 5}, {1, 3, 4}, {2, 6}});
    runMergeArraysTest(2, {{}, {2, 5}, {}});            // some arrays empty
    runMergeArraysTest(3, {});                          // no arrays at all
}

void runKthLargestTest(int number, vector<int> nums, int k) {
    cout << "Test " << number << " input:  ";
    printInts(nums);
    cout << "  k = " << k << endl << "Test " << number << " output: ";
    if (isValidK(nums, k) == false) {
        cout << "invalid k" << endl << endl;
    } else {
        cout << kthLargest(nums, k) << endl << endl;
    }
}

void runProblem9() {
    cout << "Problem 9: Kth Largest Element" << endl;
    runKthLargestTest(1, {3, 2, 1, 5, 6, 4}, 2);
    runKthLargestTest(2, {7, 10, 4, 3}, 1);             // k is 1, the maximum
    runKthLargestTest(3, {5, 5, 5, 2}, 4);              // k equals n, duplicates
}

void runInversionTest(int number, vector<int> nums) {
    cout << "Test " << number << " input:       ";
    printInts(nums);
    cout << endl << "Test " << number << " inversions:  " << countInversions(nums) << endl;
    cout << "Test " << number << " brute force: " << countInversionsBruteForce(nums) << endl << endl;
}

void runProblem10() {
    cout << "Problem 10: Count Inversions" << endl;
    runInversionTest(1, {2, 4, 1, 3, 5});
    runInversionTest(2, {1, 2, 3, 4, 5});               // already sorted
    runInversionTest(3, {5, 4, 3, 2, 1});               // reverse sorted
}

// Menu
void showMenu() {
    cout << endl;
    cout << "EECE 7205 Assignment 01" << endl;
    cout << "1.  Merge Overlapping Intervals" << endl;
    cout << "2.  Sort Array of 0s, 1s, and 2s" << endl;
    cout << "3.  Largest Number from Concatenation" << endl;
    cout << "4.  Group Anagrams" << endl;
    cout << "5.  Meeting Rooms" << endl;
    cout << "6.  K Closest Points to Origin" << endl;
    cout << "7.  Top K Frequent Elements" << endl;
    cout << "8.  Merge K Sorted Arrays" << endl;
    cout << "9.  Kth Largest Element" << endl;
    cout << "10. Count Inversions" << endl;
    cout << "0.  Exit" << endl;
    cout << "Choose a problem: ";
}

int main() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;
        if (cin.fail()) {           // stop if the user types something that is not a number
            cout << endl << "That is not a valid choice." << endl;
            return 0;
        }

        cout << endl;
        switch (choice) {
            case 1: runProblem1(); break;
            case 2: runProblem2(); break;
            case 3: runProblem3(); break;
            case 4: runProblem4(); break;
            case 5: runProblem5(); break;
            case 6: runProblem6(); break;
            case 7: runProblem7(); break;
            case 8: runProblem8(); break;
            case 9: runProblem9(); break;
            case 10: runProblem10(); break;
            case 0: cout << "Goodbye." << endl; break;
            default: cout << "Please choose a number from 0 to 10." << endl; break;
        }
    }
    return 0;
}
