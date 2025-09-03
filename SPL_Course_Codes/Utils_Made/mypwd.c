#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf=getcwd(NULL, 0);    //here getcwd dynamiclly alloc the buf for varying size
    if (buf==NULL){
        printf("process failed\n");
        exit(-1);
    }
    size_t len = strlen(buf);   //getting size for writing
    if (write(1, buf,len) < 0) {
         printf("Write failed\n");
         exit(-3);
    }
    write(1, "\n", 1);
    free(buf);   // re free the alloc
    return 0;
}
