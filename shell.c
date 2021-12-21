#include <aio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "$ "
#define BLOCK 4096

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

int main(void) {
	char line[BLOCK] = {0};

	while (true) {
		printf("%s", PROMPT);

		// TODO: Currently, lines have a fixed maximum length.
		if (fgets(line, BLOCK, stdin) == NULL) {
			return EXIT_SUCCESS;
		}

		// Strip away the newline at the end of the line.
		line[strlen(line) - 1] = '\0';

		// Execute the program.
		pid_t pid = fork();
		if (pid < 0) {
			eprintf("failed to fork\n");
			return EXIT_FAILURE;
		} else if (pid == 0) {
			// TODO: Currently, no arguments are considered -- only the executable.
			char *args[] = { line, NULL };

			execvp(args[0], args);
			perror(NULL);
		} else {
			wait(NULL);
		}
	}

    return EXIT_SUCCESS;
}
