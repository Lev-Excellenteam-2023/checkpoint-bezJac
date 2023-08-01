#include "Student.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Student* createStudent(const char* first_name, const char* last_name, const char* phone_number, const int grades[10]){
    Student* student = (Student*) malloc(sizeof(Student));
    strcpy(student->first_name,first_name);
    strcpy(student->last_name,last_name);
    strcpy(student->phone_number,phone_number);
    memcpy(student->grades,grades,sizeof(int)*10);
    student->next = NULL;
    return student;
}

void printStudent(FILE* stream,Student* student,int grade,int class){
    fprintf(stream,"Grade: %d, Class Number: %d\n",grade+1,class+1 );
    fprintf(stream,"Student Name: %s %s\n", student->first_name,student->last_name);
    fprintf(stream,"Phone Number: %s\n", student->phone_number);
    fprintf(stream,"Exam Grades: ");
    for (int i = 0; i < 10; i++) {
        fprintf(stream,"%d ", student->grades[i]);
    }
    printf("\n\n");

}

int calculateAverage(Student* student)
{
    int sum=0;
    for (int i = 0; i < MAX_GRADES; ++i) {
        sum+=student->grades[i];
    }
    return sum/MAX_GRADES;
}