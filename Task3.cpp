#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float gpa;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("student_data.dat", "ab"); // Append binary
    if (!fp) { printf("File error.\n"); return; }

    printf("\nEnter ID: "); scanf("%d", &s.id);
    printf("\nEnter Name: "); scanf(" %[^\n]", s.name); // Read string with spaces
    printf("\nEnter GPA: "); scanf("%f", &s.gpa);

    fwrite(&s, sizeof(struct Student), 1, fp);
    printf("\nStudent added successfully.\n\n");
    printf("--------------------------------\n");
fclose(fp);
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("student_data.dat", "rb");
    if (!fp) { printf("No data found.\n"); return; }

    printf("\n\n    Student Records    \n\n");
	printf("--------------------------------\n");
    printf("ID\tName\t\tGPA\n");
    printf("--------------------------------\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%d\t%-15s\t%.2f\n", s.id, s.name, s.gpa);
    }
        printf("--------------------------------\n\n\n");

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int id, found = 0;
    FILE *fp = fopen("student_data.dat", "rb");
    if (!fp) { printf("No data found.\n"); return; }     printf("\n--------------------------------");

    printf("\nEnter ID to search: "); scanf("%d", &id);
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == id) {
            printf("\nFound: ID: %d, Name: %s, GPA: %.2f\n", s.id, s.name, s.gpa);
             printf("\n--------------------------------\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("\nStudent not found.\n");
     printf("\n--------------------------------\n");
    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    int id, found = 0;
    FILE *fp = fopen("student_data.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp) { printf("\nNo data found.\n"); return; }

    printf("\n\nEnter ID to delete: "); scanf("%d", &id);
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == id) {
            found = 1; // Skip writing this student (effectively deleting)
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("student_data.dat");
    rename("temp.dat", "student_data.dat");

    if (found) printf("\nStudent record deleted.\n");
    else printf("\nStudent ID not found.\n");
}

void updateStudent() {
    struct Student s;
    int id, found = 0;
    FILE *fp = fopen("student_data.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp) { printf("No data found.\n"); return; }

    printf("\nEnter ID to update: "); scanf("%d", &id);
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == id) {
            printf("\n\nEnter New Name: "); scanf(" %[^\n]", s.name);
            printf("\n\nEnter New GPA: "); scanf("%f", &s.gpa);
            found = 1;
        }
        fwrite(&s, sizeof(struct Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove("student_data.dat");
    rename("temp.dat", "student_data.dat");

    if (found) printf("\nStudent record updated.\n");
    else printf("\nStudent ID not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Add Student\n2. Display Records\n3. Search\n4. Delete\n5. Update\n6. Exit\n\nChoice: ");
        scanf("%d", &choice);
        printf("      #\n      #\n      #\n      #");
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
