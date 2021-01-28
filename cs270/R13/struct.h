// File: struct.h

// Structure definition
typedef struct
{
    char firstName[80];
    char lastName[80];
} Student;

// Function Declarations 
void inputScores(Student *student);
void outputScores(Student student);
