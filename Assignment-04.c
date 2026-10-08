// Assignment-04: Write C program to implement stack using array

#include <stdio.h>

#define MAX 5

int stack[MAX];
int top = -1;

void clearInput()
{
    while (getchar() != '\n');
}

void push(int value)
{
    if (top == MAX - 1)
    {
        printf("Stack is full\n");
        return;
    }

    top++;
    stack[top] = value;

    printf("%d inserted into stack\n", value);
}

void pop()
{
    if (top == -1)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("%d deleted from stack\n", stack[top]);
    top--;
}

void display()
{
    int i;

    if (top == -1)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack Data: ");

    for (i = top; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }

    printf("\n");
}

void update()
{
    int old_value, new_value;
    int attempts;
    int i;

    if (top == -1)
    {
        printf("Stack is empty\n");
        return;
    }

    for (attempts = 1; attempts <= 3; attempts++)
    {
        printf("Enter value to update: ");

        if (scanf("%d", &old_value) == 1)
        {
            if (getchar() == '\n')
            {
                break;
            }
            else
            {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        else
        {
            printf("Invalid input! Attempt %d of 3\n", attempts);
            clearInput();
        }
    }

    if (attempts > 3)
    {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    if (old_value < 0)
    {
        printf("Negative values are not allowed.\n");
        return;
    }

    for (attempts = 1; attempts <= 3; attempts++)
    {
        printf("Enter new value: ");

        if (scanf("%d", &new_value) == 1)
        {
            if (getchar() == '\n')
            {
                break;
            }
            else
            {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        else
        {
            printf("Invalid input! Attempt %d of 3\n", attempts);
            clearInput();
        }
    }

    if (attempts > 3)
    {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    if (new_value < 0)
    {
        printf("Negative values are not allowed.\n");
        return;
    }

    for (i = top; i >= 0; i--)
    {
        if (stack[i] == old_value)
        {
            stack[i] = new_value;
            printf("Value updated successfully\n");
            return;
        }
    }

    printf("Value not found in stack\n");
}

int main()
{
    int choice, value;
    int attempts;

    while (1)
    {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Update\n");
        printf("5. Exit\n");

        for (attempts = 1; attempts <= 3; attempts++)
        {
            printf("Enter your choice: ");

            if (scanf("%d", &choice) == 1)
            {
                if (getchar() == '\n')
                {
                    break;
                }
                else
                {
                    clearInput();
                    printf("Invalid choice! Attempt %d of 3\n", attempts);
                }
            }
            else
            {
                printf("Invalid choice! Attempt %d of 3\n", attempts);
                clearInput();
            }
        }

        if (attempts > 3)
        {
            printf("3 attempts completed. Program ended.\n");
            break;
        }

        switch (choice)
        {
            case 1:

                for (attempts = 1; attempts <= 3; attempts++)
                {
                    printf("Enter value: ");

                    if (scanf("%d", &value) == 1)
                    {
                        if (getchar() == '\n')
                        {
                            if (value < 0)
                            {
                                printf("Invalid value! Negative values are not allowed. Attempt %d of 3\n", attempts);
                                continue;
                            }

                            break;
                        }
                        else
                        {
                            clearInput();
                            printf("Invalid value! Attempt %d of 3\n", attempts);
                        }
                    }
                    else
                    {
                        printf("Invalid value! Attempt %d of 3\n", attempts);
                        clearInput();
                    }
                }

                if (attempts <= 3)
                {
                    push(value);
                }
                else
                {
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