#include <stdio.h>
#include <stdlib.h>

struct Student { //Cau truc luu tru thong tin moi sinh vien  
    int id;
    char name[50];
    float gpa;
};
//Ham cho phep nhap thong tin cua sin vien va ghi thong tin nay vao tep du lieu
 
void createStudent(FILE *file) {
    struct Student newStudent;

    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter student GPA: ");
    scanf("%f", &newStudent.gpa);

    fwrite(&newStudent, sizeof(struct Student), 1, file);
    printf("Student added successfully.\n");
}
//Ham cho phep nhap ma sinh vien va hien thi thong tin tu tep du lieu  
void readStudent(FILE *file, int id) {
    struct Student student;

    fseek(file, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        if (student.id == id) {
            printf("Student found:\n");
            printf("ID: %d\nName: %s\nGPA: %.2f\n", student.id, student.name, student.gpa);
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}
//Ham cho phep nhap thong tin va cap nhat thong tin trong tep du lieu  
void updateStudent(FILE *file, int id) {
    struct Student student;

    fseek(file, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        if (student.id == id) {
            printf("Current student information:\n");
            printf("ID: %d\nName: %s\nGPA: %.2f\n", student.id, student.name, student.gpa);

            printf("Enter new student information:\n");
            printf("Enter student name: ");
            scanf("%s", student.name);
            printf("Enter student GPA: ");
            scanf("%f", &student.gpa);

            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&student, sizeof(struct Student), 1, file);
            printf("Student information updated successfully.\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}
//Ham nay cho phep nhap ma so cua sinh vien va xoa thong tin do khoi tep du lieu 
void deleteStudent(FILE *file, int id) {
    struct Student student, emptyStudent = {0, "", 0.0};

    fseek(file, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        if (student.id == id) {
            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&emptyStudent, sizeof(struct Student), 1, file);
            printf("Student with ID %d deleted successfully.\n", id);
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}

int main() {
    FILE *file = fopen("students.dat", "a+");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int choice, id;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Read Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createStudent(file);
                break;
            case 2:
                printf("Enter student ID to read: ");
                scanf("%d", &id);
                readStudent(file, id);
                break;
            case 3:
                printf("Enter student ID to update: ");
                scanf("%d", &id);
                updateStudent(file, id);
                break;
            case 4:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(file, id);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }

    } while (choice != 5);

    fclose(file);

    return 0;
}
