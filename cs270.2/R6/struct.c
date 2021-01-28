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
    printf("Average Homeworks: ");
    scanf("%d", &student->homework);
    printf("Average Labs: ");
    scanf("%d", &student->lab);
    printf("Midterm: ");
    scanf("%d", &student->midterm);
    printf("Final: ");
    scanf("%d", &student->finalgrade);
}

// Output scores
void outputScores(Student student)
{
    printf("First name: %s\n", student.firstName);
    printf("Last name: %s\n", student.lastName);
    printf("Avg Homework: %d\n", student.homework);
    printf("Avg Labs: %d\n", student.lab);
    printf("Midterm: %d\n", student.midterm);
    printf("Final: %d\n", student.finalgrade);
    printf("Total Grade: %f\n", student.totalPoints);
    printf("Letter Grade: %c\n", student.letterGrade);
}

void calculateScores(Student *student)
{
  student->totalPoints = (student->homework * 0.30) + (student->lab * 0.20) +(student->midterm * 0.20) + 
  (student->finalgrade * 0.30);
  if (student->totalPoints > 90.0) student->letterGrade = 'A';
  else if (student->totalPoints > 80.0) student->letterGrade = 'B';
  else if (student->totalPoints > 70.0) student->letterGrade = 'C';
  else if (student->totalPoints > 60.0) student->letterGrade = 'D';
  else student->letterGrade = 'F';
  
}