#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"
#define MAX_NAME_LENGTH 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
} Employee;

void addEmployee(FILE *file) {
    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fseek(file, 0, SEEK_END);
    fwrite(&emp, sizeof(Employee), 1, file);
    printf("Employee added successfully.\n");
}

void viewEmployees(FILE *file) {
    Employee emp;
    fseek(file, 0, SEEK_SET);
    printf("\nEmployee Details:\n");
    while (fread(&emp, sizeof(Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}

void updateEmployee(FILE *file) {
    int id, found = 0;
    Employee emp;

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    fseek(file, 0, SEEK_SET);
    while (fread(&emp, sizeof(Employee), 1, file) == 1) {
        if (emp.id == id) {
            printf("Enter new name: ");
            scanf("%s", emp.name);
            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, file);
            found = 1;
            printf("Employee details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

int main() {
    FILE *file;
    int choice;

    file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        file = fopen(FILENAME, "wb+");
        if (file == NULL) {
            perror("Unable to open file");
            exit(1);
        }
    }

    while (1) {
        printf("\n1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Update Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                viewEmployees(file);
                break;
            case 3:
                updateEmployee(file);
                break;
            case 4:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
