#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo{
    int rollno;
    char name[50];
    struct StudentInfo *left;
    struct StudentInfo *right;
};

struct StackNode{
    struct StudentInfo *student;
    struct StackNode *next;
};

struct QueueNode{
    struct StudentInfo *student;
    struct QueueNode *next;
};

struct StudentInfo *root=NULL;
struct StackNode *top=NULL;
struct QueueNode *front=NULL;
struct QueueNode *rear=NULL;

int validName(char name[]){
    int i;
    if(name[0]=='\0'||name[0]==' ') return 0;
    for(i=0;name[i]!='\0';i++)
        if(!((name[i]>='A'&&name[i]<='Z')||(name[i]>='a'&&name[i]<='z')||name[i]==' ')) return 0;
    return 1;
}

int stackEmpty(){
    if(top==NULL) return 1;
    return 0;
}

void push(struct StudentInfo *student){
    struct StackNode *newNode;
    newNode=(struct StackNode *)malloc(sizeof(struct StackNode));
    if(newNode==NULL) return;
    newNode->student=student;
    newNode->next=top;
    top=newNode;
}

struct StudentInfo *pop(){
    struct StackNode *temp;
    struct StudentInfo *student;
    if(top==NULL) return NULL;
    temp=top;
    student=top->student;
    top=top->next;
    free(temp);
    return student;
}

int queueEmpty(){
    if(front==NULL) return 1;
    return 0;
}

void enqueue(struct StudentInfo *student){
    struct QueueNode *newNode;
    newNode=(struct QueueNode *)malloc(sizeof(struct QueueNode));
    if(newNode==NULL) return;
    newNode->student=student;
    newNode->next=NULL;
    if(rear==NULL){
        front=newNode;
        rear=newNode;
    }
    else{
        rear->next=newNode;
        rear=newNode;
    }
}

struct StudentInfo *dequeue(){
    struct QueueNode *temp;
    struct StudentInfo *student;
    if(front==NULL) return NULL;
    temp=front;
    student=front->student;
    front=front->next;
    if(front==NULL)
        rear=NULL;
    free(temp);
    return student;
}

int searchNode(int rollno){
    struct StudentInfo *student;
    top=NULL;
    if(root==NULL) return 0;
    push(root);
    while(!stackEmpty()){
        student=pop();
        if(student->rollno==rollno) return 1;
        if(student->right!=NULL) push(student->right);
        if(student->left!=NULL) push(student->left);
    }
    return 0;
}

void addNode(int rollno,char name[]){
    struct StudentInfo *student,*temp;
    student=(struct StudentInfo *)malloc(sizeof(struct StudentInfo));
    if(student==NULL){
        printf("Memory allocation failed\n");
        return;
    }
    student->rollno=rollno;
    strcpy(student->name,name);
    student->left=NULL;
    student->right=NULL;
    if(root==NULL){
        root=student;
        return;
    }
    front=NULL;
    rear=NULL;
    enqueue(root);
    while(!queueEmpty()){
        temp=dequeue();
        if(temp->left==NULL){
            temp->left=student;
            return;
        }
        enqueue(temp->left);
        if(temp->right==NULL){
            temp->right=student;
            return;
        }
        enqueue(temp->right);
    }
}

void display(){
    struct StudentInfo *student;
    if(root==NULL){
        printf("Tree is empty\n");
        return;
    }
    front=NULL;
    rear=NULL;
    enqueue(root);
    while(!queueEmpty()){
        student=dequeue();
        printf("Roll No: %d Name: %s\n",student->rollno,student->name);
        if(student->left!=NULL) enqueue(student->left);
        if(student->right!=NULL) enqueue(student->right);
    }
}

void preorder(){
    struct StudentInfo *student;
    top=NULL;
    push(root);
    while(!stackEmpty()){
        student=pop();
        printf("Roll No: %d Name: %s\n",student->rollno,student->name);
        if(student->right!=NULL) push(student->right);
        if(student->left!=NULL) push(student->left);
    }
}

void inorder(){
    struct StudentInfo *student;
    student=root;
    top=NULL;
    while(student!=NULL||!stackEmpty()){
        while(student!=NULL){
            push(student);
            student=student->left;
        }
        student=pop();
        printf("Roll No: %d Name: %s\n",student->rollno,student->name);
        student=student->right;
    }
}

