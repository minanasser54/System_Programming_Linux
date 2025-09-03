#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64
#define BUF_SIZE 1024

int main() {
    char buf[BUF_SIZE];

    while (1) {
        printf("FeMtOsHeLl$ ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            return -1;
        }

        // Remove trailing newline
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0)
            continue;  // empty input, show prompt again

        // Split input into command + arguments
        char *argv[MAX_ARGS];
        int argc = 0;
        char *token = strtok(buf, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;  // NULL-terminate for execvp

        pid_t pid = fork();
        if (pid > 0) {
            // Parent process
            int status;
            wait(&status);
        } else if (pid == 0) {
            // Child process
            if (strcmp(argv[0],"exit")!=0){
                printf("Good Bye :)");
	    }

            execvp(argv[0], argv);  // run command with arguments
            exit(-1);
        } else {
            printf("Good Bye :)");
	    exit(-1);
            exit(-2);
            return 0;
        }
    }
    return 0;
}

