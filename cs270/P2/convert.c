#include<string.h>
#include <stdio.h>
// PA2 Assignment - convert.c
// Author: Brent Grundman
// Date:   9/5/2015
// Class:  CS270
// Email:  grundman@rams.colostate.edu

// char2int
// Converts from a character to an integer digit
// if character '0'..'9' convert to 0..9
// else if character 'A'..'F' convert to 10..15
// else convert to -1
int char2int(char digit){
  if(digit=='A'){
    return 10;
  }
  if(digit=='B'){
    return 11;
  }
  if(digit=='C'){
    return 12;
  }
  if(digit=='D'){
    return 13;
  }
  if(digit=='E'){
    return 14;
  }
  if(digit=='F'){
    return 15;
  }
  else if(digit=='0'||digit=='1'||digit=='2'||digit=='3'||digit=='4'||digit=='5'||digit=='6'||digit=='7'||digit=='8'||digit=='9'){
  return digit-'0';
  }
  else return -1;
}

// int2char
// Converts from an integer digit to a character
// if integer 0..9 convert to '0'..'9'
// else if integer 10..15 convert to 'A'..'F'
// else convert to 'X'
char int2char(int digit){
  if(digit>=0 && digit <=9){
    return '0'+digit;
  }
  else if(digit>=10 && digit <=15){
    return 'A'+(digit-10);
  }
 else return 'X';
}

// Convert integer to string in specified base and print
// 2 <= base <= 16
void int2ascii(int value, int base){
  
  char hexa[255], *loc = hexa+sizeof(hexa)-1;
  *loc='\0';
  do{
    *--loc = int2char(value%base);
  }
  while (value/=base);
  printf("%s",loc);
}

// Convert string in specified base to integer and print
// 2 <= base <= 16
void ascii2int(char *ascii, int base){
  int result = 0;
  // Iterate characters
  int length = strlen(ascii);
  for(int index=0; index<length; index++){
    result = result*base + char2int(*ascii);
  }
  printf("%d",result);
}

