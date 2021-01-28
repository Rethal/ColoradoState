//Code by Brent Grundman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
	if (argc != 6) {
		printf("Error: must have 6 command line inputs.\n");
		return -1;
	}
	pid_t wpid;
	pid_t childID[6];
	int status = 0;
	int shm = 0;
	int *shm_ptr[6];
	for (int i = 2; i < 6; i++) {
		int mario[2];
		pipe(mario);
		childID[i] = fork();
		if (childID[i] == 0) {
			//printf("I'm the child.\n");
			close(mario[1]);
			int shm_id, nbytes;
			nbytes = read(mario[0], &shm, 20);
			//close(mario[0]);
            char str[20];
            sprintf(str, "%d", shm);
		//	printf("str: %s\n", str);
		//	printf("child shm: %d\n", shm);
			printf("Coordinator: wrote shm ID %d to pipe (%d bytes)\n", shm, nbytes);

			if (status = execlp("checker", argv[1], argv[i], str, NULL) != -1) {
			}
			else {
				printf("failed to execute\n");
				exit(-1);
			}
		}
		else {
			//printf("I'm the parent.\n");
			printf("Coordinator: forked process with ID %d.\n", childID[i]);
			close(mario[0]);
			shm = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); 
			shm_ptr[i] = (int*)shmat(shm, NULL, 0);
			//char str[sizeof(shm_ptr)];
			write(mario[1], &shm, sizeof(shm));
			close(mario[1]);
		}
	}
	//shm_ptr = (int*)shmat(shm, NULL, 0);
	//printf("%d\n", shm_ptr[2]);
	//printf("%d\n", shm);
	int i = 2;
	while ((wpid = waitpid(childID[i], &status, 0))>0) {
		printf("Coordinator: waiting on child process ID %d...\n", childID[i]);
		//printf("Coordinator: child process %d returned %d.\n", wpid, WEXITSTATUS(status));
		if (*shm_ptr[i] == 1) {
			printf("Coordinator: result %d read from shared memory: %s is divisible by %s.\n", *shm_ptr[i], argv[i], argv[1]);
		}
		else if (*shm_ptr[i] == 0) { 
			printf("Coordinator: result %d read from shared memory: %s is not divisible by %s.\n", *shm_ptr[i], argv[i], argv[1]);

		}
		i++;
	}
	/*for (int i = 1; i < 5; i++) {
		printf("Coordinator: result %d read from shared memory: %d is divisible by %d.\n", *shm_ptr, argv[i], argv[0]);
		printf("Coordinator: result %d read from shared memory: %d is not divisible by %d.\n", *shm_ptr, argv[i], argv[0]);
		shm_ptr++;
	}*/
	shmdt(&shm);
	struct shmid_ds buf;
	i = shmctl(shm, IPC_RMID, &buf);
	printf("Coordinator: exiting.\n");
}