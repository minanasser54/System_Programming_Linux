#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FILE_SIZE 100
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: %s file-name\n", argv[0]);
		exit(-1);
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		printf("Couldn't open the file\n");
		exit(-2);
	}

	char file_contents[FILE_SIZE];
	int read_size;
	while((read_size = read(fd, file_contents, FILE_SIZE)) > 0)
	{
		if(write(1, file_contents, read_size) < 0)
		{
			printf("Can't write the content of the file\n");
			exit(-3);
		}
	}

	close(fd);
	return 0;
}
