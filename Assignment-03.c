// Assignment-03 : Write C program to implement queue using linked list
#include <stdio.h>
#include <stdlib.h>

struct queue {
    int value;
    struct queue *next;
};

struct queue *first = NULL, *last = NULL;

void clearInput() {
    while (getchar() != '\n');
}

void enqueue(int value) {
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));

    temp->next = NULL;
    temp->value = value;

    if (last == NULL) {
        last = temp;
    }

    if (first == NULL) {
        first = temp;
    }
    else {
        last->next = temp;
        last = temp;
    }

    printf("%d inserted into queue\n", value);
}

void display() {
    struct queue *temp;

    if (first == NULL) {
        printf("Queue is empty\n");
        return;
    }

    temp = first;

    printf("Queue Data: ");

    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    printf("\n");
}

void update() {
    int old_value, new_value;
    int attempts;
    struct queue *temp;

    if (first == NULL) {
        printf("Queue is empty\n");
        return;
    }

    for (attempts = 1; attempts <= 3; attempts++) {
        printf("Enter value to update: ");

        if (scanf("%d", &old_value) == 1) {
            if (getchar() == '\n') {
                break;
            }
            else {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        else {
            printf("Invalid input! Attempt %d of 3\n", attempts);
            clearInput();
        }
    }

    if (attempts > 3) {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    for (attempts = 1; attempts <= 3; attempts++) {
        printf("Enter new value: ");

        if (scanf("%d", &new_value) == 1) {
            if (getchar() == '\n') {
                break;
            }
            else {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        else {
            printf("Invalid input! Attempt %d of 3\n", attempts);
            clearInput();
        }
    }

    if (attempts > 3) {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    temp = first;

    while (temp != NULL) {
        if (temp->value == old_value) {
            temp->value = new_value;
            printf("Value updated successfully\n");
            return;
        }

        temp = temp->next;
    }

    printf("Value not found in queue\n");
}

void dequeue() {
    struct queue *temp;

    if (first == NULL) {
        printf("Queue is empty\n");
        return;
    }

    temp = first;

    printf("%d deleted from queue\n", first->value);

    first = first->next;

    if (first == NULL) {
        last = NULL;
    }

    free(temp);
}

int main() {
    int choice, value;
    int attempts;

    while (1) {

        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Update\n");
        printf("5. Exit\n");

        for (attempts = 1; attempts <= 3; attempts++) {

            printf("Enter your choice: ");

            if (scanf("%d", &choice) == 1) {

                if (getchar() == '\n') {
                    break;
                }
                else {
                    clearInput();
                    printf("Invalid choice! Attempt %d of 3\n", attempts);
                }

            }
            else {
                printf("Invalid choice! Attempt %d of 3\n", attempts);
                clearInput();
            }
        }

        if (attempts > 3) {
            printf("3 attempts completed. Program ended.\n");
            break;
        }

        switch (choice) {

            case 1:

                for (attempts = 1; attempts <= 3; attempts++) {

                    printf("Enter value: ");

                    if (scanf("%d", &value) == 1) {

                        if (getchar() == '\n') {
                            break;
                        }
                        else {
                            clearInput();
                            printf("Invalid value! Attempt %d of 3\n", attempts);
                        }

                    }
                    else {
                        printf("Invalid value! Attempt %d of 3\n", attempts);
                        clearInput();
                    }
                }

                if (attempts <= 3) {
                    enqueue(value);
                }
                else {
                    printf("3 attempts completed. Enqueue cancelled.\n");
                }

                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                update();
                break;

            case 5:
                printf("Program ended.\n");
                return 0;

            default:
                printf("Invalid choice! Please enter 1 to 5.\n");
        }
    }

    return 0;
}