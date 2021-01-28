//code by Brent Grundman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>

int main(int argc, char* argv[]) {
	pid_t ID = getpid();
	printf("Checker process [%d]: Starting.\n", ID);
	int i = 0;
	int argXpct = 2;
	if (strcmp(argv[0],"checker")==0 || strcmp(argv[0],"./checker")==0) {
		i ++;
		argXpct++;
	}
	if (argc != argXpct) {
		printf ("Error: please input %d command line arguments.\n",argXpct);
		return -1;
	}
	//printf("got this far\n");
	int dividend = atoi(argv[1+i]);
	int divisor = atoi(argv[0+i]);
	//printf("%d, %d\n",dividend, divisor);
	if (dividend%divisor == 0) {
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", ID, dividend, divisor);
		printf("Checker process [%d]: Returning 1.\n",ID);
		return 1;
	}
	printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", ID, dividend, divisor);
	printf("Checker process [%d]: Returning 0.\n", ID);
	return 0;
}

