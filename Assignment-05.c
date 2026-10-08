// Assignment-05 = Write C program to implement stack using linked list

#include <stdio.h>
#include <stdlib.h>

struct stack {
    int value;
    struct stack *next;
};

struct stack *top = NULL;

void clearInput() {
    while (getchar() != '\n');
}

void push(int value) {
    struct stack *temp;

    temp = (struct stack *)malloc(sizeof(struct stack));

    temp->value = value;
    temp->next = top;
    top = temp;

    printf("%d pushed into stack\n", value);
}

void pop() {
    struct stack *temp;

    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    temp = top;
    printf("%d popped from stack\n", top->value);

    top = top->next;
    free(temp);
}

void display() {
    struct stack *temp;

    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    temp = top;

    printf("Stack Data: ");

    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    printf("\n");
}

void update() {
    int old_value, new_value;
    int attempts;
    struct stack *temp;

    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    for (attempts = 1; attempts <= 3; attempts++) {
        printf("Enter value to update: ");

        if (scanf("%d", &old_value) == 1) {
            if (getchar() != '\n') {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
                continue;
            }

            temp = top;

            while (temp != NULL) {
                if (temp->value == old_value) {
                    break;
                }
                temp = temp->next;
            }

            if (temp != NULL) {
                break;
            }

            printf("Value not found in stack! Attempt %d of 3\n", attempts);
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

    temp->value = new_value;

    printf("Value updated successfully\n");
}

int main() {
    int choice, value;
    int attempts;

    while (1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Update\n");
        printf("5. Exit\n");

        for (attempts = 1; attempts <= 3; attempts++) {
            printf("Enter your choice: ");

            if (scanf("%d", &choice) == 1) {
                if (getchar() == '\n') {
                    break;
                } else {
                    clearInput();
                    printf("Invalid choice! Attempt %d of 3\n", attempts);
                }
            } else {
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
                        } else {
                            clearInput();
                            printf("Invalid value! Attempt %d of 3\n", attempts);
                        }
                    } else {
                        printf("Invalid value! Attempt %d of 3\n", attempts);
                        clearInput();
                    }
                }

                if (attempts <= 3) {
                    push(value);
                } else {
                    printf("3 attempts completed. Push cancelled.\n");
                }
                break;

            case 2:
                pop();
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