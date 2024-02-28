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
 Date: 09/10/2023

ECE 2035 Homework 2-1

This is the only file that should be modified for the C implementation
of Homework 2.

Do not include any additional libraries.
-----------------------------------------------
    Where Harry Met Sally

This program determines when Harry and Sally first resided in the same city
and prints the ID of that city.

*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami,                //0, 1, 2, 3, 4
             Tokyo, Metz, Seoul, Toronto, Austin };                //5, 6, 7, 8, 9

void Print_Timelines(int[], int[]);

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums;
   int  Load_Mem(char *, int *, int *);
   int  City = -99;

   /* You may add additional declarations of local variables here. */

   int i = 0;  //Harry timeline loop counter
   int j = 0;  //Sally timeline loop counter

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
   if (NumNums != 20) {
     printf("valuefiles must contain 20 entries\n");
     exit(1);
   }

   /* Your program goes here */


  //Use while loops to make sure the timelines align when we start comparison 
  
  //The following loop checks if Harry's current date is lesser than Sally's and updates it 
  while (HarryTimeline[i + 2] < SallyTimeline [j]) {
   i = i + 2;
  }

  //The following loop checks if Sally's current date is lesser than Harry's and updates it 
  while (SallyTimeline[j + 2] < HarryTimeline [i]) {
   j = j + 2;
  }

  //This while loops checks whether they are in the same city at the same time
  while ( i < 9 && j < 9) {         //Condition makes sure to count 5 moves for each person

    if (HarryTimeline[i+1] == SallyTimeline[j+1]) {  //if the current city is the same for the date, then it returns that value
      City = HarryTimeline[i+1];   
      break;   
    }

    //Update the index of whoever moves first, if they move at the same time, they both get updated
    if (HarryTimeline[i+2] < SallyTimeline[j+2]) {
      i = i + 2;
    } else if (HarryTimeline[i+2] > SallyTimeline[j+2]) {
      j = j + 2;
    } else {
      i = i + 2;
      j = j + 2;
    }

   }
   
   /* Use a statement like this to print information helpful to
      debugging (e.g., the current value of some variable).
      Set DEBUG to 1 using the #define above when debugging, but
      reset it back to 0 before submitting your code so that your
      program doesn't confuse the autograder with superfluous prints. */
   if (DEBUG){
     Print_Timelines(HarryTimeline, SallyTimeline);
     printf("Sample debugging print statement. argc: %d \n", argc);
   }

   //City = 777; From shell code, -99 set at variable intialization
   printf("City in common the earliest: %d\n", City);
   
   exit(0);
}

/* This routine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     for (N=0; N < 20; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 if (N < 10)
	   IntArray1[N] = Value;
	 else
	   IntArray2[N-10] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}

/* Colors used to display timelines.
https://en.wikipedia.org/wiki/ANSI_escape_code#Colors */

// Using ANSI 256 cuz pretty colors and tried to find colorblind friendly colors
// If these colors still trouble you, use this guide https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

const char *colors[10] = {
        "\x1b[30;48;5;196m", // red
			  "\x1b[37;48;5;126m", // deep pink
			  "\x1b[30;48;5;226m", // yellow
			  "\x1b[37;48;5;27m", // blue
			  "\x1b[37;48;5;57m", // purple
			  "\x1b[30;48;5;214m", // orange
			  "\x1b[37;48;5;244m", // grey
			  "\x1b[30;48;5;255m", // white
			  "\x1b[37;48;5;88m", // deep red
			  "\x1b[30;48;5;45m"}; // light blue

#define RESET      "\x1b[0m"
#define foreground "\x1b[38;5;15m"

void Print_Years(){
  int i;
  printf("  ");
  for (i=90; i<120; i++){
    printf("%3d", i%100);
  }
  printf("\n");
}

void Print_Timeline(int Timeline[]){
  int j, duration, city;
  int scale = 3;
  char interval[6];
  duration = Timeline[0] - 1990;
  if (duration){ // Timeline does not start at 1990
    snprintf(interval, sizeof(interval), "%%%dc", duration*scale);
    printf("%s", RESET);
    printf(interval, ' ');
  }
  printf(foreground);
  for (j=0; j<10; j=j+2){
    duration = (((j+2)<10) ? Timeline[j+2] : 2020) - Timeline[j];
    city     = Timeline[j+1];
    snprintf(interval, sizeof(interval), "%%%dd", duration*scale);
    printf("%s", colors[city]); // start highlighting in city's color
    printf(interval, city);
  }
  printf(RESET); // stop highlighting
  printf("\n");
}


void Print_Timelines(int HarryTimeline[], int SallyTimeline[]) {
  Print_Years();
  printf("H: ");

  Print_Timeline(HarryTimeline);

  printf("S: ");
  Print_Timeline(SallyTimeline);
}
