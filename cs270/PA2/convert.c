// PA2 Assignment - convert.h
// Author: Brenton Grundman
// Date:   1/31/2015
// Class:  CS270
// Email:  grundman@colostate.edu

// char2int
// Converts from a character to an integer digit
// if character '0'..'9' convert to 0..9
// else if character 'A'..'F' convert to 10..15
// else convert to -1
int char2int(char digit){
	if(digit == '0'){
		return 0;
	}
	else if(digit == '1'){
		return 1;
	}
else if(digit == '2'){
		return 2;
	}
else if(digit == '3'){
		return 3;
	}
else if(digit == '4'){
		return 4;
	}
else if(digit == '5'){
		return 5;
	}
else if(digit == '6'){
		return 6;
	}
else if(digit == '7'){
		return 7;
	}
else if(digit == '8'){
		return 8;
	}
else if(digit == '9'){
		return 9;
	}
	else if(digit == 'A'){
		return 10;
	}
	else if(digit == 'B'){
		return 11;
	}
	else if(digit == 'C'){
		return 12;
	}
	else if(digit == 'D'){
		return 13;
	}
	else if(digit == 'E'){
		return 14;
	}
	else if(digit == 'F'){
		return 15;
	}
	else{
		return -1;
	}
}
// int2char
// Converts from an integer digit to a character
// if integer 0..9 convert to '0'..'9'
// else if integer 10..15 convert to 'A'..'F'
// else convert to 'X'
char int2char(int digit){
	if(digit == 10){
		return 'A';
	}
	else if(digit == 11){
		return 'B';
	}
	else if(digit == 12){
		return 'C';
	}
	else if(digit == 13){
		return 'D';
	}
	else if(digit == 14){
		return 'E';
	}
	else if(digit == 15){
		return 'F';
	}
	else if(digit == 0){
		return '0';
	}
else if(digit == 1){
		return '1';
	}
else if(digit == 2){
		return '2';
	}
else if(digit == 3){
		return '3';
	}
else if(digit == 4){
		return '4';
	}
else if(digit == 5){
		return '5';
	}
else if(digit == 6){
		return '6';
	}
else if(digit == 7){
		return '7';
	}
else if(digit == 8){
		return '8';
	}
else if(digit == 9){
		return '9';
	}
	else{
		return 'X';
	}
}
// Convert integer to string in specified base and print
// 2 <= base <= 16
void int2ascii(int value, int base){
//base ^ 0..32
// 123 1 3 9 27 81 243
// divide by base
// 41.0 13.6 4.3 1.3 .3
// 06333, divide by base
// 02111, invert
// 11120
//int remain = 0;
//int i = 0;
//char *string = "";
//char[] newNum = new Array[32]
//for(i; i<newNum.length; i++){
//	remain = value%base;
//	int2char(remain);
//	newNum[31-i]= remain;
//	value = value/base;		
//	Arrays.toString(newNum);
}
// Convert string in specified base to integer and print
// 2 <= base <= 16
void ascii2int(char *ascii, int base){
;
}

