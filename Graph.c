#include <stdio.h>

#define MAX_VERTICES 5

char vertex_name[MAX_VERTICES];
int vertices_matrix[MAX_VERTICES][MAX_VERTICES];
int no_of_elements = 0;

int stack[MAX_VERTICES];
int top = -1;

int queue[MAX_VERTICES];
int front = -1;
int rear = -1;

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
    {
        if (vertex_name[i] == vertex)
            return i;
    }
    return -1;
}

char getName(int index)
{
    return vertex_name[index];
}

void push(int vertex)
{
    if (top < no_of_elements - 1)
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
    if (rear < no_of_elements - 1)
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

void createGraph()
{
    int i, j, k, count, valid, attempts;
    char vertex, connectedVertex;
    int connectedIndex;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter total number of vertices (1-5): ");
        if (readInteger(&no_of_elements) == 1 && no_of_elements >= 1 && no_of_elements <= MAX_VERTICES)
            valid = 1;
        else
            printf("Invalid input! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Graph not created.\n");
        no_of_elements = 0;
        return;
    }

    for (i = 0; i < MAX_VERTICES; i++)
    {
        for (j = 0; j < MAX_VERTICES; j++)
            vertices_matrix[i][j] = 0;
    }

    for (i = 0; i < no_of_elements; i++)
    {
        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter vertex %d (A-E): ", i + 1);
            if (readVertex(&vertex) == 1 && vertex >= 'A' && vertex <= 'E')
            {
                valid = 1;
                for (j = 0; j < i; j++)
                {
                    if (vertex_name[j] == vertex)
                        valid = 0;
                }
            }
            if (valid == 0)
                printf("Invalid or duplicate vertex! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Graph not created.\n");
            no_of_elements = 0;
            return;
        }
        vertex_name[i] = vertex;
    }

    for (i = 0; i < no_of_elements; i++)
    {
        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("How many links of %c? ", vertex_name[i]);
            if (readInteger(&count) == 1 && count >= 0 && count < no_of_elements)
                valid = 1;
            else
                printf("Invalid input! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Graph not created.\n");
            no_of_elements = 0;
            for (j = 0; j < MAX_VERTICES; j++)
            {
                for (k = 0; k < MAX_VERTICES; k++)
                    vertices_matrix[j][k] = 0;
            }
            return;
        }

        for (j = 0; j < count; j++)
        {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter connected vertex %d of %c: ", j + 1, vertex_name[i]);
                if (readVertex(&connectedVertex) == 1)
                {
                    connectedIndex = getVertexIndex(connectedVertex);
                    if (connectedIndex != -1 && connectedIndex != i && vertices_matrix[i][connectedIndex] == 0)
                        valid = 1;
                }
                if (valid == 0)
                    printf("Invalid vertex, duplicate link or self-connection! Attempt %d of 3\n", attempts);
            }

            if (valid == 0)
            {
                printf("3 attempts completed. Graph not created.\n");
                no_of_elements = 0;
                for (k = 0; k < MAX_VERTICES; k++)
                {
                    for (int l = 0; l < MAX_VERTICES; l++)
                        vertices_matrix[k][l] = 0;
                }
                return;
            }

            vertices_matrix[i][connectedIndex] = 1;
            vertices_matrix[connectedIndex][i] = 1;
        }
    }
    printf("Graph created successfully.\n");
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
        for (column = 0; column < no_of_elements; column++)
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
        for (column = 0; column < no_of_elements; column++)
        {
            if (vertices_matrix[row][column] == 1 && visited[column] == 0)
            {
                enqueue(column);
                visited[column] = 1;
            }
        }
    }
}

void createEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex: ");
        if (readVertex(&firstVertex) == 1)
        {
            firstIndex = getVertexIndex(firstVertex);
            if (firstIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Graph not created.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter second vertex: ");
        if (readVertex(&secondVertex) == 1)
        {
            secondIndex = getVertexIndex(secondVertex);
            if (secondIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Graph not created.\n");
        return;
    }

    if (firstIndex == secondIndex)
        printf("Cannot connect a vertex to itself.\n");
    else if (vertices_matrix[firstIndex][secondIndex] == 1)
        printf("Edge already exists.\n");
    else
    {
        vertices_matrix[firstIndex][secondIndex] = 1;
        vertices_matrix[secondIndex][firstIndex] = 1;
        printf("Edge created successfully.\n");
    }
}

void updateEdge()
{
    char firstVertex, oldVertex, newVertex;
    int firstIndex, oldIndex, newIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex of existing edge: ");
        if (readVertex(&firstVertex) == 1)
        {
            firstIndex = getVertexIndex(firstVertex);
            if (firstIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter second vertex of existing edge: ");
        if (readVertex(&oldVertex) == 1)
        {
            oldIndex = getVertexIndex(oldVertex);
            if (oldIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    if (firstIndex == oldIndex || vertices_matrix[firstIndex][oldIndex] == 0)
    {
        printf("Existing edge not found.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter new second vertex: ");
        if (readVertex(&newVertex) == 1)
        {
            newIndex = getVertexIndex(newVertex);
            if (newIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Update cancelled.\n");
        return;
    }

    if (firstIndex == newIndex)
        printf("Cannot connect a vertex to itself.\n");
    else if (vertices_matrix[firstIndex][newIndex] == 1)
        printf("The new edge already exists.\n");
    else
    {
        vertices_matrix[firstIndex][oldIndex] = 0;
        vertices_matrix[oldIndex][firstIndex] = 0;
        vertices_matrix[firstIndex][newIndex] = 1;
        vertices_matrix[newIndex][firstIndex] = 1;
        printf("Edge updated successfully.\n");
    }
}

void deleteEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex: ");
        if (readVertex(&firstVertex) == 1)
        {
            firstIndex = getVertexIndex(firstVertex);
            if (firstIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Delete cancelled.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter second vertex: ");
        if (readVertex(&secondVertex) == 1)
        {
            secondIndex = getVertexIndex(secondVertex);
            if (secondIndex != -1)
                valid = 1;
        }
        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }
    if (valid == 0)
    {
        printf("3 attempts completed. Delete cancelled.\n");
        return;
    }

    if (firstIndex == secondIndex)
        printf("Cannot connect a vertex to itself.\n");
    else if (vertices_matrix[firstIndex][secondIndex] == 0)
        printf("Edge not found.\n");
    else
    {
        vertices_matrix[firstIndex][secondIndex] = 0;
        vertices_matrix[secondIndex][firstIndex] = 0;
        printf("Edge deleted successfully.\n");
    }
}

void displayMatrix()
{
    int i, j;
    if (no_of_elements == 0)
    {
        printf("No graph available.\n");
        return;
    }

    printf("  ");
    for (i = 0; i < no_of_elements; i++)
        printf("%c ", vertex_name[i]);
    printf("\n");

    for (i = 0; i < no_of_elements; i++)
    {
        printf("%c ", vertex_name[i]);
        for (j = 0; j < no_of_elements; j++)
            printf("%d ", vertices_matrix[i][j]);
        printf("\n");
    }
}

void displayVertices()
{
    int i;
    if (no_of_elements == 0)
    {
        printf("No graph available.\n");
        return;
    }

    printf("Vertices: ");
    for (i = 0; i < no_of_elements; i++)
        printf("%c ", vertex_name[i]);
    printf("\n");
}

int main()
{
    char vertex;
    int startIndex, choice, i, attempts, valid, exitProgram;

    createGraph();
    if (no_of_elements == 0)
        return 0;

    exitProgram = 0;
    while (exitProgram == 0)
    {
        printf("\n1. DFS\n");
        printf("2. BFS\n");
        printf("3. Create Edge\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Display Vertices\n");
        printf("7. Display Adjacency Matrix\n");
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
            exitProgram = 1;
        }
        else if (choice == 1 || choice == 2)
        {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter starting vertex: ");
                if (readVertex(&vertex) == 1)
                {
                    startIndex = getVertexIndex(vertex);
                    if (startIndex != -1)
                        valid = 1;
                }
                if (valid == 0)
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
            }

            if (valid == 0)
                printf("3 attempts completed. Traversal cancelled.\n");
            else
            {
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
            displayMatrix();
        else if (choice == 8)
        {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }
    return 0;
}