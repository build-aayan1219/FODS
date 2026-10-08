#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
    for (i = 0; name[i] != '\0'; i++)
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
            return 0;
    return 1;
}

int readPositiveNumber(int *value,int max) {
    char input[50],extra;
    long long number;
    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;
    if (sscanf(input,"%lld %c",&number,&extra) == 1 && number > 0 && number <= max) {
        *value=(int)number;
        return 1;
    }
    return 0;
}

int readRollNumber(unsigned int *rollno) {
    char input[50],extra;
    unsigned long long number;
    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;
    if (sscanf(input,"%llu %c",&number,&extra) == 1 && number > 0 && number <= UINT_MAX) {
        *rollno=(unsigned int)number;
        return 1;
    }
    return 0;
}

int readName(char name[]) {
    char input[50];
    int i;
    if (fgets(input,sizeof(input),stdin) == NULL)
        return 0;
    for (i=0;input[i]!='\0';i++)
        if (input[i]=='\n') {
            input[i]='\0';
            break;
        }
    if (validName(input)) {
        strcpy(name,input);
        return 1;
    }
    return 0;
}

int readChoice(int *choice) {
    return readPositiveNumber(choice,8);
}

struct StudentInfo *createNode(unsigned int rollno,char name[]) {
    struct StudentInfo *node;
    node=(struct StudentInfo *)malloc(sizeof(struct StudentInfo));
    if (node==NULL)
        return NULL;
    node->rollno=rollno;
    strcpy(node->name,name);
    node->left=NULL;
    node->right=NULL;
    return node;
}

int height(struct StudentInfo *node) {
    int leftHeight,rightHeight;
    if (node==NULL)
        return 0;
    leftHeight=height(node->left);
    rightHeight=height(node->right);
    if (leftHeight>rightHeight)
        return leftHeight+1;
    return rightHeight+1;
}

int insertAtLevel(struct StudentInfo *node,struct StudentInfo *newNode,int level) {
    if (node==NULL)
        return 0;
    if (level==1) {
        if (node->left==NULL) {
            node->left=newNode;
            return 1;
        }
        if (node->right==NULL) {
            node->right=newNode;
            return 1;
        }
        return 0;
    }
    if (insertAtLevel(node->left,newNode,level-1))
        return 1;
    return insertAtLevel(node->right,newNode,level-1);
}

void addNode(unsigned int rollno,char name[]) {
    struct StudentInfo *newNode;
    int h,level;
    newNode=createNode(rollno,name);
    if (newNode==NULL)
        return;
    if (root==NULL) {
        root=newNode;
        return;
    }
    h=height(root);
    for (level=1;level<=h;level++)
        if (insertAtLevel(root,newNode,level))
            return;
    insertAtLevel(root,newNode,h+1);
}

struct StudentInfo *searchNode(struct StudentInfo *node,unsigned int rollno) {
    struct StudentInfo *found;
    if (node==NULL)
        return NULL;
    if (node->rollno==rollno)
        return node;
    found=searchNode(node->left,rollno);
    if (found!=NULL)
        return found;
    return searchNode(node->right,rollno);
}

void displayLevel(struct StudentInfo *node,int level) {
    if (node==NULL)
        return;
    if (level==1) {
        printf("Roll No: %u Name: %s\n",node->rollno,node->name);
        return;
    }
    displayLevel(node->left,level-1);
    displayLevel(node->right,level-1);
}

void display() {
    int h,level;
    if (root==NULL) {
        printf("Tree is empty\n");
        return;
    }
    h=height(root);
    for (level=1;level<=h;level++)
        displayLevel(root,level);
}

