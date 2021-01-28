// File: struct.h

// Structure definition
typedef struct
{
    char firstName[80];
    char lastName[80];
    int hw;
    int lab;
    int midterm;
    int finex;
float totalPoints;
char finalGrade;
} Student;

// Function Declarations 
void inputScores(Student *student);
void outputScores(Student student);
void calculateScores(Student *student);

	 
