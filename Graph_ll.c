
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node
{
    int vertex;
    struct Node *next;
};

char vertex_name[MAX_VERTICES];
struct Node *adjacency[MAX_VERTICES];
int no_of_elements = 0;
int stack[MAX_VERTICES], top = -1;
int queue[MAX_VERTICES], front = -1, rear = -1;
int visited[MAX_VERTICES];

void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInteger(int *value)
{
    int c;
    if (scanf("%d", value) != 1)
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

int readVertex(char *vertex)
{
    int c;
    if (scanf(" %c", vertex) != 1)
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

int getVertexIndex(char vertex)
{
    int i;
    for (i = 0; i < no_of_elements; i++)
        if (vertex_name[i] == vertex)
            return i;
    return -1;
}

int readValidVertex(char *vertex, char message[])
{
    int attempts, valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("%s", message);
        if (readVertex(vertex) == 1 && getVertexIndex(*vertex) != -1)
            valid = 1;
        else
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
        printf("3 attempts completed. Operation cancelled.\n");

    return valid;
}

void push(int vertex)
{
    if (top < no_of_elements - 1)
        stack[++top] = vertex;
}

int pop()
{
    if (top == -1)
        return -1;
    return stack[top--];
}

void enqueue(int vertex)
{
    if (rear < no_of_elements - 1)
    {
        if (front == -1)
            front = 0;
        queue[++rear] = vertex;
    }
}

int dequeue()
{
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

int addEdge(int firstIndex, int secondIndex)
{
    struct Node *temp, *firstNode, *secondNode;

    if (firstIndex == secondIndex)
        return 0;

    temp = adjacency[firstIndex];
    while (temp != NULL)
    {
        if (temp->vertex == secondIndex)
            return 0;
        temp = temp->next;
    }

    firstNode = malloc(sizeof(struct Node));
    secondNode = malloc(sizeof(struct Node));

    if (firstNode == NULL || secondNode == NULL)
    {
        free(firstNode);
        free(secondNode);
        return -1;
    }

    firstNode->vertex = secondIndex;
    firstNode->next = adjacency[firstIndex];
    secondNode->vertex = firstIndex;
    secondNode->next = adjacency[secondIndex];

    adjacency[firstIndex] = firstNode;
    adjacency[secondIndex] = secondNode;

    return 1;
}

int removeEdge(int firstIndex, int secondIndex)
{
    struct Node *temp, *prev;

    prev = NULL;
    temp = adjacency[firstIndex];

    while (temp != NULL && temp->vertex != secondIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return 0;

    if (prev == NULL)
        adjacency[firstIndex] = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    prev = NULL;
    temp = adjacency[secondIndex];

    while (temp != NULL && temp->vertex != firstIndex)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        if (prev == NULL)
            adjacency[secondIndex] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
    }

    return 1;
}

int hasLinks()
{
    int i;
    for (i = 0; i < no_of_elements; i++)
        if (adjacency[i] != NULL)
            return 1;
    return 0;
}

int isConnected()
{
    int i, current, count = 0, tempTop = -1;
    int tempVisited[MAX_VERTICES] = {0};
    int tempStack[MAX_VERTICES];
    struct Node *temp;

    if (no_of_elements == 0)
        return 0;

    tempStack[++tempTop] = 0;
    tempVisited[0] = 1;

    while (tempTop != -1)
    {
        current = tempStack[tempTop--];
        count++;
        temp = adjacency[current];

        while (temp != NULL)
        {
            i = temp->vertex;
            if (tempVisited[i] == 0)
            {
                tempVisited[i] = 1;
                tempStack[++tempTop] = i;
            }
            temp = temp->next;
        }
    }

    return count == no_of_elements;
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

int createGraph()
{
    int attempts, valid, i, j, count, result;
    char vertex, connectedVertex;

    valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
        if (readInteger(&no_of_elements) == 1 && no_of_elements >= 1 && no_of_elements <= MAX_VERTICES)
            valid = 1;
        else
            printf("Invalid number of vertices! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Graph creation cancelled.\n");
        return 0;
    }

    for (i = 0; i < MAX_VERTICES; i++)
        adjacency[i] = NULL;

    for (i = 0; i < no_of_elements; i++)
    {
        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter name for vertex %d: ", i + 1);

            if (readVertex(&vertex) == 1)
            {
                valid = 1;
                for (j = 0; j < i; j++)
                    if (vertex_name[j] == vertex)
                        valid = 0;
            }

            if (valid == 0)
                printf("Invalid or duplicate vertex name! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Graph creation cancelled.\n");
            return 0;
        }

        vertex_name[i] = vertex;
    }

    for (i = 0; i < no_of_elements; i++)
    {
        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter number of edges for vertex %c (0-%d): ", vertex_name[i], no_of_elements - 1);
            if (readInteger(&count) == 1 && count >= 0 && count <= no_of_elements - 1)
                valid = 1;
            else
                printf("Invalid number of edges! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Graph creation cancelled.\n");
            return 0;
        }

        for (j = 0; j < count; j++)
        {
            valid = 0;

            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter vertex connected to %c: ", vertex_name[i]);

                if (readVertex(&connectedVertex) == 1 && getVertexIndex(connectedVertex) != -1 && getVertexIndex(connectedVertex) != i)
                {
                    result = addEdge(i, getVertexIndex(connectedVertex));
                    if (result == 1)
                        valid = 1;
                    else if (result == -1)
                    {
                        printf("Memory allocation failed.\n");
                        return 0;
                    }
                    else
                        printf("Self-links and duplicate edges are not allowed.\n");
                }
                else
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
            }

            if (valid == 0)
            {
                printf("3 attempts completed. Continuing to the next vertex.\n");
                break;
            }
        }
    }

    printf("Graph created successfully.\n");
    return 1;
}

void createEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex, count, i, attempts, valid, result;

    if (!readValidVertex(&firstVertex, "Enter starting vertex: "))
        return;

    firstIndex = getVertexIndex(firstVertex);
    valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter number of edges to create: ");
        if (readInteger(&count) == 1 && count >= 0 && count <= no_of_elements - 1)
            valid = 1;
        else
            printf("Invalid number! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Create edge cancelled.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        printf("Edge %d of %d\n", i + 1, count);

        if (!readValidVertex(&secondVertex, "Enter connected vertex: "))
            return;

        secondIndex = getVertexIndex(secondVertex);
        result = addEdge(firstIndex, secondIndex);

        if (result == 1)
            printf("Edge created successfully.\n");
        else if (result == 0)
            printf("Cannot create edge. Self-links and duplicate edges are not allowed.\n");
        else
            printf("Memory allocation failed.\n");
    }
}

void updateEdge()
{
    char firstVertex, oldVertex, newVertex;
    int firstIndex, oldIndex, newIndex, result;
    struct Node *temp;

    if (!readValidVertex(&firstVertex, "Enter first vertex of existing edge: "))
        return;

    if (!readValidVertex(&oldVertex, "Enter second vertex of existing edge: "))
        return;

    firstIndex = getVertexIndex(firstVertex);
    oldIndex = getVertexIndex(oldVertex);

    temp = adjacency[firstIndex];                                       
    while (temp != NULL && temp->vertex != oldIndex)
        temp = temp->next;

    if (firstIndex == oldIndex || temp == NULL)
    {
        printf("Existing edge not found.\n");
        return;
    }

    if (!readValidVertex(&newVertex, "Enter new second vertex: "))
        return;

    newIndex = getVertexIndex(newVertex);

    if (firstIndex == newIndex)
    {
        printf("Cannot connect a vertex to itself.\n");
        return;
    }

    temp = adjacency[firstIndex];                                           //check for duplicate edge
    while (temp != NULL)
    {
        if (temp->vertex == newIndex)
        {
            printf("The new edge already exists.\n");
            return;
        }
        temp = temp->next;
    }

    removeEdge(firstIndex, oldIndex);                                   //remove old edge
    result = addEdge(firstIndex, newIndex);                             //add new edge

    if (result == 1)
        printf("Edge updated successfully.\n");
    else
        printf("Unable to update edge.\n");
}

void deleteEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex;

    if (!readValidVertex(&firstVertex, "Enter first vertex: "))
        return;

    if (!readValidVertex(&secondVertex, "Enter second vertex: "))
        return;

    firstIndex = getVertexIndex(firstVertex);
    secondIndex = getVertexIndex(secondVertex);

    if (firstIndex == secondIndex)
    {
        printf("Cannot connect a vertex to itself.\n");
        return;
    }

    if (removeEdge(firstIndex, secondIndex))
        printf("Edge deleted successfully.\n");
    else
        printf("Edge not found.\n");
}

