/* Minimalist cache side-channel demo */
/* Aslan Askarov                      */
/* Language-based security, 2020      */
/* OS X demo                          */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// the instruction to get the CPU cycle counter 
static inline uint64_t get_cycles()
{
    uint64_t n;
    __asm__ __volatile__ ("rdtsc" : "=A"(n));
    return n;
}

// read a number from stdin
int readNumber () {
    int t;
    printf("Enter an integer:");
    scanf("%d", &t);  
    return t;
}


void attack()
{   // read the secret
    int secret = readNumber ();
    // we allocate a couple of blocks 
    // that are likely to be adjacently allocated
    int* secret_buffer = (int*) malloc (512) ;
    int* public_buffer = (int*) malloc (512) ; 
    
    if (secret > 42) {
        // accessing secret buffer brings the public_buffer into 
        // the cache
        secret_buffer [0] = secret;
    }

    uint64_t t1 = get_cycles () ;
    int garbage = public_buffer [0]; // read something from the public block
    uint64_t t2 = get_cycles () ;
    
    printf ("Time delta = %llu; read garbage = %d\n", t2 - t1, garbage) ;
    return;
}


// test of clock readings
void testClockReadings () {
    uint64_t t1=get_cycles();
    uint64_t t2;
    for (int i = 0; i < 30; i++) {
       t2  = get_cycles();
       printf("Time delta %d = %llu\n", i, t2-t1);
       t1 = t2;
    }
}


int main () {
    // testClockReadings();
    attack ();
    return 0;
}

