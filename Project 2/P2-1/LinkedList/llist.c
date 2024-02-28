#include "llist.h"

#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf

ll_node * find(int key) {
 ll_node * this_node = head;

 while(this_node){
    if (this_node->key == key) return this_node;
    this_node = this_node->next;
 }
 return NULL;  // not found
}

ll_node * insert(int key, int data){
   ll_node * this_node;
   // if key is already in list, replace data
   if ((this_node = find(key))){ //key is in list
       this_node->data = data;
       return this_node;
   }

   // key is not in list
   this_node = (ll_node *) malloc(sizeof(ll_node));
   if (!this_node) return NULL; // no room in heap, allocation fails

   this_node->data = data;
   this_node->key = key;
   this_node->next = head;
   head = this_node;

   return this_node;
}

// delete node with given key.  Return 0 if key is in list
// and return -1 if not
int delnode (int key) {
  ll_node * this_node = head;
  ll_node * trailing_pointer;

  if (!this_node) return -1;

  if (this_node->key == key) {
      head = this_node->next;
      free(this_node);
      return 0;
  }
  trailing_pointer = this_node;
  this_node = this_node->next;
  while (this_node){
       if (this_node->key == key){
            trailing_pointer->next = this_node->next;
            free(this_node);
           return 0;
       }
       trailing_pointer = this_node;
       this_node = this_node->next;
  }
  return -1;
}

