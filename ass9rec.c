#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo {
    int rollno;
    char name[50];
    int height;
    struct StudentInfo *left;
    struct StudentInfo *right;
};

struct StudentInfo *root = NULL;

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validName(char name[]) {
    int i;
    if (name[0] == '\0')
        return 0;
    for (i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
            return 0;
    }
    return 1;
}

int readInteger(int *value) {
    int c;
    if (scanf("%d", value) != 1) {
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

int readName(char name[]) {
    int c;
    if (scanf("%49[^\n]", name) != 1) {
        clearInput();
        return 0;
    }
    c = getchar();
    if (c == '\n' && validName(name))
        return 1;
    while (c != '\n' && c != EOF)
        c = getchar();
    return 0;
}

int height(struct StudentInfo *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int balanceFactor(struct StudentInfo *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct StudentInfo *createNode(int rollno, char name[]) {
    struct StudentInfo *node;
    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    node->rollno = rollno;
    strcpy(node->name, name);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct StudentInfo *rightRotate(struct StudentInfo *node) {
    struct StudentInfo *leftNode;
    struct StudentInfo *temp;

    leftNode = node->left;
    temp = leftNode->right;

    leftNode->right = node;
    node->left = temp;

    node->height = 1 + max(height(node->left), height(node->right));
    leftNode->height = 1 + max(height(leftNode->left), height(leftNode->right));

    return leftNode;
}

struct StudentInfo *leftRotate(struct StudentInfo *node) {
    struct StudentInfo *rightNode;
    struct StudentInfo *temp;

    rightNode = node->right;
    temp = rightNode->left;

    rightNode->left = node;
    node->right = temp;

    node->height = 1 + max(height(node->left), height(node->right));
    rightNode->height = 1 + max(height(rightNode->left), height(rightNode->right));

    return rightNode;
}

struct StudentInfo *insertNode(struct StudentInfo *node, int rollno, char name[]) {
    int balance;

    if (node == NULL)
        return createNode(rollno, name);

    if (rollno < node->rollno)
        node->left = insertNode(node->left, rollno, name);
    else if (rollno > node->rollno)
        node->right = insertNode(node->right, rollno, name);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    balance = balanceFactor(node);

    if (balance > 1 && rollno < node->left->rollno)
        return rightRotate(node);

    if (balance < -1 && rollno > node->right->rollno)
        return leftRotate(node);

    if (balance > 1 && rollno > node->left->rollno) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && rollno < node->right->rollno) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct StudentInfo *searchNode(struct StudentInfo *node, int rollno) {
    if (node == NULL)
        return NULL;

    if (rollno == node->rollno)
        return node;

    if (rollno < node->rollno)
        return searchNode(node->left, rollno);

    return searchNode(node->right, rollno);
}

struct StudentInfo *minimumNode(struct StudentInfo *node) {
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
        return node;

    return minimumNode(node->left);
}

struct StudentInfo *deleteNode(struct StudentInfo *node, int rollno) {
    struct StudentInfo *temp;
    int balance;

    if (node == NULL)
        return NULL;

    if (rollno < node->rollno)
        node->left = deleteNode(node->left, rollno);
    else if (rollno > node->rollno)
        node->right = deleteNode(node->right, rollno);
    else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }

        if (node->left == NULL) {
            temp = node->right;
            free(node);
            return temp;
        }

        if (node->right == NULL) {
            temp = node->left;
            free(node);
            return temp;
        }

        temp = minimumNode(node->right);
        node->rollno = temp->rollno;
        strcpy(node->name, temp->name);
        node->right = deleteNode(node->right, temp->rollno);
    }

    node->height = 1 + max(height(node->left), height(node->right));
    balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(struct StudentInfo *node) {
    if (node != NULL) {
        inorder(node->left);
        printf("Roll No: %d  Name: %s\n", node->rollno, node->name);
        inorder(node->right);
    }
}

void preorder(struct StudentInfo *node) {
    if (node != NULL) {
        printf("Roll No: %d  Name: %s\n", node->rollno, node->name);
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(struct StudentInfo *node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("Roll No: %d  Name: %s\n", node->rollno, node->name);
    }
}

void breadthFirst() {
    struct StudentInfo *queue[100];
    struct StudentInfo *temp;
    int front = 0;
    int rear = 0;

    if (root == NULL)
        return;

    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }
}

void depthFirst() {
    struct StudentInfo *stack[100];
    struct StudentInfo *temp;
    int top = -1;

    if (root == NULL)
        return;

    stack[++top] = root;

    while (top >= 0) {
        temp = stack[top--];

        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);

        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

void updateStudent(int rollno, char name[]) {
    struct StudentInfo *node;

    node = searchNode(root, rollno);

    if (node == NULL)
        printf("Roll number not found\n");
    else {
        strcpy(node->name, name);
        printf("Name updated successfully\n");
    }
}

int main() {
    int n, choice, i, attempts, valid, exitProgram, duplicate;
    int rollno;
    char name[50];

    valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
        printf("Enter number of students: ");

        if (readInteger(&n) == 1 && n > 0 && n <= 10)
            valid = 1;
        else
            printf("Invalid input! Attempt %d of 3\n", attempts);
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

            if (readInteger(&rollno) == 1 && rollno > 0)
                valid = 1;
            else
                printf("Invalid roll number! Attempt %d of 3\n", attempts);
        }

        if (valid == 0) {
            printf("3 attempts completed. Please enter Student %d again.\n", i + 1);
        } else {
            duplicate = 0;

            if (searchNode(root, rollno) != NULL)
                duplicate = 1;

            if (duplicate == 1) {
                printf("Roll number already exists. Student not created.\n");
            } else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter name: ");

                    if (readName(name) == 1)
                        valid = 1;
                    else
                        printf("Invalid name! Attempt %d of 3\n", attempts);
                }

                if (valid == 0) {
                    printf("3 attempts completed. Please enter Student %d again.\n", i + 1);
                } else {
                    root = insertNode(root, rollno, name);
                    printf("Student created successfully\n");
                    i++;
                }
            }
        }
    }

    exitProgram = 0;

    while (exitProgram == 0) {
        printf("\n1. Create\n");
        printf("2. Inorder\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. BFS\n");
        printf("6. DFS\n");
        printf("7. Update\n");
        printf("8. Delete\n");
        printf("9. Exit\n");

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter your choice: ");

            if (readInteger(&choice) == 1 && choice >= 1 && choice <= 9)
                valid = 1;
            else
                printf("Invalid input! Attempt %d of 3\n", attempts);
        }

        if (valid == 0) {
            printf("3 attempts completed. Program ended.\n");
            exitProgram = 1;
        } else if (choice == 1) {
            valid = 0;

            for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                printf("Enter roll number: ");

                if (readInteger(&rollno) == 1 && rollno > 0)
                    valid = 1;
                else
                    printf("Invalid roll number! Attempt %d of 3\n", attempts);
            }

            if (valid == 0) {
                printf("3 attempts completed. Create cancelled.\n");
            } else if (searchNode(root, rollno) != NULL) {
                printf("Roll number already exists. Student not created.\n");
            } else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter name: ");

                    if (readName(name) == 1)
                        valid = 1;
                    else
                        printf("Invalid name! Attempt %d of 3\n", attempts);
                }

                if (valid == 0)
                    printf("3 attempts completed. Create cancelled.\n");
                else {
                    root = insertNode(root, rollno, name);
                    printf("Student created successfully\n");
                }
            }
        } else if (choice == 2) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nInorder Traversal:\n");
                inorder(root);
            }
        } else if (choice == 3) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPreorder Traversal:\n");
                preorder(root);
            }
        } else if (choice == 4) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPostorder Traversal:\n");
                postorder(root);
            }
        } else if (choice == 5) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nBreadth First Traversal:\n");
                breadthFirst();
            }
        } else if (choice == 6) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nDepth First Traversal:\n");
                depthFirst();
            }
        } else if (choice == 7) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to update: ");

                    if (readInteger(&rollno) == 1 && rollno > 0)
                        valid = 1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                }

                if (valid == 0) {
                    printf("3 attempts completed. Update cancelled.\n");
                } else if (searchNode(root, rollno) == NULL) {
                    printf("Roll number not found\n");
                } else {
                    valid = 0;

                    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                        printf("Enter new name: ");

                        if (readName(name) == 1)
                            valid = 1;
                        else
                            printf("Invalid name! Attempt %d of 3\n", attempts);
                    }

                    if (valid == 0)
                        printf("3 attempts completed. Update cancelled.\n");
                    else
                        updateStudent(rollno, name);
                }
            }
        } else if (choice == 8) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to delete: ");

                    if (readInteger(&rollno) == 1 && rollno > 0)
                        valid = 1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                }

                if (valid == 0) {
                    printf("3 attempts completed. Delete cancelled.\n");
                } else if (searchNode(root, rollno) == NULL) {
                    printf("Roll number not found\n");
                } else {
                    root = deleteNode(root, rollno);
                    printf("Student deleted successfully\n");
                }
            }
        } else if (choice == 9) {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }

    return 0;
}