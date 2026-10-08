#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct StudentInfo {
    unsigned int rollno;
    char name[50];
    struct StudentInfo *left;
    struct StudentInfo *right;
    int rightThread;
};
struct StudentInfo *root = NULL;
struct StackNode {
    struct StudentInfo *student;
    struct StackNode *next;
};
struct QueueNode {
    struct StudentInfo *student;
    struct QueueNode *next;
};
struct StackNode *top = NULL;
struct QueueNode *front = NULL;
struct QueueNode *rear = NULL;
void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
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
int readName(char name[]) {
    int i = 0;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (i < 49) {
            name[i] = ch;
            i++;
        }
        else {
            clearInput();
            return 0;
        }
    }
    name[i] = '\0';
    return validName(name);
}
struct StudentInfo *searchNode(unsigned int rollno) {
    struct StudentInfo *temp = root;
    while (temp != NULL) {
        if (rollno == temp->rollno)
            return temp;
        if (rollno < temp->rollno)
            temp = temp->left;
        else {
            if (temp->rightThread == 1)
                temp = NULL;
            else
                temp = temp->right;
        }
    }
    return NULL;
}
void addNode(unsigned int rollno, char name[]) {
    struct StudentInfo *node;
    struct StudentInfo *temp;
    struct StudentInfo *parent;
    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    node->rollno = rollno;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->rightThread = 0;
    if (root == NULL) {
        root = node;
        return;
    }
    temp = root;
    parent = NULL;
    while (temp != NULL) {
        parent = temp;
        if (rollno < temp->rollno)
            temp = temp->left;
        else {
            if (temp->rightThread == 1)
                temp = NULL;
            else
                temp = temp->right; 
        }
    }
    if (rollno < parent->rollno) {
        node->right = parent;
        node->rightThread = 1;
        parent->left = node;
    }
    else {
        node->right = parent->right;
        node->rightThread = parent->rightThread;
        parent->right = node;
        parent->rightThread = 0;
    }
}
struct StudentInfo *leftMost(struct StudentInfo *node) {
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}
struct StudentInfo *inorderSuccessor(struct StudentInfo *node) {
    if (node == NULL)
        return NULL;
    if (node->rightThread == 1)
        return node->right;
    else
        return leftMost(node->right);
}
void push(struct StudentInfo *student) {
    struct StackNode *newNode;
    newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (newNode == NULL)
        return;
    newNode->student = student;
    newNode->next = top;
    top = newNode;
}
struct StudentInfo *pop() {
    struct StackNode *temp;
    struct StudentInfo *student;
    if (top == NULL)
        return NULL;
    temp = top;
    student = temp->student;
    top = top->next;
    free(temp);
    return student;
}
void enqueue(struct StudentInfo *student) {
    struct QueueNode *newNode;
    newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    if (newNode == NULL)
        return;
    newNode->student = student;
    newNode->next = NULL;
    if (rear == NULL) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}
