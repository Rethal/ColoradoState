/** @file printnum.c
 *  @brief You will modify this file and implement three functions
 *  @details Your implementation of the functions defined in printnum.h.
 * <p>
 * @author <b>Brenton Grundman</b>
 */

#include <stdio.h> // for putchar()

#include "printnum.h"


/** @todo Implement based on documentation contained in printnum.h */
char getDigit (int val) {
	if (val >= 0 && val <= 9)
		return val + '0';
	else
		return val - 10 + 'A';
}

/** @todo Implement based on documentation contained in printnum.h */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
	int q = (numerator / divisor);
	int r = (numerator % divisor);
	*quotient = q;
	*remainder = r;
}

/** @todo Implement based on documentation contained in printnum.h */
void printNum (int x, int base) {
	//32 in base 16: 0010 0000 = 20 so divide by base, then remainder goes in the next one/is divided in the next one
	//340 in base 16: 0001 0101 0100 = 154 r1 = 4, divided by 16 gives 21, r2 = 5, divided by 16 gives 1
	//r2 = 1, divided by 16 gives 0; calls printNum which then exits back to the previous one,
	//which calls char c and putchar (1), then exits which calls getDigit and putchar (5), then exits
	//and calls getDigit and putchar (4), then exits
	
	int quo;
	int rem;

	if (x > 0) {
		divRem(x, base, &quo, &rem);
		char c = getDigit(rem);
		printNum(quo, base);
		putchar(c);
	}
}

