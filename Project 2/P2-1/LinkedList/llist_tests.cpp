// Inform the compiler that this included module is written in C instead of C++.
extern "C" {
	#include "llist.h"
}
#include "gtest/gtest.h" //"gtest/include/gtest/gtest.h"


// Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>
////////////////
// Access tests
////////////////
// 1
TEST(AccessTest, FindKey_EmptyList)
{
  head = NULL;

  // Test when list is empty.
  EXPECT_EQ(NULL, find(0));
  EXPECT_EQ(NULL, find(1));
  EXPECT_EQ(NULL, find(2));

}

// 3

TEST(AccessTest, FindKey_1EltLL)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = find(2);
  ll_node * p = find(4);

  // Test when list is empty.
  EXPECT_EQ(NULL, (int *) p);
  EXPECT_EQ(n, m);
  EXPECT_NE(n, p);
  EXPECT_NE(m, p);

  free(n);

}

// 5

TEST(AccessTest, FindKey_LongerLL)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);

  EXPECT_EQ(n, find(2));
  EXPECT_EQ(m, find(3));
  EXPECT_EQ(p, find(4));
  EXPECT_NE(n, m);
  EXPECT_NE(n, p);
  EXPECT_NE(m, p);
  EXPECT_EQ(NULL, (int *) find(5));

  free(p);
  free(m);
  free(n);
  
}

///////////////////
// Insertion tests
///////////////////
// 2
TEST(InsertTest, InsertInto_EmptyLL)
{
  head = NULL;
  ll_node * n = insert(2, 5);

  EXPECT_EQ(n, head);
  EXPECT_EQ(n->data, 5);
  EXPECT_EQ(n->key, 2);
  // cast NULL pointer as ptr to int to avoid type error
  EXPECT_EQ(NULL, (int *) n->next); 

  free(n);
}

// 4
TEST(InsertTest, InsertAsReplace_1EltLL)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(2, 7);

  EXPECT_EQ(n, head);
  EXPECT_EQ(n, m);
  EXPECT_EQ(n->key, 2);
  EXPECT_EQ(n->data, 7);

  free(n);

}

// 4
TEST(InsertTest, InsertNew_1EltLL)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);

  EXPECT_NE(n, head);
  EXPECT_NE(n, m);
  EXPECT_EQ(m, head);
  EXPECT_EQ(m->key, 3);
  EXPECT_EQ(m->data, 7);
  EXPECT_EQ(m->next, n);
  EXPECT_EQ(n->key, 2);
  EXPECT_EQ(n->data, 5);
  // cast NULL pointer as ptr to int to avoid type error  
  EXPECT_EQ(NULL, (int *) n->next); 

  free(m);
  free(n);
}

// 5
TEST(InsertTest, InsertAsReplace_MidElt)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);
  ll_node * h = insert(3, 9);

  EXPECT_EQ(h, m);
  EXPECT_EQ(h->key, 3);
  EXPECT_EQ(h->data, 9);

  free(n);
  free(m);
  free(p);
  // why don't we free(h), too?

}

// 5
TEST(InsertTest, InsertAsReplace_TailElt)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);
  ll_node * h = insert(4, 9);

  EXPECT_EQ(h, p);
  EXPECT_EQ(h->key, 4);
  EXPECT_EQ(h->data, 9);

  free(n);
  free(m);
  free(p);
}

///////////////////
// Deletion tests
///////////////////
// 6
TEST(DeleteTest, Delete_w_EmptyLL)
{
  head = NULL;
  int result = delnode(2);

  EXPECT_EQ(result, -1);
  EXPECT_EQ(NULL, head);

}

// 7
TEST(DeleteTest, Delete_1EltLL_Match)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  int result = delnode(2);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(NULL, find(2));
  EXPECT_EQ(NULL, head);
  EXPECT_NE(head, n);
  //free(n); // already freed in delnode
}

// 7
TEST(DeleteTest, Delete_1EltLL_NoMatch)
{
  head = NULL;
  ll_node * n = insert(3, 5);
  int result = delnode(2);

  EXPECT_EQ(result, -1);
  EXPECT_EQ(n, find(3));

  free(n);
}

// 8
TEST(DeleteTest, Delete_MultiEltLL_Head)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);
  int result = delnode(4);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(head, m);
  EXPECT_EQ(n, find(2));
  EXPECT_EQ(m, find(3));
  EXPECT_EQ(NULL, find(4));
  EXPECT_NE(head, p);
  
  free(n);  free(m);
  //free(p); // already freed in delnode
}

// 8
TEST(DeleteTest, Delete_MultiEltLL_NonHead)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);
  int result = delnode(3);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(head, p);
  EXPECT_EQ(n, find(2));
  EXPECT_EQ(NULL, find(3));
  EXPECT_EQ(p, find(4));
  EXPECT_NE(head, m);
  
  free(n); free(p);  //free(m); // already freed in delnode
}

// 8
TEST(DeleteTest, Delete_MultiEltLL_NoMatch)
{
  head = NULL;
  ll_node * n = insert(2, 5);
  ll_node * m = insert(3, 7);
  ll_node * p = insert(4, 8);
  int result = delnode(1);

  EXPECT_EQ(result, -1);
  EXPECT_EQ(head, p);
  EXPECT_EQ(n, find(2));
  EXPECT_EQ(m, find(3));
  EXPECT_EQ(p, find(4));

  free(n);  free(m);  free(p);
}
