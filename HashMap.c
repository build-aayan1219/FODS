#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int key;
    int value;
    struct Node *next;
};

struct Node *hashTable[SIZE];

int hashFunction(int key) {
    return key % SIZE;
}

void insert(int key, int value) {
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            temp->value = value;
            printf("Key updated successfully.\n");
            return;
        }
        temp = temp->next;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Inserted successfully.\n");
}

void search(int key) {
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key: %d, Value: %d\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }

    printf("Key not found.\n");
}

void deleteKey(int key) {
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];
    struct Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Deleted successfully.\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Key not found.\n");
}

void display() {
    int i;
    struct Node *temp;

    printf("\nHash Table:\n");

    for (i = 0; i < SIZE; i++) {
        printf("[%d]", i);
        temp = hashTable[i];

        while (temp != NULL) {
            printf(" -> (%d, %d)", temp->key, temp->value);
            temp = temp->next;
        }

        printf(" -> NULL\n");
    }
}

int main() {
    int choice, key, value;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key and value: ");
                scanf("%d %d", &key, &value);
                insert(key, value);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;

            case 4:
                display();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}