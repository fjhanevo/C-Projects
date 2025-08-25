#include <stdio.h>
#include <string.h>

#define MAX_INPUT 255
#define MAX_ARGS 64

int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;    // remove trailing newline

        // exit statement
        if (strcmp(input, "quit") == 0) break;

        int index = 0;

        char *token = strtok(input, " ");
        while (token != NULL && index < MAX_ARGS - 1) {
            args[index] = token;    // store pointer to the token
            index++;
            token = strtok(NULL, " ");  // get next token
        }

        args[index] = NULL; // set last element to NULL

        // print arguments for testing
        printf("Arguments found:\n");
        for (int j = 0; j < index; j++) {
            printf("  args[%d]: \"%s\"\n",j, args[j]);
        }

    }
    return 0;
}
