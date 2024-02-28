#include <stdio.h>
#include <stdlib.h>

/* 
C code corresponding to MIPS.
*/

int main() {
  unsigned int x = 42;
  unsigned int x_copy = x;
  int          i = 0;
  int          limit = 32;
  int          sum = 0;
  int          lsb;               // least significant bit
  printf("sum at start: %d\n", sum);
  while (i != limit){
    lsb = x & 1;                  // & is bit-wise AND
    sum = sum + lsb;              // shorthand: "sum += lsb;"
    x = x >> 1;                   // >> is shift right
    i++;                          // i = i + 1;       
  }
  printf("sum at end: %d\n", sum);
  return 0;
}
