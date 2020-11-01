#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*	***3.4.i***
#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

void getPIN(char pin[PIN_LENGTH + 1]) {
	srand(getpid() + getppid());

	pin[0] = 49 + rand() % 7;

	for(int i = 1; i < PIN_LENGTH; i++) {
		pin[i] = 48 + rand() % 7;
	}

	pin[PIN_LENGTH] = '\0';
}

int main (void) {
	while(1) {
		int pipefds[2];
		char pin[PIN_LENGTH + 1];
		char buffer[PIN_LENGTH + 1];

		pipe(pipefds);

		pid_t pid = fork();

		if(pid == 0) {
			getPIN(pin);				//generate PIN
			close(pipefds[0]);			// close read fd
			write(pipefds[1], pin, PIN_LENGTH + 1);	//write PIN to pipe

			printf("Generate PIN in child and sending to parent...\n");

			sleep(PIN_WAIT_INTERVAL);	//delaying PIN generation intentionally

			exit(EXIT_SUCCESS);
		}

		if(pid > 0) {
			wait(NULL);	//waiting for child to finish

			close(pipefds[1]);	//close write fd
			read(pipefds[0], buffer, PIN_LENGTH + 1);	//read PIN from pipe
			close(pipefds[0]);	//close read fd
			printf("Parent received PIN '%s' from child.\n\n", buffer);
		}
	}
	return EXIT_SUCCESS;
}
*/

//3.4.ii
int getPIN() {
	//use PPID and PID as the seed
	srand(getpid() + getppid());
	int secret = 1000 + rand() % 9000;
	return secret;
}

int main (void) {
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(pid > 0) {
		close(0);
		close(fd[1]);
		dup(fd[0]);

		int secretNumber;
		size_t readBytes = read(fd[0], &secretNumber, sizeof(secretNumber));

		printf("Waiting for PIN...\n");
		wait(NULL);
		printf("Bytes read: %ld\n", readBytes);
		printf("PIN: %d\n", secretNumber);
	}
	else if(pid == 0) {
		close(1);
		close(fd[0]);
		dup(fd[1]);

		int secret = getPIN();
		write(fd[1], &secret, sizeof(secret));
		exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}
