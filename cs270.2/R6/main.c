// File:        main.c
// Description: ... fill this in
// Author:      ... fill this in
// Date:        ... fill this in

// Include files
#include <stdio.h>
#include "struct.h"

// Function:     main
// Description:  entry point  
  Student student[5];

int main()
{
    for(int i=0;i<5;i++){
      
    inputScores(&student[i]);
    }
    for(int i=0;i<5;i++){
          calculateScores(&student[i]);
          outputScores(student[i]);
    }
    return 0;
    
}

