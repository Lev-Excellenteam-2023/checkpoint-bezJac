#include "School.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void loadStudent(School *school, char *line) {
    char first_name[50];
    char last_name[50];
    char phone_number[11];
    int grades[10]={0};
    int level;
    int class;

    sscanf(line, "%s %s %s %d %d %d %d %d %d %d %d %d %d %d %d",
           first_name, last_name, phone_number, &level, &class,
           &grades[0], &grades[1], &grades[2], &grades[3], &grades[4],
           &grades[5], &grades[6], &grades[7], &grades[8], &grades[9]);
    if (school->school[level-1][class-1] == NULL) {
        school->school[level-1][class-1] = createStudent(first_name, last_name, phone_number, grades);
    } else {
        Student *new_student = createStudent(first_name, last_name, phone_number, grades);
        new_student->next = school->school[level-1][class-1];
        school->school[level-1][class-1] = new_student;
    }


}

School createSchool(char *file_path) {

    School tempSchool;
    for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            tempSchool.school[i][j] = NULL;
        }
    }
    FILE *input_file = fopen(file_path, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), input_file) && strcmp(buffer, "\n") != 0) {
        loadStudent(&tempSchool, buffer);

    }
    fclose(input_file);
    return tempSchool;
}

void printStudents(School* school) {
    for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            Student *current = school->school[i][j];
            while (current != NULL) {
                printStudent(current, i, j);
                current = current->next;
            }
        }
    }
}

void freeAllStudents(School* school){
	 for (int i = 0; i < NUM_OF_LEVELS; ++i) {
        for (int j = 0; j < NUM_OF_CLASSES; ++j) {
            Student* place_holder = school->school[i][j];
			Student* deleter;
            while (place_holder != NULL) {
                deleter = place_holder;
				place_holder = place_holder->next;
                free(deleter);
            }
        }
    }
}