void postorder(){
    struct StudentInfo *student,*previous;
    student=root;
    previous=NULL;
    top=NULL;
    while(student!=NULL||!stackEmpty()){
        while(student!=NULL){
            push(student);
            student=student->left;
        }
        student=top->student;
        if(student->right!=NULL&&student->right!=previous)
            student=student->right;
        else{
            printf("Roll No: %d Name: %s\n",student->rollno,student->name);
            previous=pop();
            student=NULL;
        }
    }
}

void bfs(){
    struct StudentInfo *student;
    if(root==NULL){
        printf("Tree is empty\n");
        return;
    }
    front=NULL;
    rear=NULL;
    enqueue(root);
    while(!queueEmpty()){
        student=dequeue();
        printf("Roll No: %d Name: %s\n",student->rollno,student->name);
        if(student->left!=NULL) enqueue(student->left);
        if(student->right!=NULL) enqueue(student->right);
    }
}

void dfs(){
    struct StudentInfo *student;
    if(root==NULL){
        printf("Tree is empty\n");
        return;
    }
    top=NULL;
    push(root);
    while(!stackEmpty()){
        student=pop();
        printf("Roll No: %d Name: %s\n",student->rollno,student->name);
        if(student->right!=NULL) push(student->right);
        if(student->left!=NULL) push(student->left);
    }
}

void update(int rollno,char name[]){
    struct StudentInfo *student;
    top=NULL;
    push(root);
    while(!stackEmpty()){
        student=pop();
        if(student->rollno==rollno){
            strcpy(student->name,name);
            printf("Name updated successfully\n");
            return;
        }
        if(student->right!=NULL) push(student->right);
        if(student->left!=NULL) push(student->left);
    }
    printf("Roll number not found\n");
}

void deleteNode(int rollno){
    struct StudentInfo *student,*found,*last,*lastParent;
    if(root==NULL){
        printf("Tree is empty\n");
        return;
    }
    found=NULL;
    last=NULL;
    lastParent=NULL;
    front=NULL;
    rear=NULL;
    enqueue(root);
    while(!queueEmpty()){
        student=dequeue();
        if(student->rollno==rollno)
            found=student;
        last=student;
        if(student->left!=NULL) enqueue(student->left);
        if(student->right!=NULL) enqueue(student->right);
    }
    if(found==NULL){
        printf("Roll number not found\n");
        return;
    }
    if(last==root){
        free(root);
        root=NULL;
        printf("Node deleted successfully\n");
        return;
    }
    front=NULL;
    rear=NULL;
    enqueue(root);
    while(!queueEmpty()){
        student=dequeue();
        if(student->left==last||student->right==last){
            lastParent=student;
            break;
        }
        if(student->left!=NULL) enqueue(student->left);
        if(student->right!=NULL) enqueue(student->right);
    }
    found->rollno=last->rollno;
    strcpy(found->name,last->name);
    if(lastParent->left==last)
        lastParent->left=NULL;
    else
        lastParent->right=NULL;
    free(last);
    printf("Node deleted successfully\n");
}

