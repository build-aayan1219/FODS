#include <stdio.h>

#define NO_OF_ELEMENTS 5

char vertex_name[NO_OF_ELEMENTS] = {'A', 'B', 'C', 'D', 'E'};

int vertices_matrix[NO_OF_ELEMENTS][NO_OF_ELEMENTS] = {
    {0, 1, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {1, 0, 0, 1, 1},
    {0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0}
};

int stack[NO_OF_ELEMENTS];
int top = -1;

int queue[NO_OF_ELEMENTS];
int front = -1;
int rear = -1;

int visited[NO_OF_ELEMENTS];

void push(int vertex)
{
    if (top < NO_OF_ELEMENTS - 1)
    {
        top++;
        stack[top] = vertex;
    }
}

int pop()
{
    int vertex;

    if (top == -1)
    {
        return -1;
    }

    vertex = stack[top];
    top--;

    return vertex;
}

void enqueue(int vertex)
{
    if (rear < NO_OF_ELEMENTS - 1)
    {
        if (front == -1)
            front = 0;

        rear++;
        queue[rear] = vertex;
    }
}

int dequeue()
{
    int vertex;

    if (front == -1 || front > rear)
    {
        return -1;
    }

    vertex = queue[front];
    front++;

    return vertex;
}

char getName(int index)
{
    return vertex_name[index];
}

int getVertexIndex(char vertex)
{
    int vertexIndex = NO_OF_ELEMENTS - 1;

    while (vertexIndex >= 0 && vertex != vertex_name[vertexIndex])
    {
        vertexIndex--;
    }

    return vertexIndex;
}

void DFS(int startIndex)
{
    int row, column;

    push(startIndex);
    visited[startIndex] = 1;

    while (top != -1)
    {
        row = pop();

        printf("%c ", getName(row));

        for (column = 0; column < NO_OF_ELEMENTS; column++)
        {
            if (vertices_matrix[row][column] == 1 && visited[column] == 0)
            {
                push(column);
                visited[column] = 1;
            }
        }
    }
}

void BFS(int startIndex)
{
    int row, column;

    enqueue(startIndex);
    visited[startIndex] = 1;

    while (front != -1 && front <= rear)
    {
        row = dequeue();

        printf("%c ", getName(row));

        for (column = 0; column < NO_OF_ELEMENTS; column++)
        {
            if (vertices_matrix[row][column] == 1 && visited[column] == 0)
            {
                enqueue(column);
                visited[column] = 1;
            }
        }
    }
}

int main()
{
    char vertex;
    int startIndex;
    int choice;
    int i;

    while (1)
    {
        printf("\n1. DFS\n");
        printf("2. BFS\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 3)
        {
            printf("Exiting...");
            break;
        }

        if (choice == 1 || choice == 2)
        {
            printf("Enter starting vertex: ");
            scanf(" %c", &vertex);

            startIndex = getVertexIndex(vertex);

            if (startIndex == -1)
            {
                printf("Vertex not found\n");
                continue;
            }

            for (i = 0; i < NO_OF_ELEMENTS; i++)
            {
                visited[i] = 0;
            }

            top = -1;
            front = -1;
            rear = -1;

            if (choice == 1)
            {
                printf("DFS Traversal: ");
                DFS(startIndex);
            }
            else
            {
                printf("BFS Traversal: ");
                BFS(startIndex);
            }

            printf("\n");
        }
        else
        {
            printf("Invalid choice\n");
        }
    }

    return 0;
}