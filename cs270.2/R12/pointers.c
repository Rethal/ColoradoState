// File:        pointers.c
// Description: Program to teach C pointers
// Author:      Chris Wilcox
// Date:        9/29/2010

// Include files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void exercise1();
void exercise2();
void exercise3();
void exercise4();
void exercise5();

// Global data
int globalInteger;
float globalFloat;
char globalChar;
char *globalString = "gh";
int globalArray[4];
int *globalPointer = &globalString;

// Function:     main
// Description:  entry point  
int main(int argc, char *argv[])
{
    bool bContinue = true;
    while (bContinue)
    {
        // Display menu
        printf("\n");
        printf("1) Exercise 1, Pointer Basics\n"); 
        printf("2) Exercise 2, Pointer Arguments\n"); 
        printf("3) Exercise 3, Arrays and Pointers\n"); 
        printf("4) Exercise 4, Strings and Pointers\n"); 
        printf("5) Exercise 5, Static versus Dynamic\n"); 
        printf("Enter Number: ");

        // Get selection
        int iSelection;
        scanf("%d", &iSelection);
        printf("\n");
    
        // Run exercise
        switch (iSelection)
        {
            case 1: exercise1(); break;
            case 2: exercise2(); break;
            case 3: exercise3(); break;
            case 4: exercise4(); break;
            case 5: exercise5(); break;
            default: bContinue = false;
        }
    }

    return 0;
}

// Exercise 1, Pointer Basics
void exercise1()
{
    printf("Exercise 1\n");

    // Variables
    int localInteger = 12345678;
    float localFloat = 0.113355;
    char localChar   = '&';

    // Pointers
    int *pInteger = &localInteger;
    float *pFloat = &localFloat;
    char *pChar = &localChar;

    // Print variables and pointers
    printf("localInteger: value = %d, address = %p\n", localInteger, pInteger); 
    printf("localFloat:   value = %f, address = %p\n", localFloat, pFloat); 
    printf("localChar:    value = %c, address = %p\n", localChar, pChar);
    
    // Print the pointer and the address of the variable
    // FILL IN CODE HERE!
	printf("localInteger: pointer = %p, address = %p\n", pInteger,&localInteger);
	printf("localFloat:   pointer = %p, address = %p\n", pFloat,&localFloat);
	printf("localChar:    pointer = %p, address = %p\n", pChar,&localChar);
    // Use the pointer to change the value of each variable
    // FILL IN CODE HERE!
	*pInteger = 17;
	*pFloat = 0.25;
	*pChar = 'B';
    // Print variables and pointers
    printf("localInteger: value = %d\n", localInteger); 
    printf("localFloat:   value = %f\n", localFloat);
    printf("localChar:    value = %c\n", localChar);
}

// Exercise 2, Pointer Arguments
void passByValue(int i, float f, char c)
{
    i = 87654321; 
    f = 0.224466; 
    c = '#';

    printf("passbyValue: i = %d\n", i); 
    printf("passbyValue: f = %f\n", f); 
    printf("passbyValue: c = %c\n", c); 
}

void passByReference(int *i, float *f, char *c)
{
    *i = 87654321; 
    *f = 0.224466; 
    *c = '#';

    printf("passbyReference: i = %d\n", *i); 
    printf("passbyReference: f = %f\n", *f); 
    printf("passbyReference: c = %c\n", *c); 
}

void exercise2()
{
    printf("Exercise 2\n");

    // Variables
    int localInteger = 12345678;
    float localFloat = 0.113355;
    char localChar   = '&';

    // Print the local variables
    printf("localInteger: value = %d\n", localInteger); 
    printf("localFloat:   value = %f\n", localFloat);
    printf("localChar:    value = %c\n", localChar);

    // Call passByValue with locals
    // FILL IN CODE HERE!
    passByValue(localInteger,localFloat,localChar);

    // Print the local variables
    printf("localInteger: value = %d\n", localInteger); 
    printf("localFloat:   value = %f\n", localFloat);
    printf("localChar:    value = %c\n", localChar);

    // Call passByReference with addresses of locals
    // FILL IN CODE HERE!
    passByReference(&localInteger,&localFloat,&localChar);
   
    // Print the local variables
    printf("localInteger: value = %d\n", localInteger); 
    printf("localFloat:   value = %f\n", localFloat);
    printf("localChar:    value = %c\n", localChar);
}

