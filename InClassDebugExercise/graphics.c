#include "graphics.h"
#include "security.h"
#include <stdio.h>
#include <string.h>
#include "ll.h"

/*
* Reads in the file from encrypted.txt, stores it in a linkedList, and decrypts the file
* to draw Buzz, the mascot of Georgia Tech. After drawing Buzz, ensures that all dynamic
* memory is freed. 
*/
void draw_buzzEncrypted(){
    linkedList* list = createLinkedList();
    FILE *buzzFile;
    buzzFile = fopen("encrypted.txt", "r");
    int i, j, inserter;
	//Iterate over the file in a 2D manner and insert to list
    for(i = 0; i < 55; i++){ 
      for(j = 0; j < 101; j++){
        fscanf(buzzFile, "%d", &inserter);
        decrypt(inserter); //decrypt the individual value, Task 1
        insertTail(j + 101 * i, inserter, list); //For Task 6, replace with insertHead
      }
    }
    
    fclose(buzzFile);
    
    //Iterate over the linkedList
    ll_node* curr = list->head;
    while(curr){
        printf("%c", &curr->data); //Task 1
        curr = curr->next;
    }
    
    printf("\n");
    
    
    //Clean up time!
    for(i = 0; i < 55; i++){ 
      for(j = 0; j < 101; j++){
        delete(j + 101 * i, list);
      }
    }
	
    if(list->size == 0){ //only free if we know this list is empty
	  if(find(0, list) == NULL) { //really make sure the list is empty
        free(list);
      }
    }
}