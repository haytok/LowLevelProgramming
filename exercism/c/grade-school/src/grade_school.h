#ifndef GRADE_SCHOOL_H
#define GRADE_SCHOOL_H

#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 20
#define MAX_STUDENTS 20

typedef struct {
   uint8_t grade;
   char *name;
} student_t;

typedef struct {
   size_t count;
   student_t students[MAX_STUDENTS];
} roster_t;

roster_t get_roster();
void clear_roster();
roster_t get_grade(uint8_t desired_grade);
bool add_student(char *name, uint8_t grade);

void sort_item(roster_t *ans, int j);
void sort_by_name(roster_t *roster);
void sort_by_grade(roster_t *roster);

#endif
