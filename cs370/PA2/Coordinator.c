//Code by Brent Grundman
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
	if (argc != 6) {
		printf("Error: must have 6 command line inputs.\n");
		return -1;
	}
	pid_t childID, wpid;
	int status = 0;
	for (int i = 2; i < 6; i++) {
		childID = fork();
		if (childID == 0) {
			//printf("I'm the child.\n");
			status = execlp("checker", argv[1], argv[i], NULL);
			//printf("Coordinator: child process %d returned %d.\n", childID, WEXITSTATUS(&status));
		}
		else {
			//printf("I'm the parent.\n");
			printf("Coordinator: forked process with ID %d.\n", childID);
			printf("Coordinator: waiting for process [%d].\n", childID);
			wpid = wait(&status);
			printf("Coordinator: child process %d returned %d.\n", wpid, WEXITSTATUS(status));
		}
	}
	printf("Coordinator: exiting.\n");
}