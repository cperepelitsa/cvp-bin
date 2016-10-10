/* Dumps the contents of the C stat(2) struct for the given files.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int longest_len(struct stat s, int *maxlen) {
    char buf[160];
    int len;
    *maxlen = 0;

    len = snprintf(buf, 160, "%lu", s.st_dev);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_dev\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_ino);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_ino\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%d",  s.st_mode);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_mode\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_nlink);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_nlink\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%d",  s.st_uid);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_uid\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%d",  s.st_gid);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_gid\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_rdev);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_rdev\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_size);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_size\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_blksize);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_blksize\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    len = snprintf(buf, 160, "%lu", s.st_blocks);
    if (len < 0) {
        fprintf(stderr, "snprintf returned %d when printing st_blocks\n", len);
        return 1;
    } else if (len > *maxlen) {
        *maxlen = len;
    }

    return 0;
}

int dump_stat(char *filename) {
    struct stat s;
    if (lstat(filename, &s) != 0) {
        perror(filename);
        return 1;
    }

    int numlen;
    if (longest_len(s, &numlen) != 0) {
        return 1;
    }

    printf("%s:\n", filename);
    printf("    st_dev     = %-*lu    // ID of device containing file\n", numlen, s.st_dev);
    printf("    st_ino     = %-*lu    // inode number\n", numlen, s.st_ino);
    printf("    st_mode    = %-*d     \b// file type and mode\n", numlen, s.st_mode);
    printf("    st_nlink   = %-*lu    // number of hard links\n", numlen, s.st_nlink);
    printf("    st_uid     = %-*d     \b// user ID of owner\n", numlen, s.st_uid);
    printf("    st_gid     = %-*d     \b// group ID of owner\n", numlen, s.st_gid);
    printf("    st_rdev    = %-*lu    // device ID (if special file)\n", numlen, s.st_rdev);
    printf("    st_size    = %-*lu    // total size, in bytes\n", numlen, s.st_size);
    printf("    st_blksize = %-*lu    // blocksize for filesystem I/O\n", numlen, s.st_blksize);
    printf("    st_blocks  = %-*lu    // number of 512B blocks allocated\n", numlen, s.st_blocks);

    char buf[80];

    asctime_r(gmtime(&s.st_atim.tv_sec), buf);
    buf[strlen(buf)-1] = '\0';
    printf("    st_atim    = %s = (%lus + %ldns)  // time of last access\n",
            buf, s.st_atim.tv_sec, s.st_atim.tv_nsec);

    asctime_r(gmtime(&s.st_mtim.tv_sec), buf);
    buf[strlen(buf)-1] = '\0';
    printf("    st_mtim    = %s = (%lus + %ldns)  // time of last modification\n",
            buf, s.st_mtim.tv_sec, s.st_mtim.tv_nsec);

    asctime_r(gmtime(&s.st_ctim.tv_sec), buf);
    buf[strlen(buf)-1] = '\0';
    printf("    st_ctim    = %s = (%lus + %ldns)  // time of last status change\n",
            buf, s.st_ctim.tv_sec, s.st_ctim.tv_nsec);

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fputs("missing argument\n", stderr);
        return 1;
    }

    int final_rc = 0;
    for (int i = 1; i < argc; i++) {
        final_rc |= dump_stat(argv[i]);
        if (i < argc-1) puts("");
    }

    return final_rc;
}
