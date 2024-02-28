#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
/* 
* Header file for implementing a singly linked list. 
* Header files are a great way to organize code in large 
* programs. This keeps all of your declarations of methods
* and structs in one place. There is no bug in here.
*
* DO NOT MAKE CHANGES TO THIS FILE!!!!
*/

// struct for defining a linked list node
typedef struct ll_node_t {
  int key;
  int data;
  struct ll_node_t* next;
}ll_node;

// struct for defining a linked list
typedef struct linkedList_t {
  struct ll_node_t* head;
  struct ll_node_t* tail;
  int size;
}linkedList;

// creates and initializes a pointer to a linked list
linkedList* createLinkedList();

// if key is in list return a ptr to node.  Otherwise return NULL
ll_node* find(int key, linkedList* lList);

/*
* if key is in list find and modify or if key is not in list allocate and insert a new ll_node into list. 
* Return  ptr to that node. Return NULL if allocation fails. Appends to the tail of the list.
*/
ll_node* insertTail(int key, int data, linkedList* lList);

/*
* if key is in list find and modify or if key is not in list allocate and insert a new ll_node into list. 
* Return  ptr to that node. Return NULL if allocation fails. Appends at the head of the list.
*/
ll_node* insertHead(int key, int data, linkedList* lList);

// delete node with given key.  Return 0 if key is in list  and return -1 if not
int delete (int key, linkedList* lList);

#endif