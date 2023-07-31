#include "Student.h"

#define NUM_OF_LEVELS 12
#define NUM_OF_CLASSES 10

typedef struct {
    Student* school[NUM_OF_LEVELS][NUM_OF_CLASSES];
} School;

School createSchool(char* file_path);
void printStudents(School* school);
void freeAllStudents(School* school);
