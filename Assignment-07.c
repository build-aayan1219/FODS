#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo {
    unsigned int rollno;
    char name[50];
    struct StudentInfo *left;
    struct StudentInfo *right;
};

struct StudentInfo *root = NULL;
struct StudentInfo *stack[50];
struct StudentInfo *queue[50];
int top = -1;
int front = 0;
int rear = 0;

void clearInput() {
    while (getchar() != '\n');
}

int stack_empty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

int queue_empty() {
    if (front == rear)
        return 1;
    else
        return 0;
}

void push(struct StudentInfo *node) {
    top++;
    stack[top] = node;
}

struct StudentInfo *pop() {
    struct StudentInfo *node;
    node = stack[top];
    top--;
    return node;
}

void enqueue(struct StudentInfo *node) {
    queue[rear] = node;
    rear++;
}

struct StudentInfo *dequeue() {
    struct StudentInfo *node;
    node = queue[front];
    front++;
    return node;
}

int validName(char name[]) {
    int i;
    if (name[0] == '\0')
        return 0;
    if (name[0] == ' ')
        return 0;
    for (i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
            return 0;
    }
    return 1;
}

int searchRoll(unsigned int rollno) {
    struct StudentInfo *temp;
    temp = root;
    while (temp != NULL) {
        if (rollno == temp->rollno)
            return 1;
        if (rollno < temp->rollno)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return 0;
}

void addNode(unsigned int rollno, char name[]) {
    struct StudentInfo *node;
    struct StudentInfo *temp;

    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));
    node->rollno = rollno;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;

    if (root == NULL)
        root = node;
    else {
        temp = root;
        while (1) {
            if (rollno < temp->rollno) {
                if (temp->left == NULL) {
                    temp->left = node;
                    break;
                }
                else
                    temp = temp->left;
            }
            else {
                if (temp->right == NULL) {
                    temp->right = node;
                    break;
                }
                else
                    temp = temp->right;
            }
        }
    }
}

void preorder(struct StudentInfo *node) {
    if (node == NULL)
        return;

    top = -1;
    push(node);

    while (!stack_empty()) {
        node = pop();
        printf("Roll No: %u  Name: %s\n", node->rollno, node->name);

        if (node->right != NULL)
            push(node->right);
        if (node->left != NULL)
            push(node->left);
    }
}

void inorder(struct StudentInfo *node) {
    top = -1;

    while (node != NULL || !stack_empty()) {
        while (node != NULL) {
            push(node);
            node = node->left;
        }

        node = pop();
        printf("Roll No: %u  Name: %s\n", node->rollno, node->name);
        node = node->right;
    }
}

void postorder(struct StudentInfo *node) {
    struct StudentInfo *previous;
    previous = NULL;
    top = -1;

    while (node != NULL || !stack_empty()) {
        while (node != NULL) {
            push(node);
            node = node->left;
        }

        node = pop();

        if (node->right != NULL && node->right != previous) {
            push(node);
            node = node->right;
        }
        else {
            printf("Roll No: %u  Name: %s\n", node->rollno, node->name);
            previous = node;
            node = NULL;
        }
    }
}

void bfs() {
    struct StudentInfo *node;

    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    front = 0;
    rear = 0;
    enqueue(root);

    while (!queue_empty()) {
        node = dequeue();
        printf("Roll No: %u  Name: %s\n", node->rollno, node->name);

        if (node->left != NULL)
            enqueue(node->left);
        if (node->right != NULL)
            enqueue(node->right);
    }
}

void dfs() {
    if (root == NULL)
        printf("Tree is empty\n");
    else
        preorder(root);
}

void update(unsigned int rollno, char name[]) {
    struct StudentInfo *searchNode;
    searchNode = root;

    while (searchNode != NULL && searchNode->rollno != rollno) {
        if (rollno < searchNode->rollno)
            searchNode = searchNode->left;
        else
            searchNode = searchNode->right;
    }

    if (searchNode == NULL)
        printf("Roll number not found\n");
    else {
        strcpy(searchNode->name, name);
        printf("Name updated successfully\n");
    }
}

