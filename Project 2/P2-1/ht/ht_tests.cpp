//=================================================================
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

// Inform the compiler that this included module is written in C instead of C++.
extern "C" {
	#include "hash_table.h"
}
#include "gtest/gtest.h"


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

// The #define directive defines a constant value that can be accessed throughout
// your code. Here it defines the default number of buckets in the hash table.
// You can change this number, but make sure to update the hash function with
// the right algorithm to compute the indices for buckets.
// For example, if the BUCKET_NUM is set to 5, the hash function should map a
// positive number to an integer between 0 and 4.
#define BUCKET_NUM  3

// Dummy value to store in hash table entry
// Please beware that any type of data (e.g. int, double, struct and etc.) can
// be stored in hash table for testing your hash table. Only the pointer to
// the data will be stored in the HashTableEntry.
struct HTItem {};

// Helper function for creating a lot of dummy values.
void make_items(HTItem* result[], unsigned n)
{
	// Populate the array with pointers to the dummy values.
	while(n--)
	{
		result[n] = (HTItem*) malloc(sizeof(HTItem));
	}
}

// A simple hash function that maps a positive number to an integer between 0~(BUCKET_NUM-1).
unsigned int hash(unsigned int key) {
	// return 0;
	return key%BUCKET_NUM;
}

////////////////////////
// Initialization tests
////////////////////////
TEST(InitTest, CreateDestroyHashTable)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);
	destroyHashTable(ht);
}

////////////////
// Access tests
////////////////
TEST(AccessTest, GetKey_TableEmpty)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Test when table is empty.
	EXPECT_EQ(NULL, getItem(ht, 0));
	EXPECT_EQ(NULL, getItem(ht, 1));
	EXPECT_EQ(NULL, getItem(ht, 2));

	// Test with index greater than the number of buckets.
	EXPECT_EQ(NULL, getItem(ht, 10));

	destroyHashTable(ht);
}

TEST(AccessTest, GetSingleKey)
{
  HashTable* ht = createHashTable(hash, BUCKET_NUM);

  // Create list of items
  size_t num_items = 1;
  HTItem* m[num_items];
  make_items(m, num_items);

  insertItem(ht, 0, m[0]);
  EXPECT_EQ(m[0], getItem(ht, 0));

  destroyHashTable(ht);    // dummy item is also freed here
}

TEST(AccessTest, GetKey_KeyNotPresent)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Create a list of items to add to hash table.
	size_t num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Insert one item into the hash table.
	insertItem(ht, 0, m[0]);

	// Test if the hash table returns NULL when the key is not found.
	EXPECT_EQ(NULL, getItem(ht, 1));

	// Destroy the hash table togeter with the inserted values
	destroyHashTable(ht);
}








////////////////////////////
// Access extra tests
////////////////////////////

//Creates a list of 5 items and calls get items and makes sure they are right. 
//Also checks for index not in table case
TEST(AccessTestExtra, GetKey_Normal)
{
    HashTable* ht = createHashTable(hash, BUCKET_NUM);

    // Create a list of items to add to the hash table.
    size_t num_items = 5;
    HTItem* m[num_items];
    make_items(m, num_items);

    // Insert 5 different items with distinct keys into the hash table.
	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 2, m[2]);
	insertItem(ht, 3, m[3]);
	insertItem(ht, 4, m[4]);

    // Verify that each item can be retrieved correctly.
	EXPECT_EQ(m[0], getItem(ht, 0));
	EXPECT_EQ(m[1], getItem(ht, 1));
	EXPECT_EQ(m[2], getItem(ht, 2));
	EXPECT_EQ(m[3], getItem(ht, 3));
	EXPECT_EQ(m[4], getItem(ht, 4));

	//Key not in table 
	EXPECT_EQ(NULL, getItem(ht, 5));
    // Destroy the hash table along with the inserted values.
    destroyHashTable(ht);
}


//Creates a list of items and tests if they have been replaced correctly
TEST(AccessTestExtra, GetKey_AfterReplace)
{
    HashTable* ht = createHashTable(hash, BUCKET_NUM);

    // Create a list of items to add to the hash table.
    size_t num_items = 6;
    HTItem* m[num_items];
    make_items(m, num_items);

	//Have 0,3 and 1,4 and 2,5 have same key of 0, 1, 2 respectively.

	// Insert 3 different items with distinct keys into the hash table.
	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 2, m[2]);

    // Verify that each item can be retrieved correctly.
	// EXPECT_EQ(m[0], getItem(ht, 0));
	EXPECT_EQ(m[1], getItem(ht, 1));
	EXPECT_EQ(m[2], getItem(ht, 2));

	//Replace all the items and check if the oldvalue is returned
	EXPECT_EQ(m[0], insertItem(ht, 0, m[3]));
	EXPECT_EQ(m[1], insertItem(ht, 1, m[4]));
	EXPECT_EQ(m[2], insertItem(ht, 2, m[5]));

	// Verify that each replaced item can be retrieved correctly.
	// EXPECT_EQ(m[3], getItem(ht, 0));
	EXPECT_EQ(m[4], getItem(ht, 1));
	EXPECT_EQ(m[5], getItem(ht, 2));

    // Destroy the hash table along with the inserted values.
    destroyHashTable(ht);
	free(m[0]);
	free(m[1]);
	// free(m[3]);
	free(m[2]);

}











