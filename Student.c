#include "Student.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Student* createStudent(const char* first_name, const char* last_name, const char* phone_number, const int grades[MAX_GRADES]){
    Student* student = (Student*) malloc(sizeof(Student));
    strcpy(student->first_name,first_name);
    strcpy(student->last_name,last_name);
    strcpy(student->phone_number,phone_number);
    memcpy(student->grades,grades,sizeof(int)*MAX_GRADES);
    student->next = NULL;
    return student;
}

void printStudent(Student* student,int grade,int class){
    printf("Grade: %d, Class Number: %d\n",grade+1,class+1 );
    printf("Student Name: %s %s\n", student->first_name,student->last_name);
    printf("Phone Number: %s\n", student->phone_number);
    printf("Exam Grades: ");
    for (int i = 0; i < MAX_GRADES; i++) {
        printf("%d ", student->grades[i]);
    }
    printf("\n\n");

}