#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define PROMPT "$ "
#define BLOCK 4096

int main(void) {
	char line[BLOCK] = {0};

	while (true) {
		printf("%s", PROMPT);

		if (fgets(line, BLOCK, stdin) == NULL) {
			// End of file.
			return EXIT_SUCCESS;
		}

		printf("%s", line);
	}

    return EXIT_SUCCESS;
}
