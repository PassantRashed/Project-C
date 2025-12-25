///////////////// made by Passant Rashed & Bassant Hussein \\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

struct Student {
    int student_id;
    char full_name[50];
    int age;
    float total_marks;
    float average;
    char grade;
};


void enter_student_info(struct Student students[], int size);
void display_all_students(struct Student students[], int size);
float calculateAverage(struct Student students);
float calculateClassAverage(struct Student students[], int size);
char assignGrade(struct Student students);
void createOrAppendFile(struct Student students[], int size);
void loadDataFromFile();
void calculateClassStatistics(struct Student students[], int size);
void sortStudents(struct Student students[], int size);
int searchstudent(struct Student students[], int size);
void updateStudent(struct Student* ptr, int size);


int main(void) {
    int choice;
    struct Student students[5];
    int size = 0;

    do {
        printf("==========================================\n");
        printf("    WELCOME TO OUR STUDENT MANAGEMENT SYSTEM :) \n");
        printf("==========================================\n");
        printf("1. ENTER STUDENT DATA\n");
        printf("2. DISPLAY ALL STUDENTS\n");
        printf("3. SEARCH FOR STUDENT\n");
        printf("4. SORT STUDENTS BY MARKS\n");
        printf("5. CALCULATE CLASS STATISTICS\n");
        printf("6. SAVE DATA TO FILE\n");
        printf("7. LOAD DATA FROM FILE\n");
        printf("8. UPDATE STUDENT RECORD\n");
        printf("9. EXIT\n");
        printf("==========================================\n");
        printf("Enter your choice (1-9): ");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (size < 5) {
                printf(">> Enter Student Data \n");
                enter_student_info(&students[size], 1);
                size++;
            }
            else {
                printf("You have reached the limit of 5 students!\n");
            }
            break;

        case 2:
            if (size == 0) {
                printf("No students to show!\n");
            }
            else {
                printf(">> Display All Students \n");
                display_all_students(students, size);
            }
            break;

        case 3:
            printf(">> Search for Student \n");
            if (size == 0) {
                printf("No students to search!\n");
                break;
            }

            int id;

            searchstudent(students, size);
            break;

        case 4:
            printf(">> Sort Students by Marks \n");
            sortStudents(students, size);
            break;

        case 5:
            printf(">> Calculate Class Statistics \n");
            calculateClassStatistics(students, size);
            break;

        case 6:
            if (size > 0) {
                createOrAppendFile(students, size);
                printf("Saved last entry to file.\n");
            }
            else {
                printf("No students to save!\n");
            }
            break;

        case 7:
            printf(">> Load Data from File \n");
            loadDataFromFile();
            break;

        case 8:
            printf(">> Update Student Record \n");
            updateStudent(&students, size);
            break;

        case 9:
            printf("Exiting program...\n");
            printf("Bye :))))))\n");
            break;

        default:
            printf("Invalid choice! Please enter 1–9.\n");
        }

        printf("\n");

    } while (choice != 9);

    return 1;
}

void enter_student_info(struct Student students[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter data for Student %d \n", size);
        printf("Enter Student ID: ");
        scanf("%d", &students[i].student_id);
        printf("Enter Full Name: ");
        getchar();
        fgets(students[i].full_name, sizeof(students[i].full_name), stdin);
        printf("Enter Age (17-25): ");
        scanf("%d", &students[i].age);

        while (students[i].age < 17 || students[i].age > 25) {
            printf("Invalid, age must be between 17 and 25.\n");
            printf("Re-enter Age (17-25): ");
            scanf("%d", &students[i].age);
        }
        printf("Enter Total Marks (0-400): ");
        scanf("%f", &students[i].total_marks);

        while (students[i].total_marks < 0 || students[i].total_marks > 400) {
            printf("Invalid, marks must be between 0 and 400.\n");
            printf("Re-enter Total Marks (0-400): ");
            scanf("%f", &students[i].total_marks);
        }

        students[i].average = calculateAverage(students[i]);
        students[i].grade = assignGrade(students[i]);
    }
}

void display_all_students(struct Student students[], int size) {
    printf("\n===============================================================\n");
    printf("%-6s %-10s %-6s %-10s %-10s %-6s\n",
        "ID", "Name", "Age", "Marks", "Average", "Grade");
    printf("===============================================================\n");

    for (int i = 0; i < size; i++) {
        printf("%-6d %-20s %-6d %-10.2f %-10.2f %-6c\n",
            students[i].student_id,
            students[i].full_name,
            students[i].age,
            students[i].total_marks,
            students[i].average,
            students[i].grade);
    }

    printf("===============================================================\n");
    printf("Number of students = %d\n", size);
}


float calculateAverage(struct Student student) {
    return student.total_marks / 4.0;
}

float calculateClassAverage(struct Student students[], int size) {
    float sum = 0;

    for (int i = 0; i < size; i++) {
        sum += students[i].total_marks;
    }
    return sum / size;
}

