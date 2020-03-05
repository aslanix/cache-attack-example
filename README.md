# Minimal cache attack example on OS X

This is a simple demonstration of cache side channels via CPU instruction
counter.  Complie with `make`.  The program reads a secret from stdin and
copies it into a buffer allocated in memory.  Information about the secret (in
this case, whether it is greater than 42) value is subsequently revealed via
the number of CPU cycles it takes to access an adjacent memory location.

## Example usage

    » make
    clang example.c -o example
    » make run
    ./example
    Enter an integer:100
    Time delta = 52; read garbage = 0
    » make
    clang example.c -o example
    » make run
    ./example
    Enter the secret:0
    Time delta = 7335; read garbage = 0

