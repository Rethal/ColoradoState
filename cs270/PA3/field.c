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
  /**  int mask[32] = makeMask(value);
  int bit = mask[31-position];
  return bit;*/
  return (value>>position)&1;
}

/**static int makeMask (int value){
  int mask[32], *p = mask+sizeof(mask)-1;
  *p = '\0';
  do{
    *--p = (value%2);
  }
  while(value/=2);
  return mask;
}

static int maskToInt (int mask[]){
  int value, *p = mask+sizeof(mask)-1;
  *p = '\0';
  for(int i=0; i<32; i++){
    value = value + ((2^i)*(*--p));
  }
  return value;

  /** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
  /**int mask[32] = makeMask(value);
  mask[31-position] = 1;
  value = maskToInt(mask);
  return value;*/
  value = value|(1<<position);
  return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
  /** int mask[32] = makeMask(value);
  mask[31-position] = 0;
  value = maskToInt(mask);
  return value;*/
  value = value&(~(1<<position));
  return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
  /** int mask[32] = makeMask(value);
  int mask2[32] = makeMask(0);
  if(isSigned){
    if(hi>lo){
      //if first bit (hi-lo) 1, value negative; 0...31-hi = 1
      int i =31-hi;
      for(mask[i]; mask[31-lo];i++){      
	mask2[(31-(hi-lo))+((i+hi)-31)]=mask[i];
      }
      if(value<0){
	i=0;
	for(i;i<(31-hi);i++){
	  mask2[i]=1;
	}
      }
    }
    else if(lo>hi){
      //if first bit 1, value negative
      for(mask[i]; mask[31-hi];i++){      
	mask2[(31-(lo-hi))+((i+lo)-31)]=mask[i];
      }
    }
    else{
      
    }
  }
  else{
    if(hi>lo){
    }
    else if(lo>hi){
    }
    else{
    }
    }*/
  return 0;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setField (int oldValue, int hi, int lo, int newValue) {
  /** if(hi>lo){
  }
  else if(lo>hi){
  }
  else{
  }*/
  return 0;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int fieldFits (int value, int width, bool isSigned) {
  if(isSigned){
    if(value>((2^(width-1))-1) || value<(-(2^(width-1)))){
      return 0;
    }
    else return 1;
  }
  else{
    if(value>(2^(width))-1 || value<0){
      return 0;
    }
    else return 1;
  } 
}
