#include <aio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "$ "
#define DELIMITER " \t\r\n\a"

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define strdup(s) (strcpy(malloc(strlen(s) + 1), s))

static char **shell_split(char *string, char *delimeter);
static char *shell_read_line(FILE *file);

int main(void) {
    while (true) {
        printf("%s", PROMPT);

        char *line = shell_read_line(stdin);
        if (line == NULL) {
            return EXIT_SUCCESS;
        }

        // Execute the program.
        pid_t pid = fork();
        if (pid < 0) {
            eprintf("failed to fork\n");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            char **args = shell_split(line, DELIMITER);
            execvp(args[0], args);

            // This will only be reached if EXECVP fails above.
            perror(NULL);
        } else {
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}

static char **shell_split(char *string, char *delimeter) {
    // If a string literal is passed in, STRTOK would have a segmentation fault
    // when it attempts to modify the string. For this reason we need a copy of
    // the string.
    char *copy = strdup(string);

    // Allocate space for 32 strings to start of with, but change this size
    // dynamically depending on what's needed.
    size_t size = 32;
    char **tokens = malloc(size * sizeof(char *));

    char *token = strtok(copy, delimeter);
    tokens[0] = token;

    for (size_t position = 1;; position += 1) {
        if (position > size) {
            if (realloc(tokens, size * 2 * sizeof(char)) == NULL) {
                free(tokens);
                return NULL;
            }

            size *= 2;
        }

        char *token = strtok(NULL, delimeter);
        tokens[position] = token;
        if (token == NULL) {
            break;
        }
    }

    return tokens;
}

static char *shell_read_line(FILE *file) {
    size_t size = 32;
    char *line = malloc(size * sizeof(char));

    int current;
    for (size_t position = 0; (current = fgetc(file)) != EOF; position += 1) {
        if (position > size) {
            if (realloc(line, size * 2 * sizeof(char)) == NULL) {
                free(line);
                return NULL;
            }

            size *= 2;
        }

        line[position] = (current == '\n' || current == EOF) ? '\0' : current;

        if (current == '\n' || current == EOF) {
            return line;
        }
    }

    return line;
}
