#include <stdio.h>
#define SIZE 100

int maxHeap[SIZE], minHeap[SIZE];
int maxN = 0, minN = 0;

void insertMax()
{
    int n, value, i, j, parent, temp;

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    if (n <= 0 || maxN + n > SIZE)
    {
        printf("Invalid number of elements.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);

        maxHeap[maxN] = value;
        maxN++;

        j = maxN - 1;

        while (j > 0)
        {
            parent = (j - 1) / 2;

            if (maxHeap[j] > maxHeap[parent])
            {
                temp = maxHeap[j];
                maxHeap[j] = maxHeap[parent];
                maxHeap[parent] = temp;
                j = parent;
            }
            else
                break;
        }
    }

    printf("Elements inserted into Max Heap successfully.\n");
}

void insertMin()
{
    int n, value, i, j, parent, temp;

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    if (n <= 0 || minN + n > SIZE)
    {
        printf("Invalid number of elements.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);

        minHeap[minN] = value;
        minN++;

        j = minN - 1;

        while (j > 0)
        {
            parent = (j - 1) / 2;

            if (minHeap[j] < minHeap[parent])
            {
                temp = minHeap[j];
                minHeap[j] = minHeap[parent];
                minHeap[parent] = temp;
                j = parent;
            }
            else
                break;
        }
    }

    printf("Elements inserted into Min Heap successfully.\n");
}

void deleteMax()
{
    int value, i, left, right, largest, temp, parent;

    if (maxN == 0)
    {
        printf("Max Heap is empty.\n");
        return;
    }

    printf("Enter element to delete: ");
    scanf("%d", &value);

    for (i = 0; i < maxN && maxHeap[i] != value; i++);

    if (i == maxN)
    {
        printf("Element not found.\n");
        return;
    }

    maxHeap[i] = maxHeap[--maxN];

    if (i > 0 && maxHeap[i] > maxHeap[(i - 1) / 2])
    {
        while (i > 0)
        {
            parent = (i - 1) / 2;

            if (maxHeap[i] > maxHeap[parent])
            {
                temp = maxHeap[i];
                maxHeap[i] = maxHeap[parent];
                maxHeap[parent] = temp;
                i = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * i + 1;
            right = 2 * i + 2;
            largest = i;

            if (left < maxN && maxHeap[left] > maxHeap[largest])
                largest = left;

            if (right < maxN && maxHeap[right] > maxHeap[largest])
                largest = right;

            if (largest != i)
            {
                temp = maxHeap[i];
                maxHeap[i] = maxHeap[largest];
                maxHeap[largest] = temp;
                i = largest;
            }
            else
                break;
        }
    }

    printf("Element %d deleted successfully.\n", value);
}

void deleteMin()
{
    int value, i, left, right, smallest, temp, parent;

    if (minN == 0)
    {
        printf("Min Heap is empty.\n");
        return;
    }

    printf("Enter element to delete: ");
    scanf("%d", &value);

    for (i = 0; i < minN && minHeap[i] != value; i++);

    if (i == minN)
    {
        printf("Element not found.\n");
        return;
    }

    minHeap[i] = minHeap[--minN];

    if (i > 0 && minHeap[i] < minHeap[(i - 1) / 2])
    {
        while (i > 0)
        {
            parent = (i - 1) / 2;

            if (minHeap[i] < minHeap[parent])
            {
                temp = minHeap[i];
                minHeap[i] = minHeap[parent];
                minHeap[parent] = temp;
                i = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * i + 1;
            right = 2 * i + 2;
            smallest = i;

            if (left < minN && minHeap[left] < minHeap[smallest])
                smallest = left;

            if (right < minN && minHeap[right] < minHeap[smallest])
                smallest = right;

            if (smallest != i)
            {
                temp = minHeap[i];
                minHeap[i] = minHeap[smallest];
                minHeap[smallest] = temp;
                i = smallest;
            }
            else
                break;
        }
    }

    printf("Element %d deleted successfully.\n", value);
}

void updateMax()
{
    int oldValue, newValue, i, left, right, largest, temp, parent;

    if (maxN == 0)
    {
        printf("Max Heap is empty.\n");
        return;
    }

    printf("Enter element to update: ");
    scanf("%d", &oldValue);

    for (i = 0; i < maxN && maxHeap[i] != oldValue; i++);

    if (i == maxN)
    {
        printf("Element not found.\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &newValue);

    maxHeap[i] = newValue;

    if (i > 0 && maxHeap[i] > maxHeap[(i - 1) / 2])
    {
        while (i > 0)
        {
            parent = (i - 1) / 2;

            if (maxHeap[i] > maxHeap[parent])
            {
                temp = maxHeap[i];
                maxHeap[i] = maxHeap[parent];
                maxHeap[parent] = temp;
                i = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * i + 1;
            right = 2 * i + 2;
            largest = i;

            if (left < maxN && maxHeap[left] > maxHeap[largest])
                largest = left;

            if (right < maxN && maxHeap[right] > maxHeap[largest])
                largest = right;

            if (largest != i)
            {
                temp = maxHeap[i];
                maxHeap[i] = maxHeap[largest];
                maxHeap[largest] = temp;
                i = largest;
            }
            else
                break;
        }
    }

    printf("Max Heap updated successfully.\n");
}

void updateMin()
{
    int oldValue, newValue, i, left, right, smallest, temp, parent;

    if (minN == 0)
    {
        printf("Min Heap is empty.\n");
        return;
    }

    printf("Enter element to update: ");
    scanf("%d", &oldValue);

    for (i = 0; i < minN && minHeap[i] != oldValue; i++);

    if (i == minN)
    {
        printf("Element not found.\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &newValue);

    minHeap[i] = newValue;

    if (i > 0 && minHeap[i] < minHeap[(i - 1) / 2])
    {
        while (i > 0)
        {
            parent = (i - 1) / 2;

            if (minHeap[i] < minHeap[parent])
            {
                temp = minHeap[i];
                minHeap[i] = minHeap[parent];
                minHeap[parent] = temp;
                i = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * i + 1;
            right = 2 * i + 2;
            smallest = i;

            if (left < minN && minHeap[left] < minHeap[smallest])
                smallest = left;

            if (right < minN && minHeap[right] < minHeap[smallest])
                smallest = right;

            if (smallest != i)
            {
                temp = minHeap[i];
                minHeap[i] = minHeap[smallest];
                minHeap[smallest] = temp;
                i = smallest;
            }
            else
                break;
        }
    }

    printf("Min Heap updated successfully.\n");
}

void displayMax()
{
    int i;

    if (maxN == 0)
    {
        printf("Max Heap is empty.\n");
        return;
    }

    printf("Max Heap: ");
    for (i = 0; i < maxN; i++)
        printf("%d ", maxHeap[i]);

    printf("\n");
}

void displayMin()
{
    int i;

    if (minN == 0)
    {
        printf("Min Heap is empty.\n");
        return;
    }

    printf("Min Heap: ");
    for (i = 0; i < minN; i++)
        printf("%d ", minHeap[i]);

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n----- HEAP OPERATIONS -----\n");
        printf("1. Insert into Max Heap\n");
        printf("2. Delete from Max Heap\n");
        printf("3. Display Max Heap\n");
        printf("4. Insert into Min Heap\n");
        printf("5. Delete from Min Heap\n");
        printf("6. Display Min Heap\n");
        printf("7. Update Max Heap\n");
        printf("8. Update Min Heap\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertMax();
                break;

            case 2:
                deleteMax();
                break;

            case 3:
                displayMax();
                break;

            case 4:
                insertMin();
                break;

            case 5:
                deleteMin();
                break;

            case 6:
                displayMin();
                break;

            case 7:
                updateMax();
                break;

            case 8:
                updateMin();
                break;

            case 9:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
