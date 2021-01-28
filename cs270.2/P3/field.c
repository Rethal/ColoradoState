#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement six functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. For example, methods you write may need a mask value.
 *  You might write a method to compute a mask for you and use it wherever
 *  it is needed as opposed to just putting the code in line.
 *  These additional <b>static</b> functions are similar to Java’s private methods.
 * <p>
 * @author <b>Brenton Grundman</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	int location = 1 << (position);
	int bit = location & value;
	bit = bit >> (position);
    return bit;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	int location = 0x1 << (position);
	value = location | value;
    return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
	int location = 1 << (position);
	location = ~location;
	value = location & value;
    return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	if (hi < lo){
		int via = hi;
		hi = lo;
		lo = via;
	}
	int location = 1;
	for (int i = 0; i < hi; i++){
		location = location << 1;
		location = location | 1;
	}
	int mask = 0;
	for (int i = 0; i < lo; i++){
		mask = mask << 1;
		mask = mask | 1;
	}
	mask = ~mask;
	location = location & mask;
	value = value & location;
	if (isSigned){
		if (value >> hi == 1){
			value = ~value;
			value = value + 1;
			value = value >> 1;
		}
	}
	value = value >> lo;
	
    return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setField (int oldValue, int hi, int lo, int newValue) {
	if (hi < lo){
		int via = hi;
		hi = lo;
		lo = via;
	}
	int location = 1;
	for (int i = 0; i < (hi-lo); i++){
		location = location << 1;
		location = location | 1;
	}
	newValue = newValue & location;
	newValue = newValue << lo;
	int reset = location << lo;
	reset = ~reset;
	oldValue = oldValue & reset;
	int value = oldValue | newValue;
	return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int fieldFits (int value, int width, bool isSigned) {
	int widthmask = 1;
	if (isSigned){
		if (((value >> (width-1)) & 1) == 1){
			value = ~value;
		}
		for (int i = 0; i < ((width - 1)-1); i++){
			widthmask = widthmask << 1;
			widthmask = widthmask | 1;
		}
	}
	else{
		for (int i = 0; i < (width - 1); i++){
			widthmask = widthmask << 1;
			widthmask = widthmask | 1;
		}
	}
	widthmask = ~widthmask;
	value = value & widthmask;
	bool fits = (value == 0);
    return fits;
}
