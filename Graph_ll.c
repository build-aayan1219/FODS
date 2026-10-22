
#include <stdio.h>
#include <stdlib.h>

#define NO_OF_ELEMENTS 5

struct Node
{
    int vertex;
    struct Node *next;
};

char vertex_name[NO_OF_ELEMENTS] = {'A', 'B', 'C', 'D', 'E'};

struct Node *adjacency[NO_OF_ELEMENTS];

int stack[NO_OF_ELEMENTS];
int top = -1;

int queue[NO_OF_ELEMENTS];
int front = -1;
int rear = -1;

int visited[NO_OF_ELEMENTS];

int getVertexIndex(char vertex)
{
    int i;
    for (i = 0; i < NO_OF_ELEMENTS; i++)
    {
        if (vertex_name[i] == vertex)
            return i;
    }
    return -1;
}

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
        return -1;

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
        return -1;

    vertex = queue[front];
    front++;

    return vertex;
}

void DFS(int startIndex)
{
    int row;
    struct Node *temp;

    push(startIndex);
    visited[startIndex] = 1;

    while (top != -1)
    {
        row = pop();
        printf("%c ", vertex_name[row]);
        temp = adjacency[row];

        while (temp != NULL)
        {
            if (visited[temp->vertex] == 0)
            {
                push(temp->vertex);
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void BFS(int startIndex)
{
    int row;
    struct Node *temp;

    enqueue(startIndex);
    visited[startIndex] = 1;
    while (front != -1 && front <= rear)
    {
        row = dequeue();
        printf("%c ", vertex_name[row]);
        temp = adjacency[row];

        while (temp != NULL)
        {
            if (visited[temp->vertex] == 0)
            {
                enqueue(temp->vertex);
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void createEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex;
    struct Node *temp, *newNode;

    printf("Enter first vertex (A-E): ");
    scanf(" %c", &firstVertex);

    printf("Enter second vertex (A-E): ");
    scanf(" %c", &secondVertex);

    firstIndex = getVertexIndex(firstVertex);
    secondIndex = getVertexIndex(secondVertex);

    if (firstIndex == -1 || secondIndex == -1)
    {
        printf("Invalid vertex!\n");
        return;
    }

    if (firstIndex == secondIndex)
    {
        printf("Cannot connect a vertex to itself.\n");
        return;
    }
    temp = adjacency[firstIndex];

    while (temp != NULL)
    {
        if (temp->vertex == secondIndex)
        {
            printf("Edge already exists.\n");
            return;
        }
        temp = temp->next;
    }

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = secondIndex;
    newNode->next = adjacency[firstIndex];
    adjacency[firstIndex] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = firstIndex;
    newNode->next = adjacency[secondIndex];
    adjacency[secondIndex] = newNode;

    printf("Edge created successfully.\n");
}

void updateEdge()
{
    char firstVertex, oldVertex, newVertex;
    int firstIndex, oldIndex, newIndex;
    struct Node *temp, *prev, *newNode;

    printf("Enter first vertex of existing edge (A-E): ");
    scanf(" %c", &firstVertex);

    printf("Enter second vertex of existing edge (A-E): ");
    scanf(" %c", &oldVertex);

    firstIndex = getVertexIndex(firstVertex);
    oldIndex = getVertexIndex(oldVertex);

    if (firstIndex == -1 || oldIndex == -1)
    {
        printf("Invalid vertex!\n");
        return;
    }

    if (firstIndex == oldIndex)
    {
        printf("Existing edge not found.\n");
        return;
    }

    temp = adjacency[firstIndex];   

    while (temp != NULL && temp->vertex != oldIndex)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Existing edge not found.\n");
        return;
    }

    printf("Enter new second vertex (A-E): ");
    scanf(" %c", &newVertex);

    newIndex = getVertexIndex(newVertex);

    if (newIndex == -1)
    {
        printf("Invalid vertex!\n");
        return;
    }

    if (firstIndex == newIndex)
    {
        printf("Cannot connect a vertex to itself.\n");
        return;
    }

    temp = adjacency[firstIndex];

    while (temp != NULL)
    {
        if (temp->vertex == newIndex)
        {
            printf("The new edge already exists.\n");
            return;
        }
        temp = temp->next;
    }

    prev = NULL;
    temp = adjacency[firstIndex];

    while (temp->vertex != oldIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        adjacency[firstIndex] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    prev = NULL;
    temp = adjacency[oldIndex];

    while (temp->vertex != firstIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        adjacency[oldIndex] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = newIndex;
    newNode->next = adjacency[firstIndex];
    adjacency[firstIndex] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = firstIndex;
    newNode->next = adjacency[newIndex];
    adjacency[newIndex] = newNode;

    printf("Edge updated successfully.\n");
}

void deleteEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex;
    struct Node *temp, *prev;

    printf("Enter first vertex (A-E): ");
    scanf(" %c", &firstVertex);

    printf("Enter second vertex (A-E): ");
    scanf(" %c", &secondVertex);

    firstIndex = getVertexIndex(firstVertex);
    secondIndex = getVertexIndex(secondVertex);

    if (firstIndex == -1 || secondIndex == -1)
    {
        printf("Invalid vertex!\n");
        return;
    }

    if (firstIndex == secondIndex)
    {
        printf("Cannot connect a vertex to itself.\n");
        return;
    }

    temp = adjacency[firstIndex];

    while (temp != NULL && temp->vertex != secondIndex)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Edge not found.\n");
        return;
    }

    prev = NULL;
    temp = adjacency[firstIndex];

    while (temp->vertex != secondIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        adjacency[firstIndex] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    prev = NULL;
    temp = adjacency[secondIndex];

    while (temp->vertex != firstIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        adjacency[secondIndex] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Edge deleted successfully.\n");
}

void displayVertices()
{
    int i;

    printf("Vertices: ");

    for (i = 0; i < NO_OF_ELEMENTS; i++)
        printf("%c ", vertex_name[i]);

    printf("\n");
}

int main()
{
    char vertex;
    int choice, startIndex, i;
    struct Node *newNode, *temp;

    for (i = 0; i < NO_OF_ELEMENTS; i++)
        adjacency[i] = NULL;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = 1;
    newNode->next = malloc(sizeof(struct Node));
    newNode->next->vertex = 2;
    newNode->next->next = NULL;
    adjacency[0] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = 0;
    newNode->next = malloc(sizeof(struct Node));
    newNode->next->vertex = 3;
    newNode->next->next = NULL;
    adjacency[1] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = 0;
    newNode->next = malloc(sizeof(struct Node));
    newNode->next->vertex = 3;
    newNode->next->next = malloc(sizeof(struct Node));
    newNode->next->next->vertex = 4;
    newNode->next->next->next = NULL;
    adjacency[2] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = 1;
    newNode->next = malloc(sizeof(struct Node));
    newNode->next->vertex = 2;
    newNode->next->next = malloc(sizeof(struct Node));
    newNode->next->next->vertex = 4;
    newNode->next->next->next = NULL;
    adjacency[3] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->vertex = 2;
    newNode->next = malloc(sizeof(struct Node));
    newNode->next->vertex = 3;
    newNode->next->next = NULL;
    adjacency[4] = newNode;

    while (1)
    {
        printf("\n1. DFS\n");
        printf("2. BFS\n");
        printf("3. Create Edge\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Display Vertices\n");
        printf("7. Display Adjacency List\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2)
        {
            printf("Enter starting vertex (A-E): ");
            scanf(" %c", &vertex);

            startIndex = getVertexIndex(vertex);

            if (startIndex == -1)
            {
                printf("Invalid vertex!\n");
                continue;
            }

            for (i = 0; i < NO_OF_ELEMENTS; i++)
                visited[i] = 0;

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
        else if (choice == 3)
            createEdge();
        else if (choice == 4)
            updateEdge();
        else if (choice == 5)
            deleteEdge();
        else if (choice == 6)
            displayVertices();
        else if (choice == 7)
        {
            for (i = 0; i < NO_OF_ELEMENTS; i++)
            {
                printf("%c -> ", vertex_name[i]);

                temp = adjacency[i];

                while (temp != NULL)
                {
                    printf("%c -> ", vertex_name[temp->vertex]);
                    temp = temp->next;
                }

                printf("NULL\n");
            }
        }
        else if (choice == 8)
        {
            printf("Program ended.\n");
            return 0;
        }
        else
            printf("Invalid choice!\n");
    }
}
