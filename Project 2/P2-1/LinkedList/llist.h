typedef struct ll_node {
  int key;
  int data;
  struct ll_node * next;
} ll_node;

// global var holding pointer to head of list
ll_node * head;

// If key is in list return a ptr to node.  Otherwise return NULL.
ll_node * find(int key);

// If key is in list find and modify or if key is not in list allocate and insert
// a new ll_node into list. Return  ptr to that node. Return NULL if allocation fails.
ll_node * insert(int key, int data);

// Delete node with given key.  Return 0 if key is in list  and return -1 if not.
int delnode(int key);

