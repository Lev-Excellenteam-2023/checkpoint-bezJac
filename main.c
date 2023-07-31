#include <stdio.h>
#include "School.h"

#define FILE_PATH "/home/bezjac/Downloads/students_with_class.txt"
int main()
{
    School school = createSchool(FILE_PATH);
    printStudents(&school);
    freeAllStudents(&school);
}
