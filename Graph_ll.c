#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 5

char vertex[MAX] = {'A', 'B', 'C', 'D', 'E'};

struct Node
{
    int vertex;
    struct Node *next;
};

struct Node *adj[MAX] = {NULL, NULL, NULL, NULL, NULL};
int visited[MAX];

struct QueueNode
{
    int vertex;
    struct QueueNode *next;
};

struct QueueNode *front = NULL;
struct QueueNode *rear = NULL;

void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInteger(int *n)
{
    int c;

    if (scanf("%d", n) != 1)
    {
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

int vertexIndex(char ch)
{
    int i;
    ch = (char)toupper((unsigned char)ch);

    for (i = 0; i < MAX; i++)
    {
        if (vertex[i] == ch)
            return i;
    }

    return -1;
}

void addEdge(int a, int b)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->vertex = b;
    newNode->next = adj[a];
    adj[a] = newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        struct Node *temp = adj[a];
        adj[a] = temp->next;
        free(temp);
        printf("Memory allocation failed\n");
        return;
    }
    newNode->vertex = a;
    newNode->next = adj[b];
    adj[b] = newNode;
}

int edgeExists(int a, int b)
{
    struct Node *temp = adj[a];

    while (temp != NULL)
    {
        if (temp->vertex == b)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void deleteOneSide(int a, int b)
{
    struct Node *temp = adj[a];
    struct Node *previous = NULL;

    while (temp != NULL)
    {
        if (temp->vertex == b)
        {
            if (previous == NULL)
                adj[a] = temp->next;
            else
                previous->next = temp->next;

            free(temp);
            return;
        }
        previous = temp;
        temp = temp->next;
    }
}

void deleteEdge(int a, int b)
{
    deleteOneSide(a, b);
    deleteOneSide(b, a);
}

void DFS(int v)
{
    struct Node *temp;

    visited[v] = 1;
    printf("%c ", vertex[v]);

    temp = adj[v];
    while (temp != NULL)
    {
        if (visited[temp->vertex] == 0)
            DFS(temp->vertex);
        temp = temp->next;
    }
}

void enqueue(int v)
{
    struct QueueNode *newNode;

    newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->vertex = v;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue()
{
    struct QueueNode *temp;
    int v;

    if (front == NULL)
        return -1;

    temp = front;
    v = temp->vertex;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
    return v;
}

void BFS(int start)
{
    struct Node *temp;
    int v, i;

    for (i = 0; i < MAX; i++)
        visited[i] = 0;

    front = NULL;
    rear = NULL;
    enqueue(start);
    visited[start] = 1;

    while (front != NULL)
    {
        v = dequeue();
        printf("%c ", vertex[v]);

        temp = adj[v];
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

void displayGraph()
{
    int i;
    struct Node *temp;

    printf("\nAdjacency List:\n");
    for (i = 0; i < MAX; i++)
    {
        printf("%c -> ", vertex[i]);
        temp = adj[i];
        while (temp != NULL)
        {
            printf("%c -> ", vertex[temp->vertex]);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    int choice, a, b, i, attempts, valid, start;
    char ch1, ch2;
    struct Node *temp;

    /* Initial graph edges */
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(2, 4);
    addEdge(3, 4);

    do
    {
        printf("\n1. DFS\n");
        printf("2. BFS\n");
        printf("3. Create Edge\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Display Vertices\n");
        printf("7. Display Adjacency List\n");
        printf("8. Exit\n");

        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter your choice: ");
            if (readInteger(&choice) == 1 && choice >= 1 && choice <= 8)
                valid = 1;
            else
                printf("Invalid input! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Program ended.\n");
            choice = 8;
        }
        else if (choice == 1 || choice == 2)
        {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter starting vertex (A-E): ");
                if (scanf(" %c", &ch1) == 1)
                {
                    clearInput();
                    start = vertexIndex(ch1);
                    if (start != -1)
                        valid = 1;
                }
                else
                    clearInput();

                if (valid == 0)
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
            }

            if (valid == 1)
            {
                for (i = 0; i < MAX; i++)
                    visited[i] = 0;

                if (choice == 1)
                {
                    printf("DFS: ");
                    DFS(start);
                }
                else
                {
                    printf("BFS: ");
                    BFS(start);
                }
                printf("\n");
            }
        }
        else if (choice == 3 || choice == 5)
        {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter first vertex (A-E): ");
                if (scanf(" %c", &ch1) != 1)
                {
                    clearInput();
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
                    continue;
                }
                clearInput();
                a = vertexIndex(ch1);

                printf("Enter second vertex (A-E): ");
                if (scanf(" %c", &ch2) != 1)
                {
                    clearInput();
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
                    continue;
                }
                clearInput();
                b = vertexIndex(ch2);

                if (a != -1 && b != -1 && a != b)
                    valid = 1;
                else
                    printf("Invalid vertices! Attempt %d of 3\n", attempts);
            }

            if (valid == 1)
            {
                if (choice == 3)
                {
                    if (edgeExists(a, b))
                        printf("Edge already exists\n");
                    else
                    {
                        addEdge(a, b);
                        if (edgeExists(a, b))
                            printf("Edge created successfully\n");
                    }
                }
                else
                {
                    if (edgeExists(a, b))
                    {
                        deleteEdge(a, b);
                        printf("Edge deleted successfully\n");
                    }
                    else
                        printf("Edge not found\n");
                }
            }
        }
        else if (choice == 4)
        {
            printf("Enter old edge's first vertex (A-E): ");
            if (scanf(" %c", &ch1) == 1)
            {
                clearInput();
                a = vertexIndex(ch1);
                printf("Enter old edge's second vertex (A-E): ");
                if (scanf(" %c", &ch2) == 1)
                {
                    clearInput();
                    b = vertexIndex(ch2);
                    if (a != -1 && b != -1 && a != b && edgeExists(a, b))
                    {
                        printf("Enter new edge's first vertex (A-E): ");
                        if (scanf(" %c", &ch1) == 1)
                        {
                            clearInput();
                            i = vertexIndex(ch1);
                            printf("Enter new edge's second vertex (A-E): ");
                            if (scanf(" %c", &ch2) == 1)
                            {
                                clearInput();
                                start = vertexIndex(ch2);
                                if (i != -1 && start != -1 && i != start && !edgeExists(i, start))
                                {
                                    deleteEdge(a, b);
                                    addEdge(i, start);
                                    printf("Edge updated successfully\n");
                                }
                                else
                                    printf("Invalid new edge or edge already exists\n");
                            }
                            else
                            {
                                clearInput();
                                printf("Invalid input\n");
                            }
                        }
                        else
                        {
                            clearInput();
                            printf("Invalid input\n");
                        }
                    }
                    else
                        printf("Old edge not found or invalid\n");
                }
                else
                {
                    clearInput();
                    printf("Invalid input\n");
                }
            }
            else
            {
                clearInput();
                printf("Invalid input\n");
            }
        }
        else if (choice == 6)
        {
            printf("Vertices: ");
            for (i = 0; i < MAX; i++)
                printf("%c ", vertex[i]);
            printf("\n");
        }
        else if (choice == 7)
            displayGraph();

    } while (choice != 8);

    for (i = 0; i < MAX; i++)
    {
        temp = adj[i];
        while (temp != NULL)
        {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    while (front != NULL)
        dequeue();

    printf("Program ended.\n");
    return 0;
}
