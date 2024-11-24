#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEF_ARG(x)      arg_##x = !strcmp(argv[arg_id], "-"#x)
#define ERROR(fmt)      error("\n ERROR: "fmt"\n"USAGE_FMT, argv[0])
#define ERROR2(fmt, x)  error("\n ERROR: "fmt"\n"USAGE_FMT, x, argv[0])
#define RAND_SEED       ((unsigned)clock() + (unsigned)time(NULL))
#define REPEAT(n)       for (unsigned i = (unsigned)(n); i > 0; i--)
#define SCAN_ARG(x)     (arg_##x && sscanf(argv[arg_id + 1], "%u", &x) != 1)
#define USAGE_FMT       "\n Usage: %s [-a|b|m|n|s <positive-integer>]\n\n"
#define WRAPS_PRINTF    __attribute__((format(printf, 1, 2)))

static WRAPS_PRINTF int error(char const* const restrict fmt, ...);
static inline unsigned randDice(unsigned const a, unsigned const b);

static WRAPS_PRINTF int error(char const* const restrict fmt, ...) {
    va_list args;
    assert(fmt != NULL);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    return EXIT_FAILURE;
}

int main(int argc, char* argv[]) {
    unsigned a = 1, b = 6, m = 1, n = 2, s = RAND_SEED;

    for (int arg_id = 1; arg_id < argc; arg_id += 2) {
        int const
            DEF_ARG(a), DEF_ARG(b), DEF_ARG(m), DEF_ARG(n), DEF_ARG(s),
            sum = arg_a + arg_b + arg_m + arg_n + arg_s;

        if (sum == 0)           return ERROR2("Unrecognized argument '%s'", argv[arg_id]);
        if (arg_id + 1 >= argc) return ERROR2("Missing value after '%s'", argv[arg_id]);

        assert(sum == 1);
        if (SCAN_ARG(a) || SCAN_ARG(b) || SCAN_ARG(m) || SCAN_ARG(n) || SCAN_ARG(s))
            return ERROR2("The value after '%s' must be a positive integer", argv[arg_id]);
    }

    if (a > b)          return ERROR("'a' cannot be larger than 'b'");
    if (b > RAND_MAX)   return ERROR2("'b' cannot be larger than %d", RAND_MAX);
    if (n == 0)         return EXIT_SUCCESS;

    srand(s);
    while (m--) {
        REPEAT(n-1) printf("%u ", randDice(a, b));
        printf("%u\n", randDice(a, b));
    }

    return EXIT_SUCCESS;
}

static inline unsigned randDice(unsigned const a, unsigned const b) {
    return (unsigned)rand() % (b - a + 1) + a;
}
