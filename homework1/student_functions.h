//
// Created by jnalo on 2/24/2020.
//

#ifndef CLASS_PRACTICE_STUDENT_FUNCTIONS_H
#define CLASS_PRACTICE_STUDENT_FUNCTIONS_H

#endif //CLASS_PRACTICE_STUDENT_FUNCTIONS_H
#include <stdbool.h>

const int MAX = 50;
typedef struct Student{
    char name[50];
    struct Student *next, *prev;

} Student;

Student *insert_student(Student *node, char *name, char *prev_name);
int delete_student(Student *node, char *name);
Student *search_list(Student *node, char *name);
void swap(Student *node1, Student *node2);
void free_list(Student *node);
bool isEmpty();
Student *create_Student(char *name);
void print_list(Student *head);