
#include <stdio.h>

#define MAX_VERTICES 100

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

int hasLinks()
{
    int i, j;
    for (i = 0; i < no_of_elements; i++)
    {
        for (j = 0; j < no_of_elements; j++)
        {
            if (vertices_matrix[i][j] == 1)
                return 1;
        }
    }
    return 0;
}

int isConnected()
{
    int i, current, next, tempTop = -1, count = 0;
    int tempVisited[MAX_VERTICES] = {0};
    int tempStack[MAX_VERTICES];

    if (no_of_elements == 0)
        return 0;

    tempStack[++tempTop] = 0;
    tempVisited[0] = 1;

    while (tempTop != -1)
    {
        current = tempStack[tempTop--];
        count++;

        for (i = 0; i < no_of_elements; i++)
        {
            next = i;
            if (vertices_matrix[current][next] == 1 && tempVisited[next] == 0)
            {
                tempVisited[next] = 1;
                tempStack[++tempTop] = next;
            }
        }
    }
    if (count == no_of_elements)
        return 1;

    return 0;
}

void push(int vertex)
{
    if (top < MAX_VERTICES - 1)
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
    if (rear < MAX_VERTICES - 1)
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

int createGraph()
{
    int i, j, count, valid, attempts, connectedIndex;
    char vertex;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter total number of vertices (1-%d): ", MAX_VERTICES);
        if (readInteger(&no_of_elements) == 1 && no_of_elements >= 1 && no_of_elements <= MAX_VERTICES)
            valid = 1;
        else
            printf("Invalid input! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Program ended.\n");
        return 0;
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
            printf("Enter vertex %d name: ", i + 1);
            if (readVertex(&vertex) == 1)
            {
                valid = 1;
                for (j = 0; j < i; j++)
                {
                    if (vertex_name[j] == vertex)
                        valid = 0;
                }
                if (valid == 1)
                    vertex_name[i] = vertex;
            }

            if (valid == 0)
                printf("Invalid or duplicate vertex! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Program ended.\n");
            no_of_elements = 0;
            return 0;
        }
    }

    for (i = 0; i < no_of_elements; i++)
    {
        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("How many links does %c have? ", vertex_name[i]);
            if (readInteger(&count) == 1 && count >= 0 && count < no_of_elements)
                valid = 1;
            else
                printf("Invalid link count! Attempt %d of 3\n", attempts);
        }

        if (valid == 0)
        {
            printf("3 attempts completed. Program ended.\n");
            no_of_elements = 0;
            return 0;
        }

        for (j = 0; j < count; j++)
        {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
            {
                printf("Enter connected vertex for %c: ", vertex_name[i]);
                if (readVertex(&vertex) == 1)
                {
                    connectedIndex = getVertexIndex(vertex);
                    if (connectedIndex != -1 && connectedIndex != i)
                        valid = 1;
                }

                if (valid == 0)
                    printf("Invalid vertex or self-connection! Attempt %d of 3\n", attempts);
            }

            if (valid == 0)
                printf("3 attempts completed. Link input skipped.\n");
            else if (vertices_matrix[i][connectedIndex] == 1)
                printf("Edge already exists.\n");
            else
            {
                vertices_matrix[i][connectedIndex] = 1;
                vertices_matrix[connectedIndex][i] = 1;
            }
        }
    }

    printf("Graph created successfully.\n");
    if (!hasLinks())
        printf("There is no graph as there are no links.\n");

    return 1;
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
    int firstIndex, secondIndex, valid, attempts, count, i;

    if (no_of_elements < 2)
    {
        printf("At least two vertices are required to create an edge.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter starting vertex: ");
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
        printf("How many edges do you want to create from %c? ", firstVertex);
        if (readInteger(&count) == 1 && count >= 0 && count < no_of_elements)
            valid = 1;
        else
            printf("Invalid edge count! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Create edge cancelled.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
        {
            printf("Enter connected vertex %d for %c: ", i + 1, firstVertex);
            if (readVertex(&secondVertex) == 1)
            {
                secondIndex = getVertexIndex(secondVertex);
                if (secondIndex != -1 && secondIndex != firstIndex && vertices_matrix[firstIndex][secondIndex] == 0)
                    valid = 1;
            }
            if (valid == 0)
                printf("Invalid vertex, self-connection, or edge already exists! Attempt %d of 3\n", attempts);
        }

        if (valid == 1)
        {
            vertices_matrix[firstIndex][secondIndex] = 1;
            vertices_matrix[secondIndex][firstIndex] = 1;
            printf("Edge %c-%c created successfully.\n", firstVertex, secondVertex);
        }
        else
            printf("3 attempts completed. This edge was skipped.\n");
    }

    if (count == 0)
        printf("No edges were created.\n");
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
        if (!hasLinks())
            printf("There is no graph as there are no links.\n");
    }
}

