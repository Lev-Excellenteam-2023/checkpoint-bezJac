#define MAX_GRADES 10
#define MAX_NAME_LENGTH 50
#define PHONE_NUMBER_LENGTH 11
#include <stdio.h>

typedef struct Student {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char phone_number[PHONE_NUMBER_LENGTH];
    int grades[MAX_GRADES];
    struct Student* next;
} Student;


Student* createStudent(const char* first_name, const char* last_name, const char* phone_number, const int grades[]);
void printStudent(FILE* stream,Student* student, int grade,int class);
int calculateAverage(Student* student);