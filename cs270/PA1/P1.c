// P1 Assignment
// Author: Brent Grundman
// Date:   8/28/2015
// Class:  CS270
// Email:  grundman@rams.colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool computeSphere(double radius, double *volume)
{
    // Compute volume
    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);

    // Dereference pointer
    *volume = result;

    return true;
}
bool computeCircle(double radius, double *area)
{
  //compute area
  double result = (3.141593 * radius * radius);
  
  //Dereference pointer
  *area = result;
  
  return true;
}
bool computeTriangle(double side, double *area)
{
  //compute area
  double result = (.433013 * side * side);
  
  //Dereference pointer
  *area = result;
  
  return true;
}
bool computeSquare(double side, double *area)
{
  //compute area
  double result = side * side;
  
  //Dereference pointer
  *area = result;
  
  return true;
}
bool computePentagon(double side, double *area)
{
  //compute area
  double result = 1.720477 * side * side;
  
  //dereference pointer
  *area = result;
  
  return true;
}
bool computeHexagon(double side, double *area)
{
  //compute area
  double result = 2.59806 * side * side;
  
  //dereference pointer
  *area = result;
  
  return true;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6)
        printf("usage P1 <double>\n");

    // Parse arguments
    double radius = atof(argv[1]);
    double length1 = atof(argv[2]);
    double length2 = atof(argv[3]);
    double length3 = atof(argv[4]);
    double length4 = atof(argv[5]);
    
    // Local variable
    // double volume;
    double area1;
    double area2;
    double area3;
    double area4;
    double area5;

    // Call function
    //computeSphere(radius, &volume);
    computeCircle(radius, &area1);
    computeTriangle(length1, &area2);
    computeSquare(length2, &area3);
    computePentagon(length3, &area4);
    computeHexagon(length4, &area5);
    
    // Print volume
    //printf("The volume of a sphere with radius %.5f equals %.5f.\n", radius, volume);
    printf("CIRCLE, radius = %.5f, area = %.5f.\n", radius, area1);
    printf("TRIANGLE, length = %.5f, area = %.5f.\n", length1, area2);
    printf("SQUARE, length = %.5f, area = %.5f.\n", length2, area3);
    printf("PENTAGON, length = %.5f, area = %.5f.\n", length3, area4);
    printf("HEXAGON, length = %.5f, area = %.5f.\n", length4, area5);
  
}