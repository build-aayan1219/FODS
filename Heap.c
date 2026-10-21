
#include <stdio.h>

#define SIZE 100

int maxHeap[SIZE], minHeap[SIZE];
int maxN = 0, minN = 0;

void insertMax(int value) {
    int i = maxN, temp;
  
    if (maxN == SIZE) {
        printf("Max Heap is full.\n");
        return;
    }

    maxHeap[maxN++] = value;

    while (i > 0 && maxHeap[(i - 1) / 2] < maxHeap[i]) {
        temp = maxHeap[i];
        maxHeap[i] = maxHeap[(i - 1) / 2];
        maxHeap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }

    printf("Inserted into Max Heap.\n");
}

void insertMin(int value) {
    int i = minN, temp;

    if (minN == SIZE) {
        printf("Min Heap is full.\n");
        return;
    }

    minHeap[minN++] = value;

    while (i > 0 && minHeap[(i - 1) / 2] > minHeap[i]) {
        temp = minHeap[i];
        minHeap[i] = minHeap[(i - 1) / 2];
        minHeap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }

    printf("Inserted into Min Heap.\n");
}

void deleteMax() {
    int i = 0, left, right, largest, temp;

    if (maxN == 0) {
        printf("Max Heap is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", maxHeap[0]);
    maxHeap[0] = maxHeap[--maxN];

    while (i < maxN) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        largest = i;

        if (left < maxN && maxHeap[left] > maxHeap[largest])
            largest = left;

        if (right < maxN && maxHeap[right] > maxHeap[largest])
            largest = right;

        if (largest == i)
            break;

        temp = maxHeap[i];
        maxHeap[i] = maxHeap[largest];
        maxHeap[largest] = temp;
        i = largest;
    }
}

void deleteMin() {
    int i = 0, left, right, smallest, temp;

    if (minN == 0) {
        printf("Min Heap is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", minHeap[0]);
    minHeap[0] = minHeap[--minN];

    while (i < minN) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;

        if (left < minN && minHeap[left] < minHeap[smallest])
            smallest = left;

        if (right < minN && minHeap[right] < minHeap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        temp = minHeap[i];
        minHeap[i] = minHeap[smallest];
        minHeap[smallest] = temp;
        i = smallest;
    }
}

void displayMax() {
    int i;

    if (maxN == 0) {
        printf("Max Heap is empty.\n");
        return;
    }

    printf("Max Heap: ");
    for (i = 0; i < maxN; i++)
        printf("%d ", maxHeap[i]);

    printf("\n");
}

void displayMin() {
    int i;

    if (minN == 0) {
        printf("Min Heap is empty.\n");
        return;
    }

    printf("Min Heap: ");
    for (i = 0; i < minN; i++)
        printf("%d ", minHeap[i]);

    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Insert into Max Heap");
        printf("\n2. Delete from Max Heap");
        printf("\n3. Display Max Heap");
        printf("\n4. Insert into Min Heap");
        printf("\n5. Delete from Min Heap");
        printf("\n6. Display Min Heap");
        printf("\n7. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertMax(value);
                break;

            case 2:
                deleteMax();
                break;

            case 3:
                displayMax();
                break;

            case 4:
                printf("Enter value: ");
                scanf("%d", &value);
                insertMin(value);
                break;

            case 5:
                deleteMin();
                break;

            case 6:
                displayMin();
                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
