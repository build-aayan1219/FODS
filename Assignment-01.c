// Assignment-01 : Write C program to implement student database using file handling

#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

void clear_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void input_name(char name[]) {
    fgets(name, 50, stdin);

    int i = 0;
    while (name[i] != '\0') {
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
        i++;
    }
}

int valid_name(char name[]) {
    int i = 0;

    if (name[0] == '\0')
        return 0;

    while (name[i] != '\0') {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' ')) {
            return 0;
        }
        i++;
    }

    return 1;
}

int roll_exists(int roll_no) {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "rb");

    if (fp == NULL)
        return 0;

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll_no == roll_no) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void create_file() {
    FILE *fp;
    struct Student s;
    int attempts = 0;

    while (attempts < 3) {
        printf("\nEnter Roll No: ");

        if (scanf("%d", &s.roll_no) != 1) {
            printf("Invalid Roll No!\n");
            clear_buffer();
            attempts++;
            continue;
        }

        clear_buffer();

        if (s.roll_no <= 0) {
            printf("Roll No must be greater than 0!\n");
            attempts++;
            continue;
        }

        if (roll_exists(s.roll_no)) {
            printf("Roll No already exists! Try another Roll No.\n");
            attempts++;
            continue;
        }

        break;
    }

    if (attempts == 3) {
        printf("3 wrong attempts. Returning to main menu.\n");
        return;
    }

    printf("Enter Name: ");
    input_name(s.name);

    if (!valid_name(s.name)) {
        printf("Invalid Name! Name should contain only letters and spaces.\n");
        return;
    }

    printf("Enter Marks: ");

    if (scanf("%f", &s.marks) != 1) {
        printf("Invalid Marks!\n");
        clear_buffer();
        return;
    }

    fp = fopen("students.txt", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record Created Successfully!\n");
}

void read_file() {
    FILE *fp;
    struct Student s;
    int found = 0;

    fp = fopen("students.txt", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        found = 1;
        printf("\nRoll No: %d", s.roll_no);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
    }

    if (!found)
        printf("No records found!\n");

    fclose(fp);
}
void update_file() {
    FILE *fp;
    struct Student s;
    int roll_no;
    int found = 0;
    int attempts = 0;
    int choice;
    char new_name[50];
    float new_marks;

    while (attempts < 3) {
        fp = fopen("students.txt", "rb+");

        if (fp == NULL) {
            printf("No records found!\n");
            return;
        }

        printf("\nEnter Roll No to update: ");

        if (scanf("%d", &roll_no) != 1) {
            printf("Invalid Roll No!\n");
            clear_buffer();
            fclose(fp);
            attempts++;
            continue;
        }

        clear_buffer();

        if (roll_no <= 0) {
            printf("Roll No must be greater than 0!\n");
            fclose(fp);
            attempts++;
            continue;
        }

        while (fread(&s, sizeof(s), 1, fp) == 1) {
            if (s.roll_no == roll_no) {
                found = 1;
                break;
            }
        }

        if (found)
            break;

        attempts++;
        fclose(fp);

        if (attempts < 3)
            printf("Record Not Found! Try again.\n");
    }

    if (!found) {
        printf("3 wrong attempts. Returning to main menu.\n");
        return;
    }

    printf("\nCurrent Record:");
    printf("\nRoll No: %d", s.roll_no);
    printf("\nName: %s", s.name);
    printf("\nMarks: %.2f\n", s.marks);

    printf("\n1. Update Name");
    printf("\n2. Update Marks");
    printf("\n3. Update Both");
    printf("\n4. Cancel");
    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice!\n");
        clear_buffer();
        fclose(fp);
        return;
    }

    if (choice == 1) {
        printf("Enter New Name: ");
        clear_buffer();
        input_name(new_name);

        if (!valid_name(new_name)) {
            printf("Invalid Name!\n");
            fclose(fp);
            return;
        }

        int i = 0;

        while (new_name[i] != '\0') {
            s.name[i] = new_name[i];
            i++;
        }

        s.name[i] = '\0';

        fseek(fp, -sizeof(s), SEEK_CUR);
        fwrite(&s, sizeof(s), 1, fp);

        printf("Name Updated Successfully!\n");
    }

    else if (choice == 2) {
        printf("Enter New Marks: ");

        if (scanf("%f", &new_marks) != 1) {
            printf("Invalid Marks!\n");
            clear_buffer();
            fclose(fp);
            return;
        }

        s.marks = new_marks;

        fseek(fp, -sizeof(s), SEEK_CUR);
        fwrite(&s, sizeof(s), 1, fp);

        printf("Marks Updated Successfully!\n");
    }

    else if (choice == 3) {
        printf("Enter New Name: ");
        clear_buffer();
        input_name(new_name);

        if (!valid_name(new_name)) {
            printf("Invalid Name!\n");
            fclose(fp);
            return;
        }

        printf("Enter New Marks: ");

        if (scanf("%f", &new_marks) != 1) {
            printf("Invalid Marks!\n");
            clear_buffer();
            fclose(fp);
            return;
        }

        int i = 0;

        while (new_name[i] != '\0') {
            s.name[i] = new_name[i];
            i++;
        }

        s.name[i] = '\0';
        s.marks = new_marks;

        fseek(fp, -sizeof(s), SEEK_CUR);
        fwrite(&s, sizeof(s), 1, fp);

        printf("Record Updated Successfully!\n");
    }

    else if (choice == 4) {
        printf("Update cancelled.\n");
    }

    else {
        printf("Invalid choice!\n");
    }

    fclose(fp);
}
void delete_record() {
    FILE *fp, *temp;
    struct Student s;
    int roll_no;
    int found = 0;
    int attempts = 0;

    while (attempts < 3) {
        fp = fopen("students.txt", "rb");

        if (fp == NULL) {
            printf("No records found!\n");
            return;
        }

        printf("\nEnter Roll No to delete: ");

        if (scanf("%d", &roll_no) != 1) {
            printf("Invalid Roll No!\n");
            clear_buffer();
            fclose(fp);
            attempts++;
            continue;
        }

        clear_buffer();

        if (roll_no <= 0) {
            printf("Roll No must be greater than 0!\n");
            fclose(fp);
            attempts++;
            continue;
        }

        while (fread(&s, sizeof(s), 1, fp) == 1) {
            if (s.roll_no == roll_no) {
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (found)
            break;

        attempts++;

        if (attempts < 3)
            printf("Record Not Found! Try again.\n");
    }

    if (!found) {
        printf("3 wrong attempts. Returning to main menu.\n");
        return;
    }

    fp = fopen("students.txt", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");

        if (fp != NULL)
            fclose(fp);

        if (temp != NULL)
            fclose(temp);

        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll_no != roll_no)
            fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    printf("Record Deleted Successfully!\n");
}

int main() {
    int choice;
    char extra;

    while (1) {
        printf("\n1. Create");
        printf("\n2. Read");
        printf("\n3. Update");
        printf("\n4. Delete");
        printf("\n5. Exit");
        printf("\n\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            clear_buffer();
            continue;
        }

        extra = getchar();

        if (extra != '\n') {
            printf("Invalid choice! Enter only one choice.\n");
            clear_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                read_file();
                break;
            case 3:
                update_file();
                break;
            case 4:
                delete_record();
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}