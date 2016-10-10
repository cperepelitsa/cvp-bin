/* Checks files for bytes outside of a pretty/printable ASCII range.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>

int invalid(char b) {
    return (
        (b < 0x20 && (b != 0x09 && b != 0x0A && b != 0x0D))
        || (b > 0x7e)
    );
}

int checkfile(char *filename) {
    char buf[BUFSIZ];
    size_t pos = 0;
    int fd = strcmp(filename, "-") == 0 ? 0 : open(filename, O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }
    ssize_t r;
    while ((r = read(fd, buf, BUFSIZ)) > 0) {
        for (ssize_t i = 0; i < r; i++)
            if (invalid(buf[i])) {
                printf("%s: 0x%02x @ pos %lu\n",
                        filename, buf[i] & 0xff, pos+i);
                return 1;
            }
        pos += r;
    }
    close(fd);
    printf("%s: OK\n", filename);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file|-> [...]\n", basename(argv[0]));
        return EXIT_FAILURE;
    }

    int rc = 0;
    for (int i = 1; i < argc; i++)
        rc |= checkfile(argv[i]);

    return rc;
}
