/* Dumps the binary representation of floats.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_float(float f) {
    unsigned int u = *(unsigned int*)&f;
    int i;
    for (i = 31; i >= 0; i--) {
        printf("%d", (u & (1 << i)) > 0);
        if (i == 31 || i == 23)
            printf(" ");
    }
}

void print_double(double d) {
    uint64_t u = *(uint64_t*)&d;
    int i;
    for (i = 63; i >= 0; i--) {
        printf("%d", (u & (1 << i)) > 0);
        if (i == 63 || i == 52)
            printf(" ");
    }
}

int main(int argc, char** argv) {
    float fval;
    double dval;
    int doubles = 0, i;
    char* endptr;

    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        doubles = 1;
        argc--;
        argv++;
    }

    if (argc < 2) while (1) {
        printf("> ");
        i = doubles ? scanf("%lf", &dval) : scanf("%f", &fval);
        if (i < 1) break;
        if (doubles) {
            printf("  %lf = ", dval);
            print_double(dval);
        } else {
            printf("  %f = ", fval);
            print_float(fval);
        }
        printf("\n");
    } else for (i = 1; i < argc; i++) {
        if (doubles) {
            dval = strtod(argv[i], &endptr);
            if (endptr == argv[i]) {
                fprintf(stderr, "failed to parse \"%s\" as double\n", argv[i]);
                continue;
            }
            printf("%lf = ", dval);
            print_double(dval);
            printf("\n");
        } else {
            fval = strtof(argv[i], &endptr);
            if (endptr == argv[i]) {
                fprintf(stderr, "failed to parse \"%s\" as float\n", argv[i]);
                continue;
            }
            printf("%f = ", fval);
            print_float(fval);
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
