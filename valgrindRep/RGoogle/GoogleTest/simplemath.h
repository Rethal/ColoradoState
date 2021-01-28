// simplemath.h

#include <cmath>

double cubic(double d,double e)
{
	return pow(d - e ,2);
	
}
double plustorial(double d){
	double total = 0;
	for(d; d>0;d--){
		total = total+d;
	}
return total;
}
