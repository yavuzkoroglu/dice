#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ERROR(fmt)      error("\n ERROR:"fmt"\n"USAGE_FMT, argv[0])
#define ERROR2(fmt, x)  error("\n ERROR:"fmt"\n"USAGE_FMT, x, argv[0])
#define RAND_DICE(a, b) ((unsigned)rand() % (b - a + 1) + a)
#define RAND_SEED       ((unsigned)clock() + (unsigned)time(NULL))
#define REPEAT(n)       for (unsigned i = (unsigned)(n); i > 0; i--)
#define USAGE_FMT       "\n Usage: %s [-a|b|m|n|s <positive-integer>]\n\n"

__attribute__((format(printf, 1, 2)))
static int error(char const* const restrict fmt, ...) {
    va_list args;
    assert(fmt != NULL);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    return EXIT_FAILURE;
}

int main(int argc, char* argv[]) {
    unsigned
        a = 1, b = 6,
        m = 1, n = 2,
        s = 0;

    for (int arg_id = 1; arg_id < argc; arg_id += 2) {
        int const
            arg_a = !strcmp(argv[arg_id], "-a"),
            arg_b = !strcmp(argv[arg_id], "-b"),
            arg_m = !strcmp(argv[arg_id], "-m"),
            arg_n = !strcmp(argv[arg_id], "-n"),
            arg_s = !strcmp(argv[arg_id], "-s"),
            sum   = arg_a + arg_b + arg_m + arg_n + arg_s;
        assert(sum == 0 || sum == 1);

        if (sum == 0)           ERROR2("Unrecognized argument '%s'", argv[arg_id]);
        if (arg_id + 1 >= argc) ERROR2("Missing value after '%s'", argv[arg_id]);

        if (
            (arg_a && sscanf(argv[arg_id + 1], "%u", &a) != 1) ||
            (arg_b && sscanf(argv[arg_id + 1], "%u", &b) != 1) ||
            (arg_m && sscanf(argv[arg_id + 1], "%u", &m) != 1) ||
            (arg_n && sscanf(argv[arg_id + 1], "%u", &n) != 1) ||
            (arg_s && sscanf(argv[arg_id + 1], "%u", &s) != 1)
        ) ERROR2("The value after '%s' must be a positive integer", argv[arg_id]);
    }

    if (s == 0) s = RAND_SEED;
    srand(s);

    if (a > b)          ERROR("'a' cannot be larger than 'b'");
    if (b > RAND_MAX)   ERROR2("'b' cannot be larger than %d", RAND_MAX);

    if (n == 0) return EXIT_SUCCESS;

    while (m--) {
        REPEAT(n-1) printf("%u ", RAND_DICE(a, b));
        printf("%u\n", RAND_DICE(a, b));
    }

    return EXIT_SUCCESS;
}
