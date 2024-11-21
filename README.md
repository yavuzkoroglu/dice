# dice
Generates 'm' lines of 'n' random integers between 'a'-'b', inclusive, using the seed 's' or a random seed.

If no parameters given, it generates one line of two random integers between 1-6, inclusive.

## Examples

```
cc dice.c -o dice.exe; ./dice.exe -a 0 -b 1 -m 1 -n 20 -s 12345
```

```
cc dice.c -o dice.out; ./dice.out -m 5 -n 6
```
