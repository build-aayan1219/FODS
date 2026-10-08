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

struct StudentInfo *createNode(unsigned int rollno,char name[]) {
    struct StudentInfo *node;

    node = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));

    if (node == NULL)
        return NULL;

    node->rollno = rollno;
    strcpy(node->name,name);
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct StudentInfo *insertNode(struct StudentInfo *node,unsigned int rollno,char name[]) {
    if (node == NULL)
        return createNode(rollno,name);

    if (rollno < node->rollno)
        node->left = insertNode(node->left,rollno,name);
    else if (rollno > node->rollno)
        node->right = insertNode(node->right,rollno,name);

    return node;
}

struct StudentInfo *searchNode(struct StudentInfo *node,unsigned int rollno) {
    if (node == NULL)
        return NULL;

    if (node->rollno == rollno)
        return node;

    if (rollno < node->rollno)
        return searchNode(node->left,rollno);

    return searchNode(node->right,rollno);
}

void display(struct StudentInfo *node) {
    if (node != NULL) {
        display(node->left);
        printf("Roll No: %u  Name: %s\n",node->rollno,node->name);
        display(node->right);
    }
}

void preorder(struct StudentInfo *node) {
    if (node != NULL) {
        printf("Roll No: %u  Name: %s\n",node->rollno,node->name);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(struct StudentInfo *node) {
    if (node != NULL) {
        inorder(node->left);
        printf("Roll No: %u  Name: %s\n",node->rollno,node->name);
        inorder(node->right);
    }
}

void postorder(struct StudentInfo *node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("Roll No: %u  Name: %s\n",node->rollno,node->name);
    }
}

struct StudentInfo *findMin(struct StudentInfo *node) {
    if (node == NULL || node->left == NULL)
        return node;

    return findMin(node->left);
}

struct StudentInfo *deleteNode(struct StudentInfo *node,unsigned int rollno,int *deleted) {
    struct StudentInfo *temp;

    if (node == NULL)
        return NULL;

    if (rollno < node->rollno) {
        node->left = deleteNode(node->left,rollno,deleted);
    }
    else if (rollno > node->rollno) {
        node->right = deleteNode(node->right,rollno,deleted);
    }
    else {
        *deleted = 1;

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

        temp = findMin(node->right);
        node->rollno = temp->rollno;
        strcpy(node->name,temp->name);
        node->right = deleteNode(node->right,temp->rollno,deleted);
    }

    return node;
}

int readNumberOfStudents(int *n) {
    char input[50];
    char extra;
    int value;

    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;

    if (sscanf(input,"%d %c",&value,&extra) == 1 && value > 0 && value <= 10) {
        *n = value;
        return 1;
    }

    return 0;
}

int readRollNumber(unsigned int *rollno) {
    char input[50];
    char extra;
    long long value;

    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;

    if (sscanf(input,"%lld %c",&value,&extra) == 1 && value > 0 && value <= 4294967295LL) {
        *rollno = (unsigned int)value;
        return 1;
    }

    return 0;
}

int readName(char name[]) {
    char input[50];
    int i;

    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;

    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }

    if (validName(input)) {
        strcpy(name,input);
        return 1;
    }

    return 0;
}

int readChoice(int *choice) {
    char input[50];
    char extra;
    int value;

    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;

    if (sscanf(input,"%d %c",&value,&extra) == 1 && value >= 1 && value <= 8) {
        *choice = value;
        return 1;
    }

    return 0;
}