// Exercise 3, Arrays and Pointers
void exercise3()
{
    printf("Exercise 3\n");

    // Static allocation
    int intArray[4];
    intArray[0] = 1234;
    intArray[1] = 2345;
    intArray[2] = 3456;
    intArray[3] = 4567;

    // Dynamic allocation
    int *intPointer = malloc(4*sizeof(int));
    *(intPointer+0) = 6543;
    *(intPointer+1) = 5432;
    *(intPointer+2) = 4321;
    *(intPointer+3) = 3210;

    // Access and print static array, using pointer access, e.g. *(intArray+0) 
    // FILL IN CODE HERE!
	for(int i = 0;i<4;i++){
	  printf("intArray[%d] = %d\n",i,*(intArray+i));
	}
    // Access and print dynamic array, using array notation, e.g. intPointer[0]
    // FILL IN CODE HERE!
	for(int i = 0;i<4;i++){
	  printf("intArray[%d] = %d\n",i,intPointer[i]);
	}
    // Free allocated memory
    // FILL IN CODE HERE!
    free(intPointer);
}

// Exercise 4, Strings and Pointers
void exercise4()
{
    printf("Exercise 4\n");

    char *string0   = "String0";
    char string1[8] = "String1"; // don't forget the null termination
    char *string2   = malloc(8*sizeof(char));
    strcpy(string2, "String2");
    
    // Add code to print out these strings using %s and the name
    // FILL IN CODE HERE!
    printf("%s\n",string0);
    printf("%s\n",string1);
    printf("%s\n",string2);

    // Add code to print out the sixth character using %c and array access, e.g. string1[6]
    // FILL IN CODE HERE!
    printf("%c\n",*(string0+6));
    printf("%c\n",string1[6]);
    printf("%c\n",string2[6]);
    free(string2);
}

// Exercise 5, Static versus Dynamic
void exercise5()
{
    printf("Exercise 5\n");

    // Static allocation
    int intArray[4];
    float floatArray[4];
    char charArray[4];

    // Dynamic allocation
    int *intPointer = malloc(4*sizeof(int));
    float *floatPointer = malloc(4*sizeof(float));
    char *charPointer = malloc(4*sizeof(char));
    
    // Add code to display pointers to the static arrays
    // FILL IN CODE HERE!
    printf("intArray = %p\n",intArray);
    printf("floatArray = %p\n",floatArray);
    printf("charArray = %p\n",charArray);
            
    // Add code to display pointers to the dynamic arrays
    // FILL IN CODE HERE!
    printf("intPointer = %p\n",intPointer);
    printf("floatPointer = %p\n",floatPointer);
    printf("charPointer = %p\n",charPointer);

    // Add code to display pointers to global variables
    // FILL IN CODE HERE!
    printf("globalInteger = %p\n",&globalInteger);
    printf("globalFloat = %p\n",&globalFloat);
    printf("globalChar = %p\n",&globalChar);
    printf("globalString = %p\n",globalString);
    printf("globalArray = %p\n",&globalArray[4]);
    printf("globalPointer = %p\n",globalPointer);

    // Add code to display pointers to functions in this module!
    // FILL IN CODE HERE!
    printf("exercise1 = %p\n",&exercise1);
    printf("exercise2 = %p\n",&exercise2);
    printf("exercise3 = %p\n",&exercise3);
    printf("exercise4 = %p\n",&exercise4);
    printf("exercise5 = %p\n",&exercise5);
    
    free(intPointer);
    free(floatPointer);
    free(charPointer);
}
