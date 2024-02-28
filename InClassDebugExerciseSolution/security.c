#include "security.h"
#include <stdio.h>
#include <string.h>

/*
* Method to encrypt the original buzz.txt file and write it to
* encrypted.txt. There is no bug in here.
*/
void encrypt(){
  //Open the files
  FILE* encryptFile;
  encryptFile = fopen("encrypted.txt", "w");
  FILE* buzzFile;
  buzzFile = fopen("buzz.txt", "r");
  
  int i, j, encrypter;
  //For each data value in buzz.txt, encrypt it and write
  for(i = 0; i < 55; i++){ 
    for(j = 0; j < 101; j++){
      if (fscanf(buzzFile, "%d", &encrypter)) { 
        encrypter *= 20;
        encrypter += 3;
        fprintf(encryptFile, "%d", encrypter);
        fprintf(encryptFile, " ");
      }
    }
  }
  
  //Close the files
  fclose(encryptFile);
  fclose(buzzFile);
}

/*
* Pass by reference decrypt method that is used to decrypt
* a value encrypted in the encrypt method above.
*/
void decrypt(int* input){ //Task 5
  *input -= 3; 
  *input /= 20;
}