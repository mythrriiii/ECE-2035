#include "ll.h"
#include <stdlib.h>
#include <stdio.h>

// creates and initializes a pointer to a linked list
linkedList* createLinkedList(){
  linkedList* lList = (linkedList*) malloc(sizeof(linkedList));
  lList->head = NULL;
  lList->tail = NULL;
  lList->size = 0;
  
  return lList;
}

// if key is in list return a ptr to node.  Otherwise return NULL
ll_node* find(int key, linkedList* lList) { //Task 2
  ll_node* this_node = (ll_node*) lList->head;
  
  while(this_node){ 
     if (this_node->key == key) return this_node;
     this_node = (ll_node*) this_node->next;
  }
  return NULL;  // not found
}


/*
* if key is in list find and modify or if key is not in list allocate and insert a new ll_node into list. 
* Return  ptr to that node. Return NULL if allocation fails. Appends to the tail of the list.
*/
ll_node* insertTail(int key, int data, linkedList* lList) { //Task 3
    ll_node* this_node;
    this_node = find(key, lList);
    
    if (this_node){ //key is in list
        this_node->data = data;
        return this_node;
    }
    // key is not in list
    this_node = (ll_node *) malloc(sizeof(ll_node)); 
    if (!this_node) {
      free(this_node);
      return NULL;
    }
    
    this_node->data = data;
    this_node->key = key;
    this_node->next = NULL;
    
    //Empty list case
    if(lList->tail == NULL){
        lList->head = this_node;
        lList->tail = this_node;
       
    }
    //List is not empty case
    else{
        lList->tail->next = this_node;
        lList->tail = this_node; 
    }
    lList->size++;
    
    return this_node;
}

/*
* if key is in list find and modify or if key is not in list allocate and insert a new ll_node into list. 
* Return  ptr to that node. Return NULL if allocation fails. Appends at the head of the list.
*/
ll_node* insertHead(int key, int data, linkedList* lList) {
    ll_node* this_node;
    this_node = find(key, lList);
    if (this_node){ //key is in list
        this_node->data = data;
        return this_node;
    }
    // key is not in list
    this_node = (ll_node*) malloc(sizeof(ll_node)); 
    if (!this_node) {
      free(this_node);
      return NULL;
    }
    this_node->data = data;
    this_node->key = key;
    this_node->next = lList->head;
    lList->size++;
    lList->head = this_node;
    return this_node;
}

// delete node with given key.  Return 0 if key is in list and return -1 if not
int delete (int key, linkedList* lList) { //Task 4
   ll_node* this_node = lList->head;
   ll_node* tmp;

   if (!this_node) return -1;
  
    //if the head is what we are looking for. delete the old head and update
   if (this_node->key == key) {
       tmp = this_node->next; 
       free(this_node); 
       lList->head = tmp;
       lList->size--; 
       return 0;
   }
   
   //otherwise, search for the element
   while (this_node->next){
        if (this_node->next->key == key){
             tmp = this_node->next;
             this_node->next = this_node->next->next;
             lList->size--;
             free(tmp);
             return 0;
        }
    this_node = this_node->next;
  }
  return -1;
}