int main(){
    int n,choice,i,attempts,valid,rollno,exitProgram;
    char name[50];

    valid=0;
    for(attempts=1;attempts<=3&&valid==0;attempts++){
        printf("Enter number of students: ");
        scanf("%d",&n);
        if(n>0&&n<=10)
            valid=1;
        else
            printf("Invalid input! Attempt %d of 3\n",attempts);
    }

    if(valid==0){
        printf("3 attempts completed. Program ended.\n");
        return 0;
    }

    i=0;
    while(i<n){
        printf("\nEnter details of student %d\n",i+1);
        valid=0;

        for(attempts=1;attempts<=3&&valid==0;attempts++){
            printf("Enter roll number: ");
            scanf("%d",&rollno);

            if(rollno>0){
                if(searchNode(rollno)==1)
                    printf("Roll number already exists. Enter another roll number.\n");
                else
                    valid=1;
            }
            else
                printf("Invalid roll number! Attempt %d of 3\n",attempts);
        }

        if(valid==0){
            printf("3 attempts completed. Please enter Student %d again.\n",i+1);
            continue;
        }

        valid=0;
        for(attempts=1;attempts<=3&&valid==0;attempts++){
            printf("Enter name: ");
            scanf(" %49[^\n]",name);

            if(validName(name))
                valid=1;
            else
                printf("Invalid name! Attempt %d of 3\n",attempts);
        }

        if(valid==0)
            printf("3 attempts completed. Please enter Student %d again.\n",i+1);
        else{
            addNode(rollno,name);
            printf("Student created successfully\n");
            i++;
        }
    }

    exitProgram=0;

    while(exitProgram==0){
        printf("\n1. Insert\n");
        printf("2. Display\n");
        printf("3. Preorder\n");
        printf("4. Inorder\n");
        printf("5. Postorder\n");
        printf("6. BFS\n");
        printf("7. DFS\n");
        printf("8. Update\n");
        printf("9. Delete\n");
        printf("10. Exit\n");

        valid=0;
        for(attempts=1;attempts<=3&&valid==0;attempts++){
            printf("Enter your choice: ");
            scanf("%d",&choice);

            if(choice>=1&&choice<=10)
                valid=1;
            else
                printf("Invalid choice! Attempt %d of 3\n",attempts);
        }

        if(valid==0){
            printf("3 attempts completed. Program ended.\n");
            exitProgram=1;
        }
        else if(choice==1){
            valid=0;

            for(attempts=1;attempts<=3&&valid==0;attempts++){
                printf("Enter roll number: ");
                scanf("%d",&rollno);

                if(rollno>0){
                    if(searchNode(rollno)==1)
                        printf("Roll number already exists. Enter another roll number.\n");
                    else
                        valid=1;
                }
                else
                    printf("Invalid roll number! Attempt %d of 3\n",attempts);
            }

            if(valid==0)
                printf("3 attempts completed. Insert cancelled.\n");
            else{
                valid=0;

                for(attempts=1;attempts<=3&&valid==0;attempts++){
                    printf("Enter name: ");
                    scanf(" %49[^\n]",name);

                    if(validName(name))
                        valid=1;
                    else
                        printf("Invalid name! Attempt %d of 3\n",attempts);
                }

                if(valid==0)
                    printf("3 attempts completed. Insert cancelled.\n");
                else{
                    addNode(rollno,name);
                    printf("Student inserted successfully\n");
                }
            }
        }
        else if(choice==2)
            display();
        else if(choice==3){
            if(root==NULL)
                printf("Tree is empty\n");
            else{
                printf("\nPreorder Traversal:\n");
                preorder();
            }
        }
        else if(choice==4){
            if(root==NULL)
                printf("Tree is empty\n");
            else{
                printf("\nInorder Traversal:\n");
                inorder();
            }
        }
        else if(choice==5){
            if(root==NULL)
                printf("Tree is empty\n");
            else{
                printf("\nPostorder Traversal:\n");
                postorder();
            }
        }
        else if(choice==6){
            printf("\nBreadth First Traversal:\n");
            bfs();
        }
        else if(choice==7){
            printf("\nDepth First Traversal:\n");
            dfs();
        }
        else if(choice==8){
            if(root==NULL)
                printf("Tree is empty\n");
            else{
                valid=0;

                for(attempts=1;attempts<=3&&valid==0;attempts++){
                    printf("Enter roll number to update: ");
                    scanf("%d",&rollno);

                    if(rollno>0)
                        valid=1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                }

                if(valid==0)
                    printf("3 attempts completed. Update cancelled.\n");
                else if(searchNode(rollno)==0)
                    printf("Roll number not found\n");
                else{
                    valid=0;

                    for(attempts=1;attempts<=3&&valid==0;attempts++){
                        printf("Enter new name: ");
                        scanf(" %49[^\n]",name);

                        if(validName(name))
                            valid=1;
                        else
                            printf("Invalid name! Attempt %d of 3\n",attempts);
                    }

                    if(valid==0)
                        printf("3 attempts completed. Update cancelled.\n");
                    else
                        update(rollno,name);
                }
            }
        }
        else if(choice==9){
            if(root==NULL)
                printf("Tree is empty\n");
            else{
                valid=0;

                for(attempts=1;attempts<=3&&valid==0;attempts++){
                    printf("Enter roll number to delete: ");
                    scanf("%d",&rollno);

                    if(rollno>0)
                        valid=1;
                    else
                        printf("Invalid roll number! Attempt %d of 3\n",attempts);
                }

                if(valid==0)
                    printf("3 attempts completed. Delete cancelled.\n");
                else
                    deleteNode(rollno);
            }
        }
        else if(choice==10){
            printf("Program ended.\n");
            exitProgram=1;
        }
    }

    return 0;
}

