//=================================================================
// Copyright 2023 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name: Mythri Muralikanna
 Date: 09/04/2023

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

Do not include any additional libraries.

Assume 9 < x < 32,768.
This program determines whether the square of x can be computed by
1) taking all but the least significant digit of x, adding this "upper" number to the square of itself, and 
2) concatenating the result of step 1 to the 2-digit square of the least significant digit of x.

For example, if x = 54, your program should determine whether 54^2 == 3016. 
    1) 5^2+5 = 30
    2) concat 30 w/ 4^2 = 16 to get 3016.

FOR FULL CREDIT (on all assignments in this class), BE SURE TO TRY
MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

**************************************************************************
ALSO, FILL IN THE ANSWER TO THIS QUESTION:
Suppose SQ is x squared and A is the value computed by steps 1 and 2 above.
What is true of all integers x for which SQ == A, but is not true for
integers where SQ != A?

YOUR ANSWER: x ends with 5 wherever SQ == A. The last digit of x is 5.
**************************************************************************
*/

//DO NOT change the following declaration (you may change the initial value).
int x = 675;
int SQ;
int A;
int Result;

/*
For the grading scripts to run correctly, the above declarations
must be the first lines of code in this file (for this homework
assignment only).  Under penalty of grade point loss, do not change
these lines, except to replace the initial values while you are testing
your code.  

Also, do not include any additional libraries.
 */

int main() {

  //Value of x squared
  SQ = x * x;            
  
  //Value of least significant digit and calculate its square
  int Xlo = x % 10;  
  int XloSq = Xlo * Xlo;

  //Value of the upper part of the number and calculate its square
  int Xhi = x / 10;
  int XhiSq = Xhi * Xhi + Xhi;

  //Concatenate the results
  A = XhiSq * 100 + XloSq;

  //Check for result
  if (SQ == A) {
    Result = 1;
  } else {
    Result = 0;
  }


  // your program should use this print statement
  printf("x: %d, SQ: %d, A: %d, Result: %d\n", x, SQ, A, Result);

  return 0;
}



