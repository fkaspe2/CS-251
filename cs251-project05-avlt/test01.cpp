/*test01.cpp*/

//
// Unit tests for threaded AVL tree
//

#include <iostream>
#include <vector>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree") 
{
  avlt<int, int>  tree;

  REQUIRE(tree.size() == 0);
  REQUIRE(tree.height() == -1);
}

TEST_CASE("(99) tra tests") 
{
	avlt<int, int>  tree;
	tree.insert(200,200, cout);
	tree.insert(100,100, cout);
	tree.insert(50,50, cout);
	REQUIRE(tree.height() == 1);
	
	tree.insert(150,150, cout);
	tree.insert(125,125, cout);
	REQUIRE(tree.height() == 2);
	
	tree.insert(51,51, cout);
	tree.insert(52,52, cout);
	REQUIRE(tree.height() == 2);
	
	tree.insert(195,195, cout);
	tree.insert(197,197, cout);
	REQUIRE(tree.height() == 3);
	
	
	
	
	
	//tree.clear();
}