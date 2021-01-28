//code by Brent Grundman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/resource.h>
#include <string.h>

int main(int argc, char* argv[]) {
	pid_t ID = getpid();
	printf("Checker process [%d]: Starting.\n", ID);
	int i = 0;
	int argXpct = 3;
	if (strcmp(argv[0],"checker")==0 || strcmp(argv[0],"./checker")==0) {
		i ++;
		argXpct++;
	}
	if (argc != argXpct) {
		printf ("Error: please input %d command line arguments.\n",argXpct);
		return -1;
	}
	int dividend = atoi(argv[1+i]);
	int divisor = atoi(argv[0+i]);
	int shm_id, nbytes;
	//char readbuffer[80];
	//printf("%s\n", argv[2 + i]);
	//printf("%d\n", atoi(argv[2 + i]));
	//nbytes = read(atoi(argv[2 + i]), &shm_id, sizeof(shm_id));
	shm_id = atoi(argv[2 + i]);
	nbytes = sizeof(shm_id);
	printf("Checker process [%d]: read %d bytes containing shm ID %d\n", ID, nbytes, shm_id);
	int* shm_ptr = (int*)shmat(shm_id, NULL, 0);
	//printf("shm_ptr: %d\n", *shm_ptr);

	//printf("%d, %d\n",dividend, divisor);
	if (dividend%divisor == 0) {
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", ID, dividend, divisor);
		*shm_ptr = 1;
		//printf("shm_ptr: %d\n", *shm_ptr);
		printf("Checker process [%d]: wrote result (1) to shared memory.\n",ID);
		shmdt(&shm_id);
		return 1;
	}
	printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", ID, dividend, divisor);
	*shm_ptr = 0;
	printf("Checker process [%d]: wrote result (0) to shared memory.\n", ID);
	shmdt(&shm_id);
	return 0;
}

