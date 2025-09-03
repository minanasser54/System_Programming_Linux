#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 1024
#define MAX_SIZE 8192
int main()
{
	int size = INIT_SIZE;
	char* cur_working_dir = (char*)malloc(size);
	while(getcwd(cur_working_dir, size) == NULL)
	{
		size *= 2;
		if(size > MAX_SIZE)
		{
			printf("Error: Failed to get the pathname (pathname is too long)\n");
			exit(-1);
		}
		cur_working_dir = (char*)realloc(cur_working_dir, size);
	}

	printf("%s\n", cur_working_dir);
	free(cur_working_dir);
	return 0;
}
