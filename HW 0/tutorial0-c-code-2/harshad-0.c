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
  printf("i at start: %d\n", i);
  while (i != limit){
    i = i + 1;        // shorthand: "i++;" or "++i;"
  }
  printf("i at end: %d\n", i);
  return 0;
}
