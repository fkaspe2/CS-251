/*test01.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("(99) jul") 
{
	bstt<int, int>  tree;
	tree.insert(200,200);
	tree.insert(100,100);
	tree.insert(50,50);
	tree.insert(150,150);
	tree.insert(125,125);
		
	cout << endl;
	tree.begin();
	int key;
	while (tree.next(key))
       cout << key << endl;
	
	tree.clear();
}