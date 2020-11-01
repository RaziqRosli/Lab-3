#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*	***3.3.i***

int main (void) {
	int pipefds[2];
	int buffer;

	if(pipe(pipefds)==-1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	int nombor = 22;

	printf("Writing a number to pipe...\n");
	write(pipefds[1], &nombor, sizeof(nombor));
	printf("Done.\n\n");

	printf("Reading a number from pipe...\n");
        read(pipefds[0], &buffer, sizeof(buffer));
        printf("Done.\n\n");

	printf("Number from pipe: %d\n", buffer);

	return EXIT_SUCCESS;
}
*/

// 3.3.ii
int main (void) {
        int pipefds[2];
        char buffer[5];

        if(pipe(pipefds)==-1) {
                perror("pipe");
                exit(EXIT_FAILURE);
        }

        char *pin = "4128\0";

        printf("Writing PIN to pipe...\n");
        write(pipefds[1],pin, 5);
        printf("Done.\n\n");

        printf("Reading PIN from pipe...\n");
        read(pipefds[0], buffer, 5);
        printf("Done.\n\n");

        printf("PIN from pipe: %s\n", buffer);

        return EXIT_SUCCESS;
}
