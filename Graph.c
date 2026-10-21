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
    if (c == '\n')
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
    for (i = 0; i < NO_OF_ELEMENTS; i++)
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

void createEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex (A-E): ");
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
        printf("3 attempts completed. Create edge cancelled.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter second vertex (A-E): ");
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
        printf("3 attempts completed. Create edge cancelled.\n");
        return;
    }

    if (firstIndex == secondIndex)
        printf("Cannnot Connect Link to itself.\n");
    else if (vertices_matrix[firstIndex][secondIndex] == 1)
        printf("Edge already exists.\n");
    else                                                                        //here I created a new link...!!
    {
        vertices_matrix[firstIndex][secondIndex] = 1;
        vertices_matrix[secondIndex][firstIndex] = 1;
        printf("Edge created successfully\n");
    }
}

void updateEdge()
{
    char firstVertex, oldVertex, newVertex;
    int firstIndex, oldIndex, newIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex of existing edge (A-E): ");
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
        printf("Enter second vertex of existing edge (A-E): ");
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
        printf("Enter new second vertex (A-E): ");
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
        printf("Cannot Update a connection with itself..\n");
    else if (vertices_matrix[firstIndex][newIndex] == 1)
        printf("The new edge already exists.\n");
    else
    {
        vertices_matrix[firstIndex][oldIndex] = 0;
        vertices_matrix[oldIndex][firstIndex] = 0;
        vertices_matrix[firstIndex][newIndex] = 1;
        vertices_matrix[newIndex][firstIndex] = 1;
        printf("Edge updated successfully\n");
    }
}

void deleteEdge()
{
    char firstVertex, secondVertex;
    int firstIndex, secondIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter first vertex (A-E): ");
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
        printf("Enter second vertex (A-E): ");
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
        printf("Cannoct connect a link with itself.\n");
    else if (vertices_matrix[firstIndex][secondIndex] == 0)
        printf("Edge not found\n");
    else
    {
        vertices_matrix[firstIndex][secondIndex] = 0;
        vertices_matrix[secondIndex][firstIndex] = 0;
        printf("Edge deleted successfully\n");
    }
}

void displayMatrix()
{
    int i, j;
    printf("  ");
    for (i = 0; i < NO_OF_ELEMENTS; i++)
        printf("%c ", vertex_name[i]);
    printf("\n");

    for (i = 0; i < NO_OF_ELEMENTS; i++)
    {
        printf("%c ", vertex_name[i]);
        for (j = 0; j < NO_OF_ELEMENTS; j++)
            printf("%d ", vertices_matrix[i][j]);
        printf("\n");
    }
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
    int startIndex, choice, i, attempts, valid, exitProgram;

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
                printf("Enter starting vertex (A-E): ");
                if (scanf(" %c", &vertex) == 1)
                {
                    clearInput();
                    startIndex = getVertexIndex(vertex);
                    if (startIndex != -1)
                        valid = 1;
                }
                else
                    clearInput();

                if (valid == 0)
                    printf("Invalid vertex! Attempt %d of 3\n", attempts);
            }

            if (valid == 0)
                printf("3 attempts completed. Traversal cancelled.\n");
            else
            {
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
