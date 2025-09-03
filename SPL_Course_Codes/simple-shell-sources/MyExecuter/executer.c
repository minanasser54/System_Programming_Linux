#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s path-to-elf\n", argv[0]);
		exit(-1);
	}

	getchar();

	char* newargv[] = {argv[1], NULL};
	char* newenvp[] = {NULL};

	execve(argv[1], newargv, newenvp);
	printf("Exec failed, kernel is not the mode of executing programs\n");
	return -2;
}
