#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int key;
    int value;
    struct Node *next;
};

struct Node *hashTable[SIZE] = {NULL};

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInteger(int *value) {
    int c;

    if (scanf("%d", value) != 1) {
        clearInput();
        return 0;
    }

    c = getchar();

    if (c == '\n' || c == EOF)
        return 1;

    while (c != '\n' && c != EOF)
        c = getchar();

    return 0;
}

int inputInteger(char *prompt, int *value) {
    int attempts, valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
        printf("%s", prompt);
        if (readInteger(value) == 1)
            valid = 1;
        else
            printf("Invalid input! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
        printf("3 attempts completed. Operation cancelled.\n");
    return valid;
}

int hashFunction(int key) {
    return ((key % SIZE) + SIZE) % SIZE;
}

struct Node *findNode(int key) {
    struct Node *temp = hashTable[hashFunction(key)];
    while (temp != NULL) {
        if (temp->key == key)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void insert(int key, int value) {
    int index = hashFunction(key);
    struct Node *newNode;

    if (findNode(key) != NULL) {
        printf("Key already exists. Duplicate keys are not allowed.\n");
        return;
    }

    newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("Inserted successfully.\n");
}

void search(int key) {
    int index = hashFunction(key);
    struct Node *temp = findNode(key);

    if (temp != NULL)
        printf("Key: %d, Value: %d, Index: %d\n", temp->key, temp->value, index);
    else
        printf("Key not found.\n");
}

void deleteKey(int key) {
    int index = hashFunction(key);
    struct Node *temp = hashTable[index], *prev = NULL;

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

void update(int oldKey, int newKey, int newValue) {
    int oldIndex, newIndex;
    struct Node *temp, *prev = NULL;

    oldIndex = hashFunction(oldKey);
    temp = hashTable[oldIndex];

    while (temp != NULL && temp->key != oldKey) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found. Update failed.\n");
        return;
    }

    if (oldKey != newKey && findNode(newKey) != NULL) {
        printf("New key already exists. Update failed.\n");
        return;
    }

    if (oldKey == newKey) {
        temp->value = newValue;
        printf("Value updated successfully.\n");
        return;
    }

    if (prev == NULL)
        hashTable[oldIndex] = temp->next;
    else
        prev->next = temp->next;

    newIndex = hashFunction(newKey);
    temp->key = newKey;
    temp->value = newValue;
    temp->next = hashTable[newIndex];
    hashTable[newIndex] = temp;

    printf("Key and value updated successfully.\n");
}

void display() {
    int i, empty = 1;
    struct Node *temp;

    for (i = 0; i < SIZE; i++) {
        if (hashTable[i] != NULL)
            empty = 0;
    }

    printf("\nHash Table:\n");

    for (i = 0; i < SIZE; i++) {
        printf("[%d] ", i);
        temp = hashTable[i];

        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    if (empty)
        printf("Hash table is empty.\n");
}

int main() {
    int choice, key, value, newKey, newValue;
    int attempts, valid, exitProgram = 0;

    while (exitProgram == 0) {
        printf("\n1. Insert\n2. Search\n3. Update\n4. Delete\n5. Display\n6. Exit\n");

        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter your choice: ");
            if (readInteger(&choice) == 1 && choice >= 1 && choice <= 6)
                valid = 1;
            else
                printf("Invalid input! Attempt %d of 3\n", attempts);
        }

        if (valid == 0) {
            printf("3 attempts completed. Program ended.\n");
            exitProgram = 1;
        }
        else if (choice == 1) {
            if (inputInteger("Enter key: ", &key) == 1 &&
                inputInteger("Enter value: ", &value) == 1)
                insert(key, value);
        }
        else if (choice == 2) {
            if (inputInteger("Enter key to search: ", &key) == 1)
                search(key);
        }
        else if (choice == 3) {
            if (inputInteger("Enter old key: ", &key) == 1 &&
                inputInteger("Enter new key: ", &newKey) == 1 &&
                inputInteger("Enter new value: ", &newValue) == 1)
                update(key, newKey, newValue);
        }
        else if (choice == 4) {
            if (inputInteger("Enter key to delete: ", &key) == 1)
                deleteKey(key);
        }
        else if (choice == 5)
            display();
        else if (choice == 6) {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }

    return 0;
}