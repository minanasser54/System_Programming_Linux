#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	int err_fd;
	if (argc < 2)
	{
		printf("Usage: %s path-to-elf\n", argv[0]);
		exit(-1);
	}

	getchar();

	char* newargv[] = {argv[1], NULL};
	char* newenvp[] = {NULL};

	if ((err_fd = open("err.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
		fprintf(stderr, "Could not open the file for error redirection\n");
		exit(-1);
	}

	dup2(err_fd, 2);
	close(err_fd);
	getchar();

	execve(argv[1], newargv, newenvp);
	printf("Exec failed, kernel is not the mode of executing programs\n");
	return -2;
}