void addVertex()
{
    char vertex;
    int attempts, valid = 0, i;

    if (no_of_elements == MAX_VERTICES)
    {
        printf("Maximum number of vertices reached.\n");
        return;
    }

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter new vertex name: ");

        if (readVertex(&vertex) == 1)
        {
            valid = 1;
            for (i = 0; i < no_of_elements; i++)
                if (vertex_name[i] == vertex)
                    valid = 0;
        }

        if (valid == 0)
            printf("Invalid or duplicate vertex name! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Add vertex cancelled.\n");
        return;
    }

    vertex_name[no_of_elements] = vertex;
    adjacency[no_of_elements] = NULL;
    no_of_elements++;

    printf("Vertex added successfully.\n");
}

void updateVertex()
{
    char oldVertex, newVertex;
    int oldIndex, attempts, valid = 0, i;

    if (!readValidVertex(&oldVertex, "Enter vertex to update: "))
        return;

    oldIndex = getVertexIndex(oldVertex);

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter new vertex name: ");

        if (readVertex(&newVertex) == 1)
        {
            valid = 1;
            for (i = 0; i < no_of_elements; i++)
                if (vertex_name[i] == newVertex)
                    valid = 0;
        }

        if (valid == 0)
            printf("Invalid or duplicate vertex name! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Update vertex cancelled.\n");
        return;
    }

    vertex_name[oldIndex] = newVertex;
    printf("Vertex updated successfully.\n");
}

void deleteVertex()
{
    char vertex;
    int index, i;
    struct Node *temp, *nextNode;

    if (no_of_elements == 0)
    {
        printf("There are no vertices.\n");
        return;
    }

    if (!readValidVertex(&vertex, "Enter vertex to delete: "))
        return;

    index = getVertexIndex(vertex);

    temp = adjacency[index];
    while (temp != NULL)
    {
        nextNode = temp->next;
        removeEdge(index, temp->vertex);
        temp = nextNode;
    }

    for (i = 0; i < no_of_elements; i++)
    {
        temp = adjacency[i];
        while (temp != NULL)
        {
            if (temp->vertex > index)
                temp->vertex--;
            temp = temp->next;
        }
    }

    for (i = index; i < no_of_elements - 1; i++)
    {
        vertex_name[i] = vertex_name[i + 1];
        adjacency[i] = adjacency[i + 1];
    }

    no_of_elements--;
    adjacency[no_of_elements] = NULL;

    printf("Vertex deleted successfully.\n");
}

void displayVertices()
{
    int i;

    printf("Vertices: ");
    for (i = 0; i < no_of_elements; i++)
        printf("%c ", vertex_name[i]);
    printf("\n");
}

void displayAdjacencyList()
{
    int i;
    struct Node *temp;

    for (i = 0; i < no_of_elements; i++)
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

int main()
{
    char vertex;
    int choice, startIndex, i, attempts, valid;

    if (!createGraph())
        return 0;

    while (1)
    {
        printf("\n1. DFS\n");
        printf("2. BFS\n");
        printf("3. Create Edge\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Add Vertex\n");
        printf("7. Update Vertex\n");
        printf("8. Delete Vertex\n");
        printf("9. Display Vertices\n");
        printf("10. Display Adjacency List\n");
        printf("11. Exit\n");

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter your choice: ");
            if (readInteger(&choice) == 1 && choice >= 1 && choice <= 11)
                valid = 1;
            else
                printf("Invalid input! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Program ended.\n");
            return 0;
        }

        if (choice == 1 || choice == 2)
        {
            if (no_of_elements == 0)
            {
                printf("There are no vertices.\n");
                continue;
            }

            if (!hasLinks())
            {
                printf("There is no graph as there are no links.\n");
                continue;
            }

            if (!isConnected())
            {
                printf("All vertices are not connected. Connect them.\n");
                continue;
            }

            if (!readValidVertex(&vertex, "Enter starting vertex: "))
                continue;

            startIndex = getVertexIndex(vertex);

            for (i = 0; i < no_of_elements; i++)
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
            addVertex();
        else if (choice == 7)
            updateVertex();
        else if (choice == 8)
            deleteVertex();
        else if (choice == 9)
            displayVertices();
        else if (choice == 10)
            displayAdjacencyList();
        else if (choice == 11)
        {
            printf("Program ended.\n");
            return 0;
        }
    }
}
