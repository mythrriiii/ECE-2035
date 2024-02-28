//=================================================================
// Copyright 2023 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*
Please fill in the following
 Student Name: Mythri Muralikannan
 Date: 09/28/2023

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
   TopLeft = 0;        // Temporary: replace this.
   BottomRight = 100;  // Temporary: replace this.
   
   // Match Conditions
   int George86 = 0x08;         //(REMOVE) Checks the color of the mouth
   int George77 = 0x08;         //Checks whether there is a smile and color 
   int George56 = 0x03;         //Checks the color of the eyes
   int George57 = 0X05;         //Checks if there are no sunglasses
   int George37 = 0x01;         //Checks for the hat design

   //Initialize all the variables  
   int currRow = 63;            //Row counter variable
   int currCol = 63;            //Column counter variable
   int currIndex;               //Current index = currRow*64 + currCol 
   int countIndex;              //Index used in calculating scaling factor
   int greenCount;              //Number of greens used to calculate scaling factor
   int scalingFactor;           //Calculated scaling factor = greenCount/5

   //Initialize scaled indices 
   int scaledrow3;       
   int scaledrow5;
   int scaledrow7; 
   int scaledrow8; 
   int scaledcol6; 
   int scaledcol7; 

   //Initialize the match conditions
   int Curr86;
   int Curr77;
   int Curr56;
   int Curr57;
   int Curr37;


   //While loops to make sure row and column variables are within the bounds
   while (currRow >= 0) {
      while (currCol >= 0) {

         currIndex = currRow*64 + currCol;

         //Identifies a possible george
         if (Crowd[currIndex] == 0x07) {

            //Calculate scaling factor
            greenCount = 0;
            countIndex = currIndex;

            //printf("currRow: %4d, currCol: %4d\n", currRow, currCol);

            while (Crowd[countIndex] == 0x07) {
               greenCount++;
               countIndex--;
            }

            scalingFactor = greenCount/5;

            //Calculate TopLeft and BottomRight  
            currCol = currCol + 4*scalingFactor;
            currIndex = currRow*64 + currCol;
            BottomRight = currIndex;
            TopLeft = (currRow - 12*scalingFactor + 1)*64 + (currCol - 12*scalingFactor + 1);


            //printf("currRow: %4d, currCol: %4d, currScalingfactor: %4d\n", currRow, currCol, scalingFactor);  


            //Calculate Scaled indices for rows 3, 5, 7, 8 and columns 6, 7
            scaledrow3 = currRow - 8*scalingFactor; 
            scaledrow5 = currRow - 6*scalingFactor;
            scaledrow7 = currRow - 4*scalingFactor; 
            scaledrow8 = currRow - 3*scalingFactor; //REMOVE
            scaledcol6 = currCol - 5*scalingFactor; 
            scaledcol7 = currCol - 4*scalingFactor; 

            //Calculate the match condition pixels
            Curr86 = Crowd[scaledrow8*64 + scaledcol6];
            Curr77 = Crowd[scaledrow7*64 + scaledcol7];
            Curr56 = Crowd[scaledrow5*64 + scaledcol6];
            Curr57 = Crowd[scaledrow5*64 + scaledcol7];
            Curr37 = Crowd[scaledrow3*64 + scaledcol7];


            //Check if this is George and if not change the currCol accordingly
            //printf("curr86Row 08: %4d, curr77 08: %4d, curr56 03: %4d, curr57 05: %4d, curr37 01: %4d\n", Curr86, Curr77, Curr56, Curr57, Curr37);
            if ((Curr86 == George86) && (Curr77 == George77) && (Curr56 == George56) && (Curr57 == George57) && (Curr37 == George37)) {
               goto found; 
            } else {
               currCol = (currCol + 1)/scalingFactor - 12;
            }

         }

         currCol--;
      }
      currCol = 63;
      currRow--;
   }

   found:
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
