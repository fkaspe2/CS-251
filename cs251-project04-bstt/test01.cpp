/*test01.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree, basic insert, clear") 
{
	//  <key, data>
	bstt<int, int>  tree;
	
	REQUIRE(tree.size() == 0);
	
	int value;
	tree.insert(1,111);
	REQUIRE(tree.size() == 1);
	REQUIRE(tree.search(1, value));
	REQUIRE(value == 111);
	REQUIRE(tree[1] == 111);
	
	tree.clear();
	REQUIRE(tree.size() == 0);
	
	
	// ANOTHER ONE
	tree.insert(1,111);
	REQUIRE(tree.size() == 1);
	REQUIRE(tree.search(1, value));
	REQUIRE(value == 111);
	REQUIRE(tree[1] == 111);
	
	tree.clear();
	REQUIRE(tree.size() == 0);
}


TEST_CASE("(2) setting two trees equal(destructs save for end)") 
{
	bstt<int, int>  tree1;
	tree1.insert(1,111);
	tree1.insert(7,777);
	tree1.insert(3,333);
	REQUIRE(tree1.size() == 3);
	REQUIRE(tree1[1] == 111);
	REQUIRE(tree1[3] == 333);
	
	// copy constructor test
	bstt<int, int>  tree2(tree1);
	tree2.insert(6,666);
	tree2.insert(4,444);
	REQUIRE(tree2[4] == 444); //inserted 
	REQUIRE(tree2[6] == 666);
	REQUIRE(tree2[1] == 111);  //from tree1
	REQUIRE(tree2[7] == 777);
	REQUIRE(tree2[3] == 333);
		
	tree2.clear();
	
	// =operator test
	bstt<int, int>  tree4 ;
	int value;
	tree4.insert(9,9);
	tree4.insert(0,0);
	tree4.insert(2,2);
	tree1 = tree4;
	REQUIRE(tree1.search(9,value));
	REQUIRE(value == 9);
	REQUIRE(!(tree1.search(1,value)));
	REQUIRE(!(value == 111));
	
}

TEST_CASE("(3) to the right") 
{
	bstt<int, int>  tree;
	tree.insert(30,30);
	tree.insert(15,15);
	tree.insert(8,8);
	tree.insert(25,25);
	tree.insert(20,20);
	tree.insert(28,28);
	tree.insert(50,50);
	tree.insert(70,70);
	tree.insert(60,60);
	
	REQUIRE(tree(15) == 25);
	REQUIRE(tree(20) == 25);
	REQUIRE(tree(28) == 30);
	REQUIRE(tree(8) == 15);
	REQUIRE(tree(70) == 0);
	
	tree.clear();
}

TEST_CASE("(4) to the right") 
{
	bstt<int, int>  tree;
	tree.insert(30,30);
	tree.insert(15,15);
	tree.insert(8,8);
	tree.insert(25,25);
	tree.insert(20,20);
	tree.insert(28,28);
	tree.insert(50,50);
	tree.insert(70,70);
	tree.insert(60,60);
	
	cout << endl;
	tree.begin();
	int key;
	while (tree.next(key))
       cout << key << endl;
	
	tree.clear();
}




// 	{	
// 		// if emptree
// 		if (Root == nullptr) {
// 			return false;
// 		}
		
// 		// for first node
// 		if (prevState == nullptr) {
// 			key = InternalState->Key;
// 			prevState = InternalState;
// 			InternalState = InternalState->Right;
// 			return true;
// 		}
		
// 		// end of tree
// 		if (InternalState == nullptr ) 
// 			{
// 				 return false;
// 			}
		
// 		// second to last cases
// 		// if node with largest key has no left child...
// 		if (InternalState->Right == nullptr && 
// 					 InternalState->Left == nullptr) 
// 			{
// 				 key = InternalState->Key;
// 				 InternalState = InternalState->Right;
// 				 return true;
// 			}
// 		// if node with largest key node DOES have a left child...
// 		if (InternalState->Right == nullptr && 
// 					 InternalState->Left->Key == prevState->Key) 
// 			{
// 				 key = InternalState->Key;
// 				 InternalState = InternalState->Right;
// 				 return true;
// 			}
		
// 		// Tree traversal stages
// 		// 
// 		while ( InternalState != nullptr) {
			
// 			// if left child exists that hasn't been traversed yet
// 			if (InternalState->Left != nullptr &&
// 				InternalState->Left->Key != prevState->Key && 
// 				prevState->isThreaded == false)
// 			{
// 				prevState = InternalState;
// 				InternalState = InternalState->Left;
// 			}
			
// 			// prints leftmost child of a given branch
// 			else if ( InternalState->Key < prevState->Key &&
// 					  (prevState->Right == InternalState ||
// 					   prevState->Right == nullptr) ) 
// 			{
// 				key = InternalState->Key;
// 				prevState = InternalState;
// 				InternalState = InternalState->Right;
// 				return true;
// 			}
			
// 			// checks if current is at the highest key
// 			// if not...
// 			if (InternalState->Right != nullptr) 
// 			{
// 				// ...
// 				// check if we can print the right child
// 				if ( InternalState->Right->Key == prevState->Key &&
// 						  InternalState->Left == nullptr ) 
// 				{
// 					key = InternalState->Key;
// 					prevState = InternalState;
// 					InternalState = InternalState->Right;
// 					return true;
// 				}			
// 			}
			
// 			// after left branch is complete, non-threaded traverse
// 			if (InternalState->isThreaded == false) 
// 			{
// 				key = InternalState->Key;
// 				prevState = InternalState;
// 				InternalState = InternalState->Right;
// 				return true;
// 			}
			
// 			// after left branch is complete, threaded traverse
// 			else if (InternalState->isThreaded) 
// 			{
// 				key = InternalState->Key;
// 				prevState = InternalState;
// 				InternalState = InternalState->Right;
// 				return true;
// 			}			
// 		} // end while (tree traversal)
		
// 		return false;    // nothing happens
// 	}