struct StudentInfo *dequeue() {
    struct QueueNode *temp;
    struct StudentInfo *student;
    if (front == NULL)
        return NULL;
    temp = front;
    student = temp->student;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    free(temp);
    return student;
}
void clearStack() {
    while (top != NULL)
        pop();
}
void clearQueue() {
    while (front != NULL)
        dequeue();
}
void inorder(struct StudentInfo *node) {
    struct StudentInfo *temp;
    clearStack();
    temp = node;
    while (temp != NULL || top != NULL) {
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }
        temp = pop();
        printf("Roll No: %u  Name: %s\n", temp->rollno, temp->name);
        if (temp->rightThread == 1)
            temp = NULL;
        else
            temp = temp->right;
    }
}
void preorder(struct StudentInfo *node) {
    struct StudentInfo *temp;
    clearStack();
    if (node == NULL)
        return;
    push(node);
    while (top != NULL) {
        temp = pop();
        printf("Roll No: %u  Name: %s\n", temp->rollno, temp->name);
        if (temp->rightThread == 0 && temp->right != NULL)
            push(temp->right);
        if (temp->left != NULL)
            push(temp->left);
    }
}
void postorder(struct StudentInfo *node) {
    struct StudentInfo *temp;
    struct StackNode *secondTop = NULL;
    struct StackNode *newNode;
    clearStack();
    if (node == NULL)
        return;
    push(node);
    while (top != NULL) {
        temp = pop();
        newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
        if (newNode == NULL)
            return;
        newNode->student = temp;
        newNode->next = secondTop;
        secondTop = newNode;
        if (temp->left != NULL)
            push(temp->left);
        if (temp->rightThread == 0 && temp->right != NULL)
            push(temp->right);
    }
    while (secondTop != NULL) {
        temp = secondTop->student;
        newNode = secondTop;
        secondTop = secondTop->next;
        free(newNode);
        printf("Roll No: %u  Name: %s\n", temp->rollno, temp->name);
    }
}
void dfs(struct StudentInfo *node) {
    struct StudentInfo *temp;
    clearStack();
    if (node == NULL)
        return;
    push(node);
    while (top != NULL) {
        temp = pop();
        printf("Roll No: %u  Name: %s\n", temp->rollno, temp->name);
        if (temp->rightThread == 0 && temp->right != NULL)
            push(temp->right);
        if (temp->left != NULL)
            push(temp->left);
    }
}
void bfs() {
    struct StudentInfo *temp;
    clearQueue();
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    enqueue(root);
    while (front != NULL) {
        temp = dequeue();
        printf("Roll No: %u  Name: %s\n", temp->rollno, temp->name);
        if (temp->left != NULL)
            enqueue(temp->left);
        if (temp->rightThread == 0 && temp->right != NULL)
            enqueue(temp->right);
    }
}
void updateStudent(unsigned int rollno, char name[]) {
    struct StudentInfo *node;
    node = searchNode(rollno);
    if (node == NULL)
        printf("Roll number not found\n");
    else {
        strcpy(node->name, name);
        printf("Name updated successfully\n");
    }
}
void deleteNode(unsigned int rollno) {
    struct StudentInfo *parent = NULL;
    struct StudentInfo *node = root;
    struct StudentInfo *successor;
    struct StudentInfo *successorParent;
    struct StudentInfo *child;
    while (node != NULL && node->rollno != rollno) {
        parent = node;
        if (rollno < node->rollno)
            node = node->left;
        else {
            if (node->rightThread == 1)
                node = NULL;
            else
                node = node->right;
        }
    }
    if (node == NULL) {
        printf("Roll number not found\n");
        return;
    }
    if (node->left != NULL && node->rightThread == 0 && node->right != NULL) {
        successorParent = node;
        successor = node->right;
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }
        node->rollno = successor->rollno;
        strcpy(node->name, successor->name);
        parent = successorParent;
        node = successor;
    }
    child = NULL;
    if (node->left != NULL)
        child = node->left;
    else if (node->rightThread == 0 && node->right != NULL)
        child = node->right;
    if (child != NULL) {
        if (parent == NULL)
            root = child;
        else if (parent->left == node)
            parent->left = child;
        else {
            parent->right = child;
            parent->rightThread = 0;
        }
        if (node->rightThread == 1) {
            struct StudentInfo *temp = child;
            while (temp->rightThread == 0 && temp->right != NULL)
                temp = temp->right;
            temp->right = node->right;
            temp->rightThread = 1;
        }
        free(node);
    }
    else {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == node)
            parent->left = NULL;
        else {
            parent->right = node->right;
            parent->rightThread = 1;
        }
        free(node);
    }
    printf("Student deleted successfully\n");
}
int main() {
    int n;
    int i;
    int choice;
    int attempts;
    int valid;
    int inputRollno;
    char name[50];
    valid = 0;
    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
        printf("Enter number of students: ");
        if (scanf("%d", &n) == 1) {
            if (getchar() == '\n') {
                if (n > 0 && n <= 100)
                    valid = 1;
                else
                    printf("Invalid input! Attempt %d of 3\n", attempts);
            }
            else {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        else {
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
            if (scanf("%d", &inputRollno) == 1) {
                if (getchar() == '\n') {
                    if (inputRollno > 0 && searchNode((unsigned int)inputRollno) == NULL) {
                        valid = 1;
                    }
                    else if (inputRollno <= 0) {
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                    else {
                        printf("Roll number already exists! Attempt %d of 3\n", attempts);
                    }
                }
                else {
                    clearInput();
                    printf("Invalid roll number! Attempt %d of 3\n", attempts);
                }
            }
            else {
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
            if (readName(name))
                valid = 1;
            else
                printf("Invalid name! Attempt %d of 3\n", attempts);
        }
        if (valid == 0) {
            printf("3 attempts completed. Please enter Student %d again.\n", i + 1);
            continue;
        }
        addNode((unsigned int)inputRollno, name);
        printf("Student created successfully\n");
        i++;
    }
    while (1) {
        printf("\n1. Create\n");
        printf("2. Inorder\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. DFS\n");
        printf("6. BFS\n");
        printf("7. Update\n");
        printf("8. Delete\n");
        printf("9. Exit\n");
        valid = 0;
        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter your choice: ");
            if (scanf("%d", &choice) == 1) {
                if (getchar() == '\n') {
                    if (choice >= 1 && choice <= 9)
                        valid = 1;
                    else
                        printf("Invalid input! Attempt %d of 3\n", attempts);
                }
                else {
                    clearInput();
                    printf("Invalid input! Attempt %d of 3\n", attempts);
                }
            }
            else {
                clearInput();
                printf("Invalid input! Attempt %d of 3\n", attempts);
            }
        }
        if (valid == 0) {
            printf("3 attempts completed. Program ended.\n");
            break;
        }
        if (choice == 1) {
            valid = 0;
            for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                printf("Enter roll number: ");
                if (scanf("%d", &inputRollno) == 1) {
                    if (getchar() == '\n') {
                        if (inputRollno > 0 && searchNode((unsigned int)inputRollno) == NULL)
                            valid = 1;
                        else if (inputRollno <= 0)
                            printf("Invalid roll number! Attempt %d of 3\n", attempts);
                        else
                            printf("Roll number already exists! Attempt %d of 3\n", attempts);
                    }
                    else {
                        clearInput();
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                }
                else {
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
                    if (readName(name))
                        valid = 1;
                    else
                        printf("Invalid name! Attempt %d of 3\n", attempts);
                }
                if (valid == 0)
                    printf("3 attempts completed. Create cancelled.\n");
                else {
                    addNode((unsigned int)inputRollno, name);
                    printf("Student created successfully\n");
                }
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
                printf("\nPreorder Traversal:\n");
                preorder(root);
            }
        }
        else if (choice == 4) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPostorder Traversal:\n");
                postorder(root);
            }
        }
        else if (choice == 5) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nDepth First Traversal:\n");
                dfs(root);
            }
        }
        else if (choice == 6) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nBreadth First Traversal:\n");
                bfs();
            }
        }
        else if (choice == 7) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                valid = 0;
                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to update: ");
                    if (scanf("%d", &inputRollno) == 1) {
                        if (getchar() == '\n') {
                            if (inputRollno > 0)
                                valid = 1;
                            else
                                printf("Invalid roll number! Attempt %d of 3\n", attempts);
                        }
                        else {
                            clearInput();
                            printf("Invalid roll number! Attempt %d of 3\n", attempts);
                        }
                    }
                    else {
                        clearInput();
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                }
                if (valid == 0)
                    printf("3 attempts completed. Update cancelled.\n");
                else if (searchNode((unsigned int)inputRollno) == NULL)
                    printf("Roll number not found\n");
                else {
                    valid = 0;
                    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                        printf("Enter new name: ");
                        if (readName(name))
                            valid = 1;
                        else
                            printf("Invalid name! Attempt %d of 3\n", attempts);
                    }
                    if (valid == 0)
                        printf("3 attempts completed. Update cancelled.\n");
                    else
                        updateStudent((unsigned int)inputRollno, name);
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
                    if (scanf("%d", &inputRollno) == 1) {
                        if (getchar() == '\n') {
                            if (inputRollno > 0)
                                valid = 1;
                            else
                                printf("Invalid roll number! Attempt %d of 3\n", attempts);
                        }
                        else {
                            clearInput();
                            printf("Invalid roll number! Attempt %d of 3\n", attempts);
                        }
                    }
                    else {
                        clearInput();
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                    }
                }
                if (valid == 0)
                    printf("3 attempts completed. Delete cancelled.\n");
                else
                    deleteNode((unsigned int)inputRollno);
            }
        }
        else if (choice == 9) {
            printf("Program ended.\n");
            break;
        }
    }
    return 0;
}