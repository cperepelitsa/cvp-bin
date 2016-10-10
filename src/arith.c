/* Reads numeric values on stdin, one per line,
 * and outputs some basic statistical information about them.
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <libgen.h>
#include <math.h>

const uint8_t PRINT_SUM    = 1 << 0;
const uint8_t PRINT_MEAN   = 1 << 1;
const uint8_t PRINT_SD     = 1 << 2;
const uint8_t PRINT_MEDIAN = 1 << 3;
const uint8_t PRINT_ALL    = PRINT_SUM | PRINT_MEAN | PRINT_MEDIAN | PRINT_SD;

long double *get_vals(size_t *length) {
    size_t vals_alloc = 2;
    size_t vals_used = 0;
    long double *vals = calloc(vals_alloc, sizeof(long double));

    char *line = NULL;
    size_t n = 0;
    char *endptr = NULL;
    while ((getline(&line, &n, stdin)) != -1) {
        long double v = strtold(line, &endptr);
        if (*endptr != 0 && *endptr != '\n') {
            fprintf(stderr, "invalid number: %s", line);
            continue;
        }
        if (vals_used == vals_alloc) {
            vals_alloc *= 2;
            vals = realloc(vals, vals_alloc * sizeof(long double));
        }
        vals[vals_used++] = v;
    }

    if (line != NULL) free(line);
    if (vals_used > 0)
        vals = realloc(vals, vals_used * sizeof(long double));
    *length = vals_used;
    return vals;
}

int cmp_ld(const void *a_vp, const void *b_vp) {
    long double a = *(long double*)a_vp;
    long double b = *(long double*)b_vp;
    if (a < b) return -1;
    else if (a > b) return 1;
    return 0;
}

void pretty_print(long double n) {
    char num[80];
    int num_len = snprintf(num, 80, "%.18Lf", n);
    char *num_end = num + num_len;
    int i;
    for (i = num_len-1; i >= 0; i--) {
        if (num[i] == '.') {
            num_end--;
            break;
        } else if (num[i] == '0') {
            num_end--;
        } else {
            break;
        }
    }
    *num_end = 0;
    puts(num);
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        fprintf(stderr, "usage: %s (FUNC[,FUNC]*|all)\n", basename(argv[0]));
        fprintf(stderr, "\nsupported functions:\n");
        fprintf(stderr, "    sum, mean, median, sd\n");
        return EXIT_SUCCESS;
    }

    uint8_t func = 0;
    char *funcStr = argv[1];
    char *tok = NULL;
    while ((tok = strsep(&funcStr, ","))) {
        if      (!strcmp(tok, "sum"))    func |= PRINT_SUM;
        else if (!strcmp(tok, "mean"))   func |= PRINT_MEAN;
        else if (!strcmp(tok, "sd"))     func |= PRINT_SD;
        else if (!strcmp(tok, "median")) func |= PRINT_MEDIAN;
        else if (!strcmp(tok, "all"))    func |= PRINT_ALL;
        else {
            fprintf(stderr, "invalid command: %s\n", tok);
            return EXIT_FAILURE;
        }
    }
    if (func == 0) func = PRINT_ALL;

    size_t num_vals;
    long double *vals = get_vals(&num_vals);
    if (vals == NULL || num_vals == 0) return 1;

    long double sum = 0, mean = 0;
    if ((func & (PRINT_ALL - PRINT_MEDIAN)) > 0) {
        size_t i;
        for (i = 0; i < num_vals; i++)
            sum += vals[i];
        mean = sum / num_vals;
    }
    if ((func & PRINT_SUM) > 0) {
        fputs("sum: ", stdout); pretty_print(sum);
    }
    if ((func & PRINT_MEAN) > 0) {
        fputs("mean: ", stdout); pretty_print(mean);
    }

    if ((func & PRINT_MEDIAN) > 0) {
        qsort(vals, num_vals, sizeof(long double), cmp_ld);
        size_t half = num_vals == 1 ? 0 : (num_vals >> 1) - 1;
        fputs("median: ", stdout);
        if ((num_vals & 1) == 0)
            pretty_print((vals[half]+vals[half+1])/2.0L);
        else
            pretty_print(vals[half]);
    }

    if ((func & PRINT_SD) > 0) {
        long double sqDiffSum = 0;
        size_t i;
        for (i = 0; i < num_vals; i++) {
            long double diff = vals[i] - mean;
            sqDiffSum += diff * diff;
        }
        fputs("sd: ", stdout);
        pretty_print(sqrtl(sqDiffSum / num_vals));
    }

    free(vals);
    return EXIT_SUCCESS;
}