void deleteNode(unsigned int rollno) {
    struct StudentInfo *parent;
    struct StudentInfo *searchNode;
    struct StudentInfo *dN;
    struct StudentInfo *delParent;
    struct StudentInfo *child;

    parent = NULL;
    searchNode = root;

    while (searchNode != NULL && searchNode->rollno != rollno) {
        parent = searchNode;

        if (rollno < searchNode->rollno)
            searchNode = searchNode->left;
        else
            searchNode = searchNode->right;
    }

    if (searchNode == NULL) {
        printf("Roll number not found\n");
        return;
    }

    if (searchNode->left == NULL && searchNode->right == NULL) {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == searchNode)
            parent->left = NULL;
        else
            parent->right = NULL;

        free(searchNode);
        printf("Student deleted successfully\n");
    }
    else if (searchNode->left == NULL || searchNode->right == NULL) {
        if (searchNode->left != NULL)
            child = searchNode->left;
        else
            child = searchNode->right;

        if (parent == NULL)
            root = child;
        else if (parent->left == searchNode)
            parent->left = child;
        else
            parent->right = child;

        free(searchNode);
        printf("Student deleted successfully\n");
    }
    else {
        dN = searchNode->left;
        delParent = searchNode;

        while (dN->right != NULL) {
            delParent = dN;
            dN = dN->right;
        }

        searchNode->rollno = dN->rollno;
        strcpy(searchNode->name, dN->name);

        if (delParent->left == dN)
            delParent->left = dN->left;
        else
            delParent->right = dN->left;

        free(dN);
        printf("Student deleted successfully\n");
    }
}

