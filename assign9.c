#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to adjust heap upward after insertion (index starting from 0)
void adjustUp(int heap[], int i) {
    int temp, parent;
    while (i > 0) {
        parent = (i - 1) / 2;
        if (heap[i] > heap[parent]) {
            temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

// Function to insert element into max heap
void insert(int heap[], int *n, int element) {
    if (*n >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    heap[*n] = element;
    adjustUp(heap, *n);
    (*n)++;
}

// Function to adjust heap downward after deletion (index starting from 0)
void adjust(int heap[], int n, int i) {
    int j, temp;
    while (2 * i + 1 < n) {
        j = 2 * i + 1;  // Index of left child
        
        // Compare left and right child and let j be the larger child
        if (j + 1 < n && heap[j + 1] > heap[j]) {
            j = j + 1;
        }
        
        // If parent >= children then break
        if (heap[i] >= heap[j]) {
            break;
        } else {
            // Swap parent with larger child
            temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
            i = j;
        }
    }
}

// Function to delete maximum element from heap
int deleteMax(int heap[], int *n) {
    if (*n == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    
    int maxElement = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    
    if (*n > 0) {
        adjust(heap, *n, 0);
    }
    
    return maxElement;
}

// Function to perform heap sort
void heapSort(int heap[], int n) {
    int i, temp;
    int originalSize = n;
    
    // Build max heap (already done through insertions)
    
    // Extract elements one by one
    for (i = n / 2 - 1; i >= 0; i--) {
        adjust(heap, n, i);
    }
    
    // Interchange the new maximum with the element at the end of array
    while (n > 0) {
        temp = heap[0];
        heap[0] = heap[n - 1];
        heap[n - 1] = temp;
        n--;
        adjust(heap, n, 0);
    }
}

// Function to display heap
void displayHeap(int heap[], int n) {
    int i;
    if (n == 0) {
        printf("Heap is empty!\n");
        return;
    }
    printf("Heap elements: ");
    for (i = 0; i < n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

// Function to display array
void displayArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int heap[MAX_SIZE];
    int n = 0;
    int numStudents, i, mark;
    int maxMark, minMark;
    
    // Get number of students
    printf("\nEnter the number of students: ");
    scanf("%d", &numStudents);
    
    if (numStudents <= 0 || numStudents > MAX_SIZE) {
        printf("Invalid number of students!\n");
        return 1;
    }
    
    // Input marks and build max heap
    printf("\nEnter marks for %d students:\n", numStudents);
    for (i = 0; i < numStudents; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d", &mark);
        insert(heap, &n, mark);
    }
    
    printf("\n--- Max Heap Created ---\n");
    displayHeap(heap, n);
    
    // Find maximum mark (root of max heap)
    maxMark = heap[0];
    printf("\nMaximum marks obtained: %d\n", maxMark);
    
    // Perform heap sort to get marks in descending order
    printf("\n--- Performing Heap Sort ---\n");
    int sortedHeap[MAX_SIZE];
    for (i = 0; i < n; i++) {
        sortedHeap[i] = heap[i];
    }
    int sortedSize = n;
    heapSort(sortedHeap, sortedSize);
    
    printf("Marks in descending order: ");
    for (i = sortedSize - 1; i >= 0; i--) {
        printf("%d ", sortedHeap[i]);
    }
    printf("\n");
    
    // Find minimum mark (last element after sorting)
    minMark = sortedHeap[0];
    printf("\nMinimum marks obtained: %d\n", minMark);
    
    printf("Total Students    : %d\n", numStudents);
    printf("Maximum Marks     : %d\n", maxMark);
    printf("Minimum Marks     : %d\n", minMark);
    
    return 0;
}
