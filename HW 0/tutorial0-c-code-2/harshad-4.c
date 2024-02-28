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
  int          remainder, result; // $6 and $8
  printf("x at start: %d\n", x);
  do {
    lsb = x & 1;                  // & is bit-wise AND
    sum += lsb;                   // sum = sum + lsb;
    x = x >> 1;                   // >> is shift right
  } while (x);                    // loop body is executed when predicate is nonzero (x != 0)

  remainder = x_copy % sum;            // % is modulo (e.g., 5 % 2 = 1)
  if (remainder)
    result = 0;
  else
    result = 1;

  printf("result at end: %d\n", result);
  if (result)
    printf("%d is a Harshad number in base 2.\n", x_copy);

  return 0;
}