int main() {
    int n, choice, i, attempts, valid, exitProgram;
    int inputRoll;
    unsigned int rollno;
    char name[50], extra;

    valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
        printf("Enter number of students: ");

        if (scanf("%d%c", &n, &extra) == 2 && extra == '\n' && n > 0 && n <= 10)
            valid = 1;
        else {
            if (extra != '\n')
                clearInput();
            printf("Invalid input! Attempt %d of 3\n", attempts);
        }
    }

    if (valid == 0) {
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }

    i = 0;

    while (i < n) {
        printf("\nEnter details of student %d\n", i + 1);

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter roll number: ");

            if (scanf("%d%c", &inputRoll, &extra) == 2 && extra == '\n' && inputRoll > 0) {
                rollno = (unsigned int)inputRoll;

                if (searchRoll(rollno) == 1)
                    printf("Roll number already exists. Enter another roll number.\n");
                else
                    valid = 1;
            }
            else {
                if (extra != '\n')
                    clearInput();
                printf("Invalid roll number! Attempt %d of 3\n", attempts);
            }
        }

        if (valid == 0) {
            printf("3 attempts completed. Please enter Student %d again.\n", i + 1);
            continue;
        }

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter name: ");

            if (scanf(" %49[^\n]", name) == 1) {
                extra = getchar();

                if (extra == '\n' && validName(name))
                    valid = 1;
                else {
                    if (extra != '\n')
                        clearInput();
                    printf("Invalid name! Attempt %d of 3\n", attempts);
                }
            }
            else {
                clearInput();
                printf("Invalid name! Attempt %d of 3\n", attempts);
            }
        }

        if (valid == 0)
            printf("3 attempts completed. Please enter Student %d again.\n", i + 1);
        else {
            addNode(rollno, name);
            printf("Student created successfully\n");
            i++;
        }
    }

    exitProgram = 0;

    while (exitProgram == 0) {
        printf("\n1. Preorder\n");
        printf("2. Inorder\n");
        printf("3. Postorder\n");
        printf("4. BFS\n");
        printf("5. DFS\n");
        printf("6. Create\n");
        printf("7. Update\n");
        printf("8. Delete\n");
        printf("9. Exit\n");

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter your choice: ");

            if (scanf("%d%c", &choice, &extra) == 2 && extra == '\n' && choice >= 1 && choice <= 9)
                valid = 1;
            else {
                if (extra != '\n')
                    clearInput();
                printf("Invalid choice! Attempt %d of 3\n", attempts);
            }
        }

        if (valid == 0) {
            printf("3 attempts completed. Program ended.\n");
            exitProgram = 1;
        }
        else if (choice == 1) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPreorder Traversal:\n");
                preorder(root);
            }
        }
        else if (choice == 2) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nInorder Traversal:\n");
                inorder(root);
            }
        }
        else if (choice == 3) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPostorder Traversal:\n");
                postorder(root);
            }
        }
        else if (choice == 4) {
            printf("\nBreadth First Traversal:\n");
            bfs();
        }
        else if (choice == 5) {
            printf("\nDepth First Traversal:\n");
            dfs();
        }
        else if (choice == 6) {
            valid = 0;

            for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                printf("Enter roll number: ");

                if (scanf("%d%c", &inputRoll, &extra) == 2 && extra == '\n' && inputRoll > 0) {
                    rollno = (unsigned int)inputRoll;

                    if (searchRoll(rollno) == 1)
                        printf("Roll number already exists. Enter another roll number.\n");
                    else
                        valid = 1;
                }
                else {
                    if (extra != '\n')
                        clearInput();
                    printf("Invalid roll number! Attempt %d of 3\n", attempts);
                }
            }

            if (valid == 0)
                printf("3 attempts completed. Create cancelled.\n");
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter name: ");

                    if (scanf(" %49[^\n]", name) == 1) {
                        extra = getchar();

                        if (extra == '\n' && validName(name))
                            valid = 1;
                        else {
                            if (extra != '\n')
                                clearInput();
                            printf("Invalid name! Attempt %d of 3\n", attempts);
                        }
                    }
                    else {
                        clearInput();
                        printf("Invalid name! Attempt %d of 3\n", attempts);
                    }
                }

                if (valid == 0)
                    printf("3 attempts completed. Create cancelled.\n");
                else {
                    addNode(rollno, name);
                    printf("Student created successfully\n");
                }
            }
        }
        else if (choice == 7) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to update: ");

                    if (scanf("%d%c", &inputRoll, &extra) == 2 && extra == '\n' && inputRoll > 0) {
                        rollno = (unsigned int)inputRoll;
                        valid = 1;
                    }
                    else {
                        if (extra != '\n')
                            clearInput();
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                }

                if (valid == 0)
                    printf("3 attempts completed. Update cancelled.\n");
                else if (searchRoll(rollno) == 0)
                    printf("Roll number not found\n");
                else {
                    valid = 0;

                    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                        printf("Enter new name: ");

                        if (scanf(" %49[^\n]", name) == 1) {
                            extra = getchar();

                            if (extra == '\n' && validName(name))
                                valid = 1;
                            else {
                                if (extra != '\n')
                                    clearInput();
                                printf("Invalid name! Attempt %d of 3\n", attempts);
                            }
                        }
                        else {
                            clearInput();
                            printf("Invalid name! Attempt %d of 3\n", attempts);
                        }
                    }

                    if (valid == 0)
                        printf("3 attempts completed. Update cancelled.\n");
                    else
                        update(rollno, name);
                }
            }
        }
        else if (choice == 8) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to delete: ");

                    if (scanf("%d%c", &inputRoll, &extra) == 2 && extra == '\n' && inputRoll > 0) {
                        rollno = (unsigned int)inputRoll;
                        valid = 1;
                    }
                    else {
                        if (extra != '\n')
                            clearInput();
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                }

                if (valid == 0)
                    printf("3 attempts completed. Delete cancelled.\n");
                else
                    deleteNode(rollno);
            }
        }
        else if (choice == 9) {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }

    return 0;
}