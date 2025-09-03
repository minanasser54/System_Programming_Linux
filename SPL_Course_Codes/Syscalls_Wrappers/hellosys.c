#include <unistd.h>   // contains system call wrappers like write(), read(), close()
#include <stdio.h>    // for printf() and other standard I/O library functions
#include <string.h>   // for strlen()
#include <stdlib.h>   // for exit()

void print_wrapper(void){
	if (write(1, "Hello Linux\n", strlen("Hello Linux\n")) < 0)
        	exit(-1);   // exit with error if write failed
	
}

int main() {
    // Using printf() would go through the C standard library (buffered I/O):
    // printf("Hello Linux\n");

    // Instead, here we call write() directly, which is a system call wrapper.
    // write(fd, buffer, count)
    // fd = 1 means standard output (stdout)
    print_wrapper();
    return 0;
}

