// Assignment-02 : Write C program to implement queue using array
#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int get_integer(int *num) {
    char extra;

    if (scanf("%d%c", num, &extra) == 2 && extra == '\n')
        return 1;

    while (getchar() != '\n');

    return 0;
}

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue is full\n");
    }
    else {
        if (front == -1)
            front = 0;

        rear++;
        queue[rear] = value;

        printf("%d inserted into queue\n", value);
    }
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    }
    else {
        printf("%d deleted from queue\n", queue[front]);
        front++;
    }
}

void display() {
    int i;

    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    }
    else {
        printf("Queue Data: ");

        for (i = front; i <= rear; i++)
            printf("%d ", queue[i]);

        printf("\n");
    }
}

int main() {
    int choice, value;
    int attempts, valid;

    while (1) {
        valid = 0;

        for (attempts = 1; attempts <= 3; attempts++) {
            printf("\n1. Enqueue\n");
            printf("2. Dequeue\n");
            printf("3. Display\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");

            if (!get_integer(&choice)) {
                printf("Invalid choice!\n");
                continue;
            }

            if (choice < 1 || choice > 4) {
                printf("Invalid choice!\n");
                continue;
            }

            valid = 1;
            break;
        }

        if (!valid) {
            printf("3 wrong attempts. Returning to main menu.\n");
            continue;
        }

        switch (choice) {
            case 1:
                valid = 0;

                for (attempts = 1; attempts <= 3; attempts++) {
                    printf("Enter value: ");

                    if (!get_integer(&value)) {
                        printf("Invalid input! Please enter an integer.\n");
                        continue;
                    }
                    if (value < 0) {
                        printf("Invalid input! Negative values are not allowed.\n");
                        continue;
                    }

                    valid = 1;
                    break;
                }

                if (!valid) {
                    printf("3 wrong attempts. Returning to main menu.\n");
                    break;
                }

                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;
        }
    }

    return 0;
}
