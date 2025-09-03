#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char buf[256];
    while(1){
        printf("Enter command to run: ");
	if (fgets(buf, sizeof(buf), stdin) == NULL) {
       	   perror("fgets failed");
  	   return -1;
	}
	// Remove newline
	buf[strlen(buf) - 1] = 0;    
    	if (strlen(buf) == 0)
	    continue;
	pid_t pid = fork();
    	
	if (pid > 0) {
        // Parent process
        int status;
        wait(&status);  // wait for child
        printf("PARENT: my pid = %d, my child status = %d\n",
               getpid(), WEXITSTATUS(status));
	
	} else if (pid == 0) {
        // Child process
        printf("CHILD: my pid = %d, my parent pid = %d\n", getpid(), getppid());

        // Use execlp: first arg = file to run, followed by argv list, ending with NULL
        execlp(buf, buf, (char *)NULL);
        // Only reached if exec fails
        perror("Exec failed");
        exit(-1);
    } else {
        // Fork failed
        perror("PARENT: failed to fork");
        return -1;
    }
    }
    return 0;
}

