#include "School.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};



enum SchoolSubjects {
    ENGLISH,
    MATH,
    SCIENCE,
    HISTORY,
    GEOGRAPHY,
    COMPUTER_SCIENCE,
    PHYSICAL_EDUCATION,
    ART,
    MUSIC,
    FOREIGN_LANGUAGE
};


void subjectMenu() {
     printf("Select a subject:\n");
    printf("1. English\n");
    printf("2. Math\n");
    printf("3. Science\n");
    printf("4. History\n");
    printf("5. Geography\n");
    printf("6. Computer Science\n");
    printf("7. Physical Education\n");
    printf("8. Art\n");
    printf("9. Music\n");
    printf("10. Foreign Language\n");
}

int findMinIndex(Student *top_students[10], int subject, int evaluated_grade) {
    int min = 101;
    int index;
    for (int i = 0; i < 10; ++i) {
        if (top_students[i]->grades[subject - 1] < min) {
            min = top_students[i]->grades[subject - 1];
            index = i;
        }
    }
    if (evaluated_grade > top_students[index]->grades[subject - 1])
        return index;
    else
        return -1;
}

void insertNewStudent(School *school) {
    char first_name[50], last_name[50], phone_number[11];
    int grade, class, exam_grades[10];
    printf("\nEnter Student's first name: ");
    while (scanf("%s", first_name) != 1) {
        printf("\nInvalid input.  ");
        while (getchar() != '\n');
    }

    printf("\nEnter Student's last name: ");
    while (scanf("%s", last_name) != 1) {
        printf("\nInvalid input. ");
        while (getchar() != '\n');
    }

    printf("\nEnter Student's phone number: ");
    while (scanf("%s", phone_number) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    printf("\nEnter Student's grade: ");
    while (scanf("%d", &grade) != 1 || grade < 1 || grade > 12) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    printf("\nEnter Student's class: ");
    while (scanf("%d", &class) != 1 || class < 1 || class > 10) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < 10; i++) {
        printf("Enter grade %d: ", i + 1);
        while (scanf("%d", &exam_grades[i]) != 1 || exam_grades[i] < 0 || exam_grades[i] > 100) {
            printf("Invalid input. Please enter a valid grade.\n");
            while (getchar() != '\n');
        }
    }
    Student *new_student = createStudent(first_name, last_name, phone_number, exam_grades);
    new_student->next = school->school[grade - 1][class - 1];
    school->school[grade - 1][class - 1] = new_student;
    //TODO compare to see if student is in database already
}

