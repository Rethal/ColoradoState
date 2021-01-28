#include "flt32.h"
#include <stdio.h>

/** @file flt32.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in flt32.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Brent Grundman</b> goes here
 */

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int signmask = 0x80000000;
int expmask = 0x7F800000;
int manmask = 0x007FFFFF;
int implOne = 0x00800000;

int flt32_get_sign (flt32 x) {
	if (x & signmask)
		return 1;
	else
		return 0;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_exp (flt32 x) {
	x = x & expmask;
	x = x >> 23;
  	return x; 
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_val (flt32 x) {
	x = x & manmask;
	x |= implOne;
	return x;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
void flt32_get_all(flt32 x, int* sign, int*exp, int* val) {
	*sign = flt32_get_sign(x);
	*exp  = flt32_get_exp(x);
	*val  = flt32_get_val(x);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_left_most_1 (int bits) {
	if (bits == 0){
		return -1;
	}
	else{
		for (int i = 31; i >= 0; i--){
			if ((bits >> i) & 1){
				return i;
			}
		}
		return 0;
	}
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_abs (flt32 x) {
	if (x < 0){
		x = x & 0x7FFFFFFF;
	}
  	return x;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_negate (flt32 x) {
	x = x ^ 0x80000000;
	return x;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_add (flt32 x, flt32 y) {
	
	//if x is zero, return y, and vice versa
	if (x == 0){return y;}
	if (y == 0){return x;}
	
	//extract values
	int signx = flt32_get_sign(x);
	int expx = flt32_get_exp(x);
	int valx = flt32_get_val(x);
	int signy = flt32_get_sign(y);
	int expy = flt32_get_exp(y);
	int valy = flt32_get_val(y);

	//if x is larger, flip them so we only have to deal with one case
	if (expx < expy){
		int diff = expy - expx;
		valx=valx>>diff;
		expx+=diff;
	}
	else if (expx > expy){
		int diff = expx - expy;
		valy=valy>>diff;
		expy+=diff;
	}

	//if negative, 2's complement
	if (signx == 1){
		valx = ~valx + 1;
	}
	if (signy == 1){
		valy = ~valy + 1;
	}

	//add
	int signz = 0;
	int expz = expx;
	int valz = valx + valy;

	// un-2's complement
	if(valz < 0){
		valz = ~valz+1;
		signz = 1;
	}

	//correct for new exponent
	int correct = flt32_left_most_1(valz);
	correct = correct - 23;
	if (correct >= 0){
		expz += correct;
		valz = valz >> correct;
	}
	else {
		expz += correct;
		valz = valz << -correct;
	}

	//remove explicit 1
	int implicit1 = 0x007FFFFF;
	valz = valz&implicit1;

	//reassemble
	int total = valz;
	total = total | (expz << 23);
	total = total | (signz << 31);

	return total;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_sub (flt32 x, flt32 y) {
	y = flt32_negate(y);
	int total = flt32_add(x, y);
  return total;
}

