// File: struct.c

// Include files
#include <stdio.h>
#include "struct.h"

// Input scores
void inputScores(Student *student)
{
    printf("First name: ");
    scanf("%s", student->firstName);
    printf("Last name: ");
    scanf("%s", student->lastName);
}

// Output scores
void outputScores(Student student)
{
    printf("First name: %s\n", student.firstName);
}
