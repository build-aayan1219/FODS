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
    if (scanf(" %49[^\n]", name) != 1) {
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
struct StudentInfo *rightRotate(struct StudentInfo *y) {
    struct StudentInfo *x;
    struct StudentInfo *temp;
    x = y->left;
    temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}
struct StudentInfo *leftRotate(struct StudentInfo *x) {
    struct StudentInfo *y;
    struct StudentInfo *temp;
    y = x->right;
    temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
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
void clearStack() {
    while (top != NULL)
        pop();
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
void clearQueue() {
    while (front != NULL)
        dequeue();
}
struct StudentInfo *insertNode(int rollno, char name[]) {
    struct StudentInfo *node;
    struct StudentInfo *newNode;
    struct StudentInfo *child;
    int balance;
    node = root;
    clearStack();
    if (node == NULL) {
        return createNode(rollno, name);
    }
    while (node != NULL) {
        if (rollno < node->rollno) {
            push(node);
            node = node->left;
        }
        else if (rollno > node->rollno) {
            push(node);
            node = node->right;
        }
        else {
            return root;
        }
    }
    newNode = createNode(rollno, name);
    if (newNode == NULL)
        return root;
    child = newNode;
    while (top != NULL) {
        node = pop();
        if (child->rollno < node->rollno)
            node->left = child;
        else
            node->right = child;
        node->height = 1 + max(height(node->left), height(node->right));
        balance = balanceFactor(node);
        if (balance > 1) {                                                  //left concentrated
            if (balanceFactor(node->left) >= 0)
                node = rightRotate(node);
            else {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }  
        }           
        
        else if (balance < -1) {                                            //right concentrated
            if (balanceFactor(node->right) <= 0)
                node = leftRotate(node);
            else {
                node->right = rightRotate(node->right);
                node = leftRotate(node);    
            }
        }
        child = node;
    }
    return child;
}
struct StudentInfo *searchNode(int rollno) {
    struct StudentInfo *traverse;
    traverse = root;
    while (traverse != NULL) {
        if (rollno == traverse->rollno)
            return traverse;
        if (rollno < traverse->rollno)
            traverse = traverse->left;
        else
            traverse = traverse->right;
    }
    return NULL;
}
struct StudentInfo *minimumNode(struct StudentInfo *node) {
    struct StudentInfo *traverse;
    traverse = node;
    while (traverse != NULL && traverse->left != NULL)
        traverse = traverse->left;
    return traverse;
}
void deleteAVL(int rollno) {
    struct StudentInfo *node;
    struct StudentInfo *parent;
    struct StudentInfo *successor;
    struct StudentInfo *child;
    struct StudentInfo *subtree;
    int balance;
    node = root;
    clearStack();
    while (node != NULL && node->rollno != rollno) {
        push(node);
        if (rollno < node->rollno)
            node = node->left;
        else
            node = node->right;
    }
    if (node == NULL)
        return;
    if (node->left != NULL && node->right != NULL) {                    //node has two child
        push(node);
        successor = node->right;                                        //access right subtree
        while (successor->left != NULL) {                               //find inorder successor which will be leftmost of right subtree
            push(successor);
            successor = successor->left;
        }
        node->rollno = successor->rollno;                               //copy successor's data into node which is to be deleted
        strcpy(node->name, successor->name);
        node = successor;                                               
    }
    if (node == NULL)
        return;
    child = NULL;                  //no child                     //find child(if it is there or not)
    if (node->left != NULL)
        child = node->left;                     //only left child
    else if (node->right != NULL)
        child = node->right;                    //only right child
    if (top == NULL) {
        root = child;                           //node is root..!! (no parent in stack)
    }
    else {                                                          //deleted node has parent
        parent = pop();
        if (parent->left == node)
            parent->left = child;
        else                                         //(already we did child=NULL, so when parent.right/left executes it returns NULL so that leaf node is deleted)
            parent->right = child;
        subtree = child;                                    //tree which is changed after deletion so we can rebalance
        while (1) { 
            parent->height = 1 + max(height(parent->left), height(parent->right));
            balance = balanceFactor(parent);
            if (balance > 1) {
                if (balanceFactor(parent->left) >= 0)
                    parent = rightRotate(parent);
                else {
                    parent->left = leftRotate(parent->left);
                    parent = rightRotate(parent);
                }
            }
            else if (balance < -1) {
                if (balanceFactor(parent->right) <= 0)
                    parent = leftRotate(parent);
                else {
                    parent->right = rightRotate(parent->right);
                    parent = leftRotate(parent);
                }
            }
            subtree = parent;               //after rotation parent changed so we need to update subtree
            if (top == NULL)
                break;
            parent = pop();
            if (subtree->rollno < parent->rollno)
                parent->left = subtree;
            else
                parent->right = subtree;
        }
        root = subtree;                 //final subtree is root of avl
    }
    free(node);
}
void inorder(struct StudentInfo *node) {
    struct StudentInfo *temp;

    clearStack();
    temp = node;

    while (temp != NULL || top != NULL) {
        if (temp != NULL) {
            push(temp);
            temp = temp->left;
        }
        else {
            temp = pop();
            printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
            temp = temp->right;
        }
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
        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
        if (temp->right != NULL)
            push(temp->right);
        if (temp->left != NULL)
            push(temp->left);
    }
}
void postorder(struct StudentInfo *node) {
    struct StudentInfo *temp;
    struct StackNode *secondTop;
    struct StackNode *newNode;
    clearStack();
    secondTop = NULL;
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
        if (temp->right != NULL)
            push(temp->right);
    }
    while (secondTop != NULL) {
        temp = secondTop->student;
        newNode = secondTop;
        secondTop = secondTop->next;
        free(newNode);
        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
    }
}
void breadthFirst() {
    struct StudentInfo *temp;
    clearQueue();
    if (root == NULL)
        return;
    enqueue(root);
    while (front != NULL) {
        temp = dequeue();
        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
        if (temp->left != NULL)
            enqueue(temp->left);
        if (temp->right != NULL)
            enqueue(temp->right);
    }
}
void depthFirst() {
    struct StudentInfo *temp;
    clearStack();
    if (root == NULL)
        return;
    push(root);
    while (top != NULL) {
        temp = pop();
        printf("Roll No: %d  Name: %s\n", temp->rollno, temp->name);
        if (temp->right != NULL)
            push(temp->right);
        if (temp->left != NULL)
            push(temp->left);
    }
}
void updateStudent(int rollno, char name[]) {
    struct StudentInfo *node;
    node = searchNode(rollno);
    if (node == NULL)
        printf("Roll number not found\n");
    else {
        strcpy(node->name, name);
        printf("Name updated successfully\n");
    }
}
void deleteStudent(int rollno) {
    if (searchNode(rollno) == NULL)
        printf("Roll number not found\n");
    else {
        deleteAVL(rollno);
        printf("Student deleted successfully\n");
    }
}
int main() {
    int n, choice, i, attempts, valid, exitProgram, duplicate;
    int rollno, newRollno;
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
        }
        else {
            duplicate = 0;
            if (searchNode(rollno) != NULL)
                duplicate = 1;
            if (duplicate == 1) {
                printf("Roll number already exists. Student not created.\n");
            }
            else {
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
                }
                else {
                    root = insertNode(rollno, name);
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
        }
        else if (choice == 1) {
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
            }
            else if (searchNode(rollno) != NULL) {
                printf("Roll number already exists. Student not created.\n");
            }
            else {
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
                    root = insertNode(rollno, name);
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
                printf("\nBreadth First Traversal:\n");
                breadthFirst();
            }
        }
        else if (choice == 6) {
            if (root == NULL)
                printf("Tree is empty\n");
            else {
                printf("\nDepth First Traversal:\n");
                depthFirst();
            }
        }
        else if (choice == 7) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
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
                }
                else if (searchNode(rollno) == NULL) {
                    printf("Roll number not found\n");
                }
                else {
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
        }
        else if (choice == 8) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                valid = 0;
                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to delete: ");
                    if (readInteger(&rollno) == 1 && rollno > 0)
                        valid = 1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n", attempts);
                }
                if (valid == 0)
                    printf("3 attempts completed. Delete cancelled.\n");
                else
                    deleteStudent(rollno);
            }
        }
        else if (choice == 9) {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }
    return 0;
}