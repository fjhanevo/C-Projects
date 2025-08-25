#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 255
#define MAX_ARGS 64

void execute_command(char *args[]);

int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;    // remove trailing newline

        // exit statement
        if (strcmp(input, "exit") == 0) break;

        int index = 0;

        char *token = strtok(input, " ");
        while (token != NULL && index < MAX_ARGS - 1) {
            args[index] = token;    // store pointer to the token
            index++;
            token = strtok(NULL, " ");  // get next token
        }

        args[index] = NULL; // set last element to NULL

        execute_command(args);

    }
    return 0;
}

void execute_command(char *args[])
{
    pid_t pid = fork();  // create child process

    if (pid == 0) {
        // child process
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        // parent process
        wait(NULL);
    } else {
        // fork failed
        perror("Fork failed");
    }
    
}
