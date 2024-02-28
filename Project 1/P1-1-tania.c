//=================================================================
// Copyright 2023 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*
Please fill in the following
 Student Name:Tania  Binu
 Date:09/25/2023

ECE 2035 Project 1-2

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
-----------------------------------------------
     Find George Variably Scaled

This routine finds an exact match of George's face which may be
scaled in a crowd of faces.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int Load_Mem(char *, int *);

int main(int argc, char *argv[]) {
   int	             CrowdInts[1024];
   // This allows you to access the pixels (individual bytes)
   // as byte array accesses (e.g., Crowd[25] gives pixel 25):
   char *Crowd = (char *)CrowdInts;
   int	             NumInts, TopLeft, BottomRight;

   if (argc != 2) {
     printf("usage: ./P1-1 valuefile\n");
     exit(1);
   }
   NumInts = Load_Mem(argv[1], CrowdInts);
   if (NumInts != 1024) {
      printf("valuefiles must contain 1024 entries\n");
      exit(1);
   }
   if (DEBUG){
     printf("Crowd[0] is Pixel 0: 0x%02x\n", Crowd[0]);
     printf("Crowd[107] is Pixel 107: 0x%02x\n", Crowd[107]);

     printf("CrowdInts[211] packs 4 Pixels: 0x%08x\n", CrowdInts[211]);
     printf("Crowd[211*4] is Pixel 844: 0x%02x\n", Crowd[844]);
     printf("Crowd[211*4+1] is Pixel 845: 0x%02x\n", Crowd[845]);
     printf("Crowd[211*4+2] is Pixel 846: 0x%02x\n", Crowd[846]);
     printf("Crowd[211*4+3] is Pixel 847: 0x%02x\n", Crowd[847]);
   }
   
   /* your code goes here. */
  
   int i;//pixel
   int scalar;//variable that George is scaled by
   int count;//number of green in a row for shirt
   int fg;//firstGreen

   //start from bottom right of grid and traverse left until find green(7) shirt
   for (i = 4095 ; i >= 0; i--) {

      //found green shirt(7), then calculate scalar
      if (Crowd[i] == 7) { 
         fg = i;//set first green
         count = 0;
         while(Crowd[i]==7) {
            count++;//how many green boxes populate the shirt
            i--;//move to next pixel on the left
         }
         scalar = count/5;//calculate scalar


         //Check if it really is george with following methods for each feature based on scalar
         //yellow(5): subtract (64*2*scalar) from first green
         //black(8): subtract (64*4*scalar) from first green
         //blue(3): subtract ((64 *6) + scalar) from first green
         //red(2): subtract (64*7*scalar) from first green
         //white(1): subtract (64*8*scalar) from first green
         //BottomRight: add (4*scalar) to first green

         //scalar is 1
         if ((scalar ==1) && (Crowd[fg - 128] == 5) && (Crowd[fg - 256] == 8) && (Crowd[fg - 320] == 5) && (Crowd[fg - 385] == 3) && (Crowd[fg - 448]== 2) && (Crowd[fg - 512]== 1) && (Crowd[fg-513] == 1) && (Crowd[fg-514] ==1)) {
            BottomRight = fg + 4;
            TopLeft = BottomRight - 715; //go up 11 rows and left 11 to get top left because 12x12
            break;//no need to keep searching, George is found
         }
         
         //scalar is 2
         else if ((scalar == 2) && (Crowd[fg - 256] == 5) && (Crowd[fg - 512] == 8 ) && (Crowd[fg - 770] ==3)&& (Crowd[fg-896] == 2) && (Crowd[fg-960]==2)) { 
            BottomRight = fg + 8; //right 8 pixels is BR
            TopLeft = BottomRight - 1495; //go up 23 rows and left 23 to get top left because 24x24
            break;//no need to keep searching, George is found
         }

         //scalar is 3
         else if ((scalar ==3) && (Crowd[fg - 384] == 5) && (Crowd[fg - 768] == 8 ) && (Crowd[fg - 1155] ==3) && (Crowd[fg-1344]==2) && (Crowd[fg-1472]==2) && (Crowd[fg-1536]==1)) { 
            BottomRight = fg + 12; //right 12 pixels is BR
            TopLeft = BottomRight - 2275; //go up 35 rows and left 35 to get top left because 36x36
            break;//no need to keep searching, George is found
         }

         //scalar is 4
         else if ((scalar == 4) && (Crowd[fg - 512] == 5) && (Crowd[fg - 1024] == 8 )&& (Crowd[fg - 1540] ==3) && (Crowd[fg-1792]==2) && (Crowd[fg-2048]==1)) {
            BottomRight = fg + 16; //right 16 pixels is BR
            TopLeft = BottomRight - 3055; //go up 47 rows and left 47 to get top left because 48x48
            break;//no need to keep searching, George is found
         }

         //scalar is 5
         else if ((scalar ==5) && (Crowd[fg - 640] == 5) && (Crowd[fg - 1280] == 8 ) && (Crowd[fg - 1925] ==3) && (Crowd[fg-2240]==2) && (Crowd[fg-2560]==1)) { 
            BottomRight = fg + 20; //right 20 pixels is BR
            TopLeft = BottomRight - 3835; //go up 59 rows and left 59 to get top left because 60x60
            break;//no need to keep searching, George is found
         }
         else {
            continue;//George is not found yet, must do same process with next pixel
         }
      }
      else {
         continue;//green shirt not found yet, keep searching
      }
   }

   printf("George is located at: top left pixel %4d, bottom right pixel %4d.\n", TopLeft, BottomRight);
   exit(0);
}

/* This routine loads in up to 1024 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 1024; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}

//printf("%d\n", scalar);
//printf("%d\n", fg);
//printf("here\n");
//printf("%d and %d\n",TopLeft, BottomRight);