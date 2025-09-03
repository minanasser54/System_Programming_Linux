#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FILE_SIZE 100

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		if(argc != 2)
			printf("Usage: %s source-name destination-name\n", argv[0]);
		else
			printf("Usage: %s %s destination-name\n", argv[0], argv[1]);

		exit(-1);
	}
	int src_fd = open(argv[1], O_RDONLY);

	if(src_fd < 0)
	{
		printf("Couldn't open the source file\n");
                exit(-2);
	}

	int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char file_content[FILE_SIZE];
	int read_size;
	while((read_size = read(src_fd, file_content, FILE_SIZE)) > 0)
	{
		if(write(dst_fd, file_content, read_size) < 0)
       		{
                	printf("Couldn't copy the content correctly\n");
                	exit(-3);
        	}
	}

	close(src_fd);
	close(dst_fd);
	unlink(argv[1]);
	return 0;
}
