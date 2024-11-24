# dice
Generates 'm' lines of 'n' random integers between 'a'-'b', inclusive, using the seed 's' or a random seed.

If no parameters given, it generates one line of two random integers between 1-6, inclusive.

## How to Build

You may use the `clang` compiler to build the `dice.out` executable:

```
clang -Weverything -Wno-unsafe-buffer-usage dice.c -o dice.out
```

## Examples

```
./dice.out -a 0 -b 1 -m 1 -n 20 -s 12345
```

```
./dice.out -m 5 -n 6
```