void preorder(struct StudentInfo *node) {
    if (node!=NULL) {
        printf("Roll No: %u Name: %s\n",node->rollno,node->name);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(struct StudentInfo *node) {
    if (node!=NULL) {
        inorder(node->left);
        printf("Roll No: %u Name: %s\n",node->rollno,node->name);
        inorder(node->right);
    }
}

void postorder(struct StudentInfo *node) {
    if (node!=NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("Roll No: %u Name: %s\n",node->rollno,node->name);
    }
}

void findLastNode(struct StudentInfo *node,struct StudentInfo **last,struct StudentInfo **parent,int depth,int *maxDepth) {
    if (node==NULL)
        return;
    if (depth>=*maxDepth) {
        *maxDepth=depth;
        *last=node;
    }
    if (node->left!=NULL) {
        *parent=node;
        findLastNode(node->left,last,parent,depth+1,maxDepth);
    }
    if (node->right!=NULL) {
        *parent=node;
        findLastNode(node->right,last,parent,depth+1,maxDepth);
    }
}

void deleteNode(unsigned int rollno) {
    struct StudentInfo *found,*last,*parent;
    int maxDepth;
    if (root==NULL) {
        printf("Tree is empty\n");
        return;
    }
    found=searchNode(root,rollno);
    if (found==NULL) {
        printf("Roll number not found\n");
        return;
    }
    if (root->left==NULL && root->right==NULL) {
        free(root);
        root=NULL;
        printf("Node deleted successfully\n");
        return;
    }
    last=NULL;
    parent=NULL;
    maxDepth=0;
    findLastNode(root,&last,&parent,1,&maxDepth);
    found->rollno=last->rollno;
    strcpy(found->name,last->name);
    if (parent->right==last)
        parent->right=NULL;
    else
        parent->left=NULL;
    free(last);
    printf("Node deleted successfully\n");
}

void update(unsigned int rollno,char name[]) {
    struct StudentInfo *node;
    node=searchNode(root,rollno);
    if (node==NULL) {
        printf("Roll number not found\n");
        return;
    }
    strcpy(node->name,name);
    printf("Name updated successfully\n");
}

int main() {
    int n,choice,i,attempts,valid,found,exitProgram;
    unsigned int rollno;
    char name[50];

    valid=0;
    for (attempts=1;attempts<=3 && valid==0;attempts++) {
        printf("Enter number of students: ");
        if (readPositiveNumber(&n,10))
            valid=1;
        else
            printf("Invalid input! Attempt %d of 3\n",attempts);
    }
    if (valid==0) {
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }

    i=0;
    while (i<n) {
        printf("\nEnter details of student %d\n",i+1);
        valid=0;
        for (attempts=1;attempts<=3 && valid==0;attempts++) {
            printf("Enter roll number: ");
            if (readRollNumber(&rollno))
                valid=1;
            else
                printf("Invalid roll number! Attempt %d of 3\n",attempts);
        }
        if (valid==0) {
            printf("3 attempts completed. Please enter Student %d again.\n",i+1);
            continue;
        }

        valid=0;
        for (attempts=1;attempts<=3 && valid==0;attempts++) {
            printf("Enter name: ");
            if (readName(name))
                valid=1;
            else
                printf("Invalid name! Attempt %d of 3\n",attempts);
        }
        if (valid==0) {
            printf("3 attempts completed. Please enter Student %d again.\n",i+1);
            continue;
        }

        found=0;
        if (searchNode(root,rollno)!=NULL)
            found=1;
        if (found==1)
            printf("Roll number already exists. Student not created.\n");
        else {
            addNode(rollno,name);
            printf("Student created successfully\n");
            i++;
        }
    }

    exitProgram=0;
    while (exitProgram==0) {
        printf("\n1. Insert\n");
        printf("2. Display\n");
        printf("3. Preorder\n");
        printf("4. Inorder\n");
        printf("5. Postorder\n");
        printf("6. Update\n");
        printf("7. Delete\n");
        printf("8. Exit\n");

        valid=0;
        for (attempts=1;attempts<=3 && valid==0;attempts++) {
            printf("Enter your choice: ");
            if (readChoice(&choice))
                valid=1;
            else
                printf("Invalid choice! Attempt %d of 3\n",attempts);
        }

        if (valid==0) {
            printf("3 attempts completed. Program ended.\n");
            exitProgram=1;
        }
        else if (choice==1) {
            valid=0;
            for (attempts=1;attempts<=3 && valid==0;attempts++) {
                printf("Enter roll number: ");
                if (readRollNumber(&rollno))
                    valid=1;
                else
                    printf("Invalid roll number! Attempt %d of 3\n",attempts);
            }
            if (valid==0)
                printf("3 attempts completed. Insert cancelled.\n");
            else {
                valid=0;
                for (attempts=1;attempts<=3 && valid==0;attempts++) {
                    printf("Enter name: ");
                    if (readName(name))
                        valid=1;
                    else
                        printf("Invalid name! Attempt %d of 3\n",attempts);
                }
                if (valid==0)
                    printf("3 attempts completed. Insert cancelled.\n");
                else if (searchNode(root,rollno)!=NULL)
                    printf("Roll number already exists. Student not created.\n");
                else {
                    addNode(rollno,name);
                    printf("Student inserted successfully\n");
                }
            }
        }
        else if (choice==2)
            display();
        else if (choice==3) {
            if (root==NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPreorder Traversal:\n");
                preorder(root);
            }
        }
        else if (choice==4) {
            if (root==NULL)
                printf("Tree is empty\n");
            else {
                printf("\nInorder Traversal:\n");
                inorder(root);
            }
        }
        else if (choice==5) {
            if (root==NULL)
                printf("Tree is empty\n");
            else {
                printf("\nPostorder Traversal:\n");
                postorder(root);
            }
        }
        else if (choice==6) {
            if (root==NULL)
                printf("Tree is empty\n");
            else {
                valid=0;
                for (attempts=1;attempts<=3 && valid==0;attempts++) {
                    printf("Enter roll number to update: ");
                    if (readRollNumber(&rollno))
                        valid=1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                }
                if (valid==0)
                    printf("3 attempts completed. Update cancelled.\n");
                else if (searchNode(root,rollno)==NULL)
                    printf("Roll number not found\n");
                else {
                    valid=0;
                    for (attempts=1;attempts<=3 && valid==0;attempts++) {
                        printf("Enter new name: ");
                        if (readName(name))
                            valid=1;
                        else
                            printf("Invalid name! Attempt %d of 3\n",attempts);
                    }
                    if (valid==0)
                        printf("3 attempts completed. Update cancelled.\n");
                    else
                        update(rollno,name);
                }
            }
        }
        else if (choice==7) {
            if (root==NULL)
                printf("Tree is empty\n");
            else {
                valid=0;
                for (attempts=1;attempts<=3 && valid==0;attempts++) {
                    printf("Enter roll number to delete: ");
                    if (readRollNumber(&rollno))
                        valid=1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                }
                if (valid==0)
                    printf("3 attempts completed. Delete cancelled.\n");
                else
                    deleteNode(rollno);
            }
        }
        else if (choice==8) {
            printf("Program ended.\n");
            exitProgram=1;
        }
    }
    return 0;
}