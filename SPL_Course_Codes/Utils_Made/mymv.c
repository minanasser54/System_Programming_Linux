#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define COUNT 100
int main(int argc, char *argv[])
{
    char buf[COUNT];

    if (argc != 3) {
	printf("Usage: %s file-name1 file-name2\n", argv[0]);
	exit(-4);
    }

    int fdrd = open(argv[1], O_RDONLY);
    if (fdrd < 0) {
        printf("could not open a to read\n");
        exit(-1);
    }

    int fdwr = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);    
    if (fdwr < 0) {
	printf("could not open a write\n");
	exit(-2);
    }

    int num_read;
    while ((num_read = read(fdrd, buf, COUNT)) > 0) {
	if (write(fdwr, buf, num_read) < 0) {
	    printf("Write failed\n");
	    exit(-3);
	}
    }

    close(fdrd);
    close(fdwr);
    unlink(argv[1]);
    return 0;

}

