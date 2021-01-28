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
    printf("Average Homework Score: ");
    scanf("%d", &student->hw);
    printf("Average Lab Grade: ");
    scanf("%d", &student->lab);
    printf("Midterm Grade: ");
    scanf("%d", &student->midterm);
    printf("Final Exam Grade: ");
    scanf("%d", &student->finex);
}

// Output scores
void outputScores(Student student)
{
    printf("First name: %s\n", student.firstName);
printf("Last name: %s\n", student.lastName);
printf("Average Homework Score: %d\n", student.hw);
printf("Average Lab Grade: %d\n", student.lab);
printf("Midterm Grade: %d\n", student.midterm);
printf("Final Exam Grade: %d\n", student.finex);
student.totalPoints = student.hw*0.30 + student.lab*0.20 + student.midterm*0.20 + student.finex*0.30;
	    if (student.totalPoints > 90.0) student.finalGrade = 'A';
	    else if (student.totalPoints > 80.0) student.finalGrade = 'B';
	    else if (student.totalPoints > 70.0) student.finalGrade = 'C';
	    else if (student.totalPoints > 60.0) student.finalGrade = 'D';
	    else student.finalGrade = 'F';
printf("Total Score: %f\n", student.totalPoints);
printf("Letter Grade: %c\n", student.finalGrade);
}
