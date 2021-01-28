// File:        main.c
// Description: ... fill this in
// Author:      ... fill this in
// Date:        ... fill this in

// Include files
#include <stdio.h>
#include "struct.h"

// Function:     main
// Description:  entry point  
int main()
{
  //  Student student;

    Student student[5];
	for(int i=0;i<1;i++){
		inputScores(&student[i]);
}
	for(int i=0;i<1;i++){
		outputScores(student[i]);
}    
//inputScores(&student);
//    outputScores(student);

    return 0;
}