char assignGrade(struct Student student) {
    if (student.average >= 90)
        student.grade = 'A';
    else if (student.average >= 80)
        student.grade = 'B';
    else if (student.average >= 70)
        student.grade = 'C';
    else if (student.average >= 60)
        student.grade = 'D';
    else
        student.grade = 'F';

    return student.grade;
}

void createOrAppendFile(struct Student students[], int size) {
    FILE* fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "ID : %d, Full Name : %s, Age: %d, Total Marks : %.2f, Average : %.2f, Grade : %c\n",
            students[i].student_id,
            students[i].full_name,
            students[i].age,
            students[i].total_marks,
            students[i].average,
            students[i].grade);
    }

    fclose(fp);
    printf("All student data saved to File (students.txt) Successfully\n");
}

void loadDataFromFile() {
    FILE* fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }
    char line[200];
    printf("Student Records from File:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}

void sortStudents(struct Student students[], int size) {
    printf("students before sorting : \n");
    printf(" ------------------------- \n");
    display_all_students(students, size);

    for (int i = 0; i < size; i++) {
        int flag = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (students[j].total_marks < students[j + 1].total_marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                flag = 1;
            }
        }
        printf("pass number %d\n", i);
        printf(" ------------------------- \n");
        for (int k = 0; k < size; k++) {
            printf("%s - %.2f\n", students[k].full_name, students[k].total_marks);
        }
        if (flag == 0) {
            break;
        }
    }
    printf("students after sorting : \n");
    printf(" ------------------------- \n");
    display_all_students(students, size);
}

void calculateClassStatistics(struct Student students[], int size) {
    if (size == 0) {
        printf("No data available!\n");
        return;
    }

    printf("\n=== CLASS STATISTICS ===\n");

    float classAvg = calculateClassAverage(students, size);
    printf("Number of Students: %d\n", size);
    printf("Class Average Marks: %.2f\n\n", classAvg);

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (students[j].total_marks < students[j + 1].total_marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Top Performer:\n");
    printf("ID: %d\n Name: %s\n Total Marks: %.2f\n Average: %.2f\n Grade: %c\n\n",
        students[0].student_id,
        students[0].full_name,
        students[0].total_marks,
        students[0].average,
        students[0].grade);

    if (students[size - 1].grade == 'F') {
        printf("Needs Improvement:\n");
        printf("ID: %d\n Name: %s\n Total Marks: %.2f\n Average: %.2f\n Grade: %c\n\n",
            students[size - 1].student_id,
            students[size - 1].full_name,
            students[size - 1].total_marks,
            students[size - 1].average,
            students[size - 1].grade);
    }
    else {
        printf("No student needs improvement!\n\n");
    }

    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;

    for (int i = 0; i < size; i++) {
        switch (students[i].grade) {
        case 'A': countA++; break;
        case 'B': countB++; break;
        case 'C': countC++; break;
        case 'D': countD++; break;
        case 'F': countF++; break;
        }
    }

    printf("---- GRADE DISTRIBUTION ----\n");
    printf("A: %d students\n", countA);
    printf("B: %d students\n", countB);
    printf("C: %d students\n", countC);
    printf("D: %d students\n", countD);
    printf("F: %d students\n\n", countF);

    printf("Press Enter to continue...");
    getchar();
    getchar();
}

int searchstudent(struct Student students[], int size)
{
    int id;
    printf("pleasr enter the ID of the student ");
    scanf("%d", &id);
    bool found = false;
    for (int i = 0; i < size; i++)
    {
        if (students[i].student_id == id)
        {
            printf("student found at index:\n ");
            printf("%d", i);
            found = true;
        }
        /*else
        {
            printf("student not found :( ");
            printf("%d", -1);
            break;
        }*/

    }
    if (found == false)
    {
        printf("student not found :( ");
        printf("%d", -1);

    }


}
void updateStudent(struct Student* ptr, int size)
{
    int id;
    printf("pleasr enter the ID of the student ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++)
    {
        if (ptr[i].student_id == id)
        {
            printf("student is found :) \n ");
            printf("please spicify what you want to edit \n  ");
            printf("1. age\n");
            printf("2. total marks\n ");
            printf("3. to exit the update\n  ");
            int choice, new_age, marks;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:

                printf("enter the updated age: ");
                scanf("%d", &new_age);
                (ptr + i)->age = new_age;
                printf("age updated :) ");
                break;
            case 2:
                printf("enter the updated total marks: ");
                scanf("%d", &marks);
                (ptr + i)->total_marks = marks;
                printf("total marks updated :) ");
                break;
            case 3:
                printf("exit update ^-^ ");
                break;
            default:
                printf("Invalid choice! Please enter 1–3.\n");
            }
        }
    }


}
///////////////// made by Passant Rashed & Bassant Hussein \\\\\\\\\\\\\\\\\\\\\