void deleteStudent(School *school) {
    char first_name[50];
    char last_name[50];
    printf("\nEnter Student's first name: ");
    while (scanf("%s", first_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    printf("\nEnter Student's last name: ");
    while (scanf("%s", last_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            Student *current_student = school->school[i][j];
            Student *previous_student = NULL;
            while (current_student != NULL) {
                if (strcmp(current_student->first_name, first_name) == 0 && strcmp(current_student->last_name, last_name) == 0) 
                {
                    if (previous_student == NULL) {
                        school->school[i][j] = school->school[i][j]->next;
                    } else {
                        previous_student->next = current_student->next;
                    }
                    free(current_student);
                    return;
                }
                previous_student = current_student;
                current_student = current_student->next;
            }
        }
    }

}

void editStudentGrade(School *school) {
    char first_name[50];
    char last_name[50];
    printf("\nEnter Student's first name: ");
    while (scanf("%s", first_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    printf("\nEnter Student's last name: ");
    while (scanf("%s", last_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    Student *student = findStudent(school, first_name, last_name);
    if (student == NULL) {
        printf("No student matches input details");
        return;
    }
    subjectMenu();

    int choice;
    int grade;
    printf("Enter your choice: ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 10) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    printf("\nEnter Student's updated grade: ");
    while (scanf("%d", &grade) != 1 || grade < 0 || grade > 100) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    student->grades[choice - 1] = grade;
}

void searchStudent(School *school) {

    char first_name[50];
    char last_name[50];
    printf("\nEnter Student's first name: ");
    while (scanf("%s", first_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    printf("\nEnter Student's last name: ");
    while (scanf("%s", last_name) != 1) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            Student *current = school->school[i][j];
            while (current != NULL) {
                if (strcmp(first_name, current->first_name) == 0 && strcmp(last_name, current->last_name) == 0) {
                    printStudent(stdout, current, i, j);
                    return;
                }
                current = current->next;
            }
        }
    }
    printf("No student matches input details");
}

void printAllStudents(School *school, FILE *stream) {
    printStudents(stream, school);
}

void printTopNStudentsPerCourse(School *school) {

    Student *top_students[10] = {NULL};
    int top_students_class_num[10];
    int choice;
    int grade;
    int min_grade_index;
    printf("\nEnter grade: ");
    while (scanf("%d", &grade) != 1 || grade < 1 || grade > 12) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    subjectMenu();
    printf("Enter your choice: ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 10) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    int initialize_index =0;
    for (int i = 0; i < NUM_OF_CLASSES; ++i) {
        Student *current = school->school[grade - 1][i];
        
        
            while (current != NULL) {
                if(initialize_index<10)
                {
                     top_students[initialize_index] = current;
                    top_students_class_num[initialize_index] = i;
                    initialize_index++;
                    
                }
                else{
                    min_grade_index = findMinIndex(top_students, choice, current->grades[choice - 1]);
                    if (min_grade_index != -1) {
                        top_students[min_grade_index] = current;
                        top_students_class_num[min_grade_index] = i;

                    }
                    
                }
                current = current->next;
            }
        
    }

    for (int i = 0; i < 10; ++i) {
        printStudent(stdout, top_students[i], grade - 1, top_students_class_num[i]);
    }


}

void printUnderperformedStudents(School *school) {
    for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            Student *current = school->school[i][j];
            while (current != NULL) {

                if (calculateAverage(current) < 55) {
                    printStudent(stdout, current, i, j);
                }
                current = current->next;
            }
        }
    }
}

void printAverage(School *school) {
    int choice;
    int grade;
    printf("\nEnter grade: ");
    while (scanf("%d", &grade) != 1 || grade < 1 || grade > 12) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    subjectMenu();
    printf("Enter your choice: ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 10) {
        printf("\nInvalid input. Please enter a valid first name: ");
        while (getchar() != '\n');
    }
    int grades = 0;
    int num_of_students = 0;
    for (int j = 0; j < NUM_OF_CLASSES; ++j) {
        Student *current = school->school[grade-1][j];
        while (current != NULL) {
            grades += current->grades[choice-1];
            num_of_students+=1;
            current = current->next;
        }
    }
    printf("%d",grades/num_of_students);

}

void exportDatabase(School *school) {
    char* filename = "/home/bezjac/Downloads/db_export.txt";
    FILE* file = fopen(filename,"w");
    printAllStudents(school,file);
    fclose(file);
}

void handleClosing(School *school) {
    freeAllStudents(school);
}


void menu() {
    School school = createSchool("/home/bezjac/test_stage2/students_with_class.txt");
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
            case Insert:
                insertNewStudent(&school);
                break;
            case Delete:
                deleteStudent(&school);
                break;
            case Edit:
                editStudentGrade(&school);
                break;
            case Search:
                searchStudent(&school);
                break;
            case Showall:
                printAllStudents(&school,stdout);
                break;
            case Top10:
                printTopNStudentsPerCourse(&school);
                break;
            case UnderperformedStudents:
                printUnderperformedStudents(&school);
                break;
            case Average:
                printAverage(&school);
                break;
            case Export:
                exportDatabase(&school);
                break;
            case Exit:
                handleClosing(&school);
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                       input);
                getc(stdin);
                getc(stdin);
                break;
        }
    } while (input != Exit);
}

int main() {

    menu();
    return 0;
}

