#include <aio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "$ "
#define BLOCK 4096
#define DELIMITER " \t\r\n\a"

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define strdup(s) (strcpy(malloc(strlen(s) + 1), s))

static char **split(char *string, char *delimeter);

int main(void) {
    char line[BLOCK] = {0};

    while (true) {
        printf("%s", PROMPT);

        // TODO: remove line length limit.
        if (fgets(line, BLOCK, stdin) == NULL) {
            return EXIT_SUCCESS;
        }

        // Execute the program.
        pid_t pid = fork();
        if (pid < 0) {
            eprintf("failed to fork\n");
            return EXIT_FAILURE;
        } else if (pid == 0) {
			char **args = split(line, DELIMITER);
            execvp(args[0], args);

			// This will only be reached if EXECVP fails above.
            perror(NULL);
        } else {
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}

static char **split(char *string, char *delimeter) {
	// If a string literal is passed in, STRTOK would have a segmentation fault
	// when it attempts to modify the string. For this reason we need a copy of
	// the string.
	char *copy = strdup(string);

	// Allocate space for 32 strings to start of with, but change this size
	// dynamically depending on what's needed.
	size_t size = 32;
	char **tokens = calloc(size, sizeof(char *));

	char *token = strtok(copy, delimeter);
	tokens[0] = token;

	for (size_t i = 1; ; i += 1) {
		if (i > size) {
			if (realloc(tokens, size * 2 * sizeof(char)) == NULL) {
				free(tokens);
				return NULL;
			}
		}

		char *token = strtok(NULL, delimeter);
		tokens[i] = token;
		if (token == NULL) {
			break;
		}
	}

	return tokens;
}