int main() {
    int n;
    int choice;
    int i;
    int attempts;
    int valid;
    int exitProgram;
    int duplicate;
    int deleted;
    unsigned int rollno;
    char name[50];

    valid = 0;

    for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
        printf("Enter number of students: ");

        if (readNumberOfStudents(&n)) {
            valid = 1;
        }
        else {
            printf("Invalid input! Attempt %d of 3\n",attempts);
        }
    }

    if (valid == 0) {
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }

    i = 0;

    while (i < n) {
        printf("\nEnter details of student %d\n",i + 1);

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter roll number: ");

            if (readRollNumber(&rollno)) {
                valid = 1;
            }
            else {
                printf("Invalid roll number! Attempt %d of 3\n",attempts);
            }
        }

        if (valid == 0) {
            printf("3 attempts completed. Please enter Student %d again.\n",i + 1);
        }
        else {
            valid = 0;

            for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                printf("Enter name: ");

                if (readName(name)) {
                    valid = 1;
                }
                else {
                    printf("Invalid name! Attempt %d of 3\n",attempts);
                }
            }

            if (valid == 0) {
                printf("3 attempts completed. Please enter Student %d again.\n",i + 1);
            }
            else {
                duplicate = 0;

                if (searchNode(root,rollno) != NULL)
                    duplicate = 1;

                if (duplicate == 1) {
                    printf("Roll number already exists. Student not created.\n");
                }
                else {
                    root = insertNode(root,rollno,name);

                    if (root != NULL) {
                        printf("Student created successfully\n");
                        i++;
                    }
                    else {
                        printf("Memory allocation failed\n");
                    }
                }
            }
        }
    }

    exitProgram = 0;

    while (exitProgram == 0) {
        printf("\n1. Create\n");
        printf("2. Read\n");
        printf("3. Preorder\n");
        printf("4. Inorder\n");
        printf("5. Postorder\n");
        printf("6. Update\n");
        printf("7. Delete\n");
        printf("8. Exit\n");

        valid = 0;

        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
            printf("Enter your choice: ");

            if (readChoice(&choice)) {
                valid = 1;
            }
            else {
                printf("Invalid choice! Attempt %d of 3\n",attempts);
            }
        }

        if (valid == 0) {
            printf("3 attempts completed. Program ended.\n");
            exitProgram = 1;
        }
        else if (choice == 1) {
            valid = 0;

            for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                printf("Enter roll number: ");

                if (readRollNumber(&rollno)) {
                    valid = 1;
                }
                else {
                    printf("Invalid roll number! Attempt %d of 3\n",attempts);
                }
            }

            if (valid == 0) {
                printf("3 attempts completed. Create cancelled.\n");
            }
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter name: ");

                    if (readName(name)) {
                        valid = 1;
                    }
                    else {
                        printf("Invalid name! Attempt %d of 3\n",attempts);
                    }
                }

                if (valid == 0) {
                    printf("3 attempts completed. Create cancelled.\n");
                }
                else {
                    duplicate = 0;

                    if (searchNode(root,rollno) != NULL)
                        duplicate = 1;

                    if (duplicate == 1) {
                        printf("Roll number already exists. Student not created.\n");
                    }
                    else {
                        root = insertNode(root,rollno,name);

                        if (root != NULL)
                            printf("Student created successfully\n");
                        else
                            printf("Memory allocation failed\n");
                    }
                }
            }
        }
        else if (choice == 2) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                printf("\nStudents in Binary Search Tree:\n");
                display(root);
            }
        }
        else if (choice == 3) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                printf("\nPreorder Traversal:\n");
                preorder(root);
            }
        }
        else if (choice == 4) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                printf("\nInorder Traversal:\n");
                inorder(root);
            }
        }
        else if (choice == 5) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                printf("\nPostorder Traversal:\n");
                postorder(root);
            }
        }
        else if (choice == 6) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to update: ");

                    if (readRollNumber(&rollno)) {
                        valid = 1;
                    }
                    else {
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                    }
                }

                if (valid == 0) {
                    printf("3 attempts completed. Update cancelled.\n");
                }
                else {
                    struct StudentInfo *student;

                    student = searchNode(root,rollno);

                    if (student == NULL) {
                        printf("Roll number not found\n");
                    }
                    else {
                        valid = 0;

                        for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                            printf("Enter new name: ");

                            if (readName(name)) {
                                valid = 1;
                            }
                            else {
                                printf("Invalid name! Attempt %d of 3\n",attempts);
                            }
                        }

                        if (valid == 0) {
                            printf("3 attempts completed. Update cancelled.\n");
                        }
                        else {
                            strcpy(student->name,name);
                            printf("Name updated successfully\n");
                        }
                    }
                }
            }
        }
        else if (choice == 7) {
            if (root == NULL) {
                printf("Tree is empty\n");
            }
            else {
                valid = 0;

                for (attempts = 1; attempts <= 3 && valid == 0; attempts++) {
                    printf("Enter roll number to delete: ");

                    if (readRollNumber(&rollno)) {
                        valid = 1;
                    }
                    else {
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                    }
                }

                if (valid == 0) {
                    printf("3 attempts completed. Delete cancelled.\n");
                }
                else {
                    deleted = 0;
                    root = deleteNode(root,rollno,&deleted);

                    if (deleted == 1)
                        printf("Student deleted successfully\n");
                    else
                        printf("Roll number not found\n");
                }
            }
        }
        else if (choice == 8) {
            printf("Program ended.\n");
            exitProgram = 1;
        }
    }

    return 0;
}