////////////////////////////
// Removal and delete tests
////////////////////////////
TEST(RemoveTest, SingleValidRemove)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Create a list of items to add to hash table.
	size_t num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Insert one item into the hash table.
	insertItem(ht, 0, m[0]);

	// After removing an item with a specific key, the data stored in the
	// corresponding entry should be returned. If the key is not present in the
	// hash table, then NULL should be returned.
	void* data = removeItem(ht, 0);

	// Since the key we want to remove is present in the hash table, the correct
	// data should be returned.
	EXPECT_EQ(m[0], data);

	// Free the data
	free(data);

	destroyHashTable(ht);
}

TEST(RemoveTest, SingleInvalidRemove)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// When the hash table is empty, the remove funtion should still work.
	EXPECT_EQ(NULL, removeItem(ht, 1));

	destroyHashTable(ht);
}




////////////////////////////
// Access extra tests
////////////////////////////
TEST(RemoveTestExtra, NormalRemove) {

	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    // Create a list of items to add to the hash table.
    size_t num_items = 8;
    HTItem* m[num_items];
    make_items(m, num_items);

    // Insert 5 different items with distinct keys into the hash table.
	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 2, m[2]);
	insertItem(ht, 3, m[3]);
	insertItem(ht, 4, m[4]);
	insertItem(ht, 5, m[5]);
	insertItem(ht, 6, m[6]);
	insertItem(ht, 7, m[7]);

    // After removing an item with a specific key, the data stored in the
	// corresponding entry should be returned. If the key is not present in the
	// hash table, then NULL should be returned.
	// Since the key we want to remove is present in the hash table, the correct
	// data should be returned.

	//Remove at head (testing with all hashcode = 0)
	void* data = removeItem(ht, 5);
	EXPECT_EQ(m[5], data);

	// Free the data
	free(data);

	
	//Remove in the middle (testing with all hashcode = 0)
	data = removeItem(ht, 3);
	EXPECT_EQ(m[3], data);

	// Free the data
	free(data);


	//Remove at tail (testing with all hashcode = 0)
	data = removeItem(ht, 0);
	EXPECT_EQ(m[0], data);

	// Free the data
	free(data);

	//Key not in table 
	EXPECT_EQ(NULL, removeItem(ht, 8));

    // Destroy the hash table along with the inserted values.
    destroyHashTable(ht);

}



TEST(RemoveTestExtra, ReplaceRemove){

	HashTable* ht = createHashTable(hash, BUCKET_NUM);

    // Create a list of items to add to the hash table.
    size_t num_items = 6;
    HTItem* m[num_items];
    make_items(m, num_items);

	//Have 0,3 and 1,4 and 2,5 have same key of 0, 1, 2 respectively.

	// Insert 3 different items with distinct keys into the hash table.
	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 2, m[2]);


	//Replace all the items and check if the oldvalue is returned
	EXPECT_EQ(m[0], insertItem(ht, 0, m[3]));
	EXPECT_EQ(m[1], insertItem(ht, 1, m[4]));
	EXPECT_EQ(m[2], insertItem(ht, 2, m[5]));


	//Remove all the replaces
	//Remove at head (testing with all hashcode = 0)
	void* data = removeItem(ht, 0);
	EXPECT_EQ(m[3], data);

	// Free the data
	free(data);



	data = removeItem(ht, 1);
	EXPECT_EQ(m[4], data);
	// Free the data
	free(data);



	data = removeItem(ht, 2);
	EXPECT_EQ(m[5], data);
	// Free the data
	free(data);


    // Destroy the hash table along with the inserted values.
    destroyHashTable(ht);
	free(m[0]);
	free(m[1]);
	free(m[2]);
}



///////////////////
// Insersion tests
///////////////////
TEST(InsertTest, InsertAsOverwrite)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Create list of items to be added to the hash table.
	size_t num_items = 2;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Only insert one item with key=0 into the hash table.
	insertItem(ht, 0, m[0]);

	// When we are inserting a different value with the same key=0, the hash table
	// entry should hold the new value instead. In the test case, the hash table entry
	// corresponding to key=0 will hold m[1] and return m[0] as the return value.
	EXPECT_EQ(m[0], insertItem(ht, 0, m[1]));

	// Now check if the new value m[1] has indeed been stored in hash table with
	// key=0.
	EXPECT_EQ(m[1], getItem(ht,0));

	destroyHashTable(ht);
	free(m[0]);    // don't forget to free item 0
}




////////////////////////////
// Jumbo Test
////////////////////////////

TEST(JumboTest, EverythingTest)
{
	HashTable* ht = createHashTable(hash, BUCKET_NUM);

	// Create list of items to be added to the hash table.
	size_t num_items = 6;
	HTItem* m[num_items];
	make_items(m, num_items);	

	
    // Insert 5 different items with distinct keys into the hash table.
	insertItem(ht, 0, m[0]);
	insertItem(ht, 1, m[1]);
	insertItem(ht, 2, m[2]);
	insertItem(ht, 3, m[3]);

	// Test with index greater than the number of buckets.
	EXPECT_EQ(NULL, getItem(ht, 10));

	// Verify that each item can be retrieved correctly.
	EXPECT_EQ(m[0], getItem(ht, 0));
	EXPECT_EQ(m[1], getItem(ht, 1));
	EXPECT_EQ(m[2], getItem(ht, 2));

	void* data = removeItem(ht, 0);
	EXPECT_EQ(m[0], data);
	// Free the data
	free(data);

	//Replace all the items and check if the oldvalue is returned
	EXPECT_EQ(m[2], insertItem(ht, 2, m[5]));
	EXPECT_EQ(m[1], insertItem(ht, 1, m[4]));

	//Remove
	data = removeItem(ht, 2);
	EXPECT_EQ(m[5], data);
	// Free the data
	free(data);

	destroyHashTable(ht);
	free(m[2]);
	free(m[1]);
}