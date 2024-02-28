#include <stdio.h>
#include <stdlib.h>

/* 
C code corresponding to MIPS.
*/

int main() {
  unsigned int x = 42;
  unsigned int x_copy = x;
  int          sum = 0;
  int          lsb;               // least significant bit
  printf("sum at start: %d\n", sum);
  while (x){                 // while loop body is executed when predicate is nonzero (x != 0)
    lsb = x & 1;                  // & is bit-wise AND
    sum = sum + lsb;              // shorthand: "sum += lsb;"
    x = x >> 1;                   // >> is shift right
  }
  printf("sum at end: %d\n", sum);
  return 0;
}
