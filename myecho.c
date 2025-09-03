#include <unistd.h>   // for write(), read()
#include <stdlib.h>   // for exit()

// Manual string length function (no strlen)
size_t my_strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') len++;
    return len;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        // No arguments -> just newline
        write(1, "\n", 1);
        return 0; // success
    }

    for (int i = 1; i < argc; i++) {
        size_t len = my_strlen(argv[i]);
        if (len > 0) {
            write(1, argv[i], len);
        }
        if (i < argc - 1) {
            // Add space between arguments
            write(1, " ", 1);
        }
    }
    // Always end with newline
    write(1, "\n", 1);

    return 0; // success always
}