void addVertex()
{
    char vertex;
    int valid, attempts, i;

    if (no_of_elements >= MAX_VERTICES)
    {
        printf("Maximum vertex limit reached.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter new vertex name: ");
        if (readVertex(&vertex) == 1 && getVertexIndex(vertex) == -1)
            valid = 1;
        else
            printf("Invalid or duplicate vertex! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Add vertex cancelled.\n");
        return;
    }

    vertex_name[no_of_elements] = vertex;
    for (i = 0; i <= no_of_elements; i++)
    {
        vertices_matrix[no_of_elements][i] = 0;
        vertices_matrix[i][no_of_elements] = 0;
    }

    no_of_elements++;
    printf("Vertex added successfully.\n");
}

void updateVertex()
{
    char oldVertex, newVertex;
    int oldIndex, valid, attempts;

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter existing vertex name: ");
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
        printf("3 attempts completed. Update vertex cancelled.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter new vertex name: ");
        if (readVertex(&newVertex) == 1 && (getVertexIndex(newVertex) == -1 || newVertex == oldVertex))
            valid = 1;
        else
            printf("Invalid or duplicate vertex! Attempt %d of 3\n", attempts);
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
    int index, valid, attempts, i, j, sourceRow, sourceColumn;
    int temp[MAX_VERTICES][MAX_VERTICES];

    if (no_of_elements == 0)
    {
        printf("There are no vertices to delete.\n");
        return;
    }

    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++)
    {
        printf("Enter vertex to delete: ");
        if (readVertex(&vertex) == 1)
        {
            index = getVertexIndex(vertex);
            if (index != -1)
                valid = 1;
        }

        if (valid == 0)
            printf("Invalid vertex! Attempt %d of 3\n", attempts);
    }

    if (valid == 0)
    {
        printf("3 attempts completed. Delete vertex cancelled.\n");
        return;
    }

    for (i = 0; i < no_of_elements - 1; i++)
    {
        sourceRow = i;
        if (sourceRow >= index)
            sourceRow++;

        for (j = 0; j < no_of_elements - 1; j++)
        {
            sourceColumn = j;
            if (sourceColumn >= index)
                sourceColumn++;

            temp[i][j] = vertices_matrix[sourceRow][sourceColumn];
        }
    }

    for (i = index; i < no_of_elements - 1; i++)
        vertex_name[i] = vertex_name[i + 1];

    no_of_elements--;

    for (i = 0; i < no_of_elements; i++)
    {
        for (j = 0; j < no_of_elements; j++)
            vertices_matrix[i][j] = temp[i][j];
    }

    for (i = 0; i < MAX_VERTICES; i++)
    {
        vertices_matrix[no_of_elements][i] = 0;
        vertices_matrix[i][no_of_elements] = 0;
    }

    printf("Vertex deleted successfully.\n");
    if (!hasLinks())
        printf("There is no graph as there are no links.\n");
}

void displayMatrix()
{
    int i, j;

    if (!hasLinks())
    {
        printf("There is no graph as there are no links.\n");
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
        printf("There are no vertices.\n");
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

    if (createGraph() == 0)
        return 0;

    exitProgram = 0;
    while (exitProgram == 0)
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
        printf("10. Display Adjacency Matrix\n");
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
            exitProgram = 1;
        }
        else if (choice == 1 || choice == 2)
        {
            if (!hasLinks())
                printf("There is no graph as there are no links.\n");
            else if (!isConnected())
                printf("All vertices are not connected. Connect them.\n");
            else if (no_of_elements == 0)
                printf("There are no vertices.\n");
            else
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
            displayMatrix();
        else if (choice == 11)
        {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }

    return 0;
}
