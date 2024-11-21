#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RAND_DICE(a, b) (rand() % (b - a + 1) + a)
#define USAGE_FMT       "\n Usage: %s [-a|b|m|n|s <positive-integer>]\n\n"

int main(int argc, char* argv[]) {
    unsigned a = 1;
    unsigned b = 6;
    unsigned m = 1;
    unsigned n = 2;
    unsigned s = 0;

    for (int arg_id = 1; arg_id < argc; arg_id += 2) {
        int const arg_a = !strcmp(argv[arg_id], "-a");
        int const arg_b = !strcmp(argv[arg_id], "-b");
        int const arg_m = !strcmp(argv[arg_id], "-m");
        int const arg_n = !strcmp(argv[arg_id], "-n");
        int const arg_s = !strcmp(argv[arg_id], "-s");
        int const sum   = arg_a + arg_b + arg_m + arg_n + arg_s;
        assert(sum == 0 || sum == 1);

        if (sum == 0) {
            fprintf(
                stderr,
                "\n ERROR: Unrecognized argument '%s'\n"
                USAGE_FMT,
                argv[arg_id],
                argv[0]
            );
            return EXIT_FAILURE;
        }

        if (arg_id + 1 >= argc) {
            fprintf(
                stderr,
                "\n ERROR: Missing value after '%s'\n"
                USAGE_FMT,
                argv[arg_id],
                argv[0]
            );
            return EXIT_FAILURE;
        }

        if (
            (arg_a && sscanf(argv[arg_id + 1], "%u", &a) != 1) ||
            (arg_b && sscanf(argv[arg_id + 1], "%u", &b) != 1) ||
            (arg_m && sscanf(argv[arg_id + 1], "%u", &m) != 1) ||
            (arg_n && sscanf(argv[arg_id + 1], "%u", &n) != 1) ||
            (arg_s && sscanf(argv[arg_id + 1], "%u", &s) != 1)
        ) {
            fprintf(
                stderr,
                "\n ERROR: The value after '%s' must be a positive integer\n"
                USAGE_FMT,
                argv[arg_id],
                argv[0]
            );
            return EXIT_FAILURE;
        }
    }

    if (s == 0) {
        s = (unsigned)clock() + (unsigned)time(NULL);
    }
    srand(s);

    if (a > b) {
        fputs("\n ERROR: 'a' cannot be larger than 'b'\n\n", stderr);
        return EXIT_FAILURE;
    }

    if (b > RAND_MAX) {
        fprintf(stderr, "\n ERROR: 'b' cannot be larger than %u\n\n", RAND_MAX);
        return EXIT_FAILURE;
    }

    if (n == 0) {
        return EXIT_SUCCESS;
    }

    while (m--) {
        unsigned i = n;
        while (--i) printf("%u ", RAND_DICE(a, b));
        printf("%u\n", RAND_DICE(a, b));
    }

    return EXIT_SUCCESS;
}
