#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("(10) insert tests") 
{
	//  <key, data>
	bstt<int, int>  tree;
	//int value;
	
	tree.insert(30,30);
	tree.insert(15,15);
	tree.insert(8,8);
	tree.insert(50,50);
	tree.insert(70,70);
	tree.insert(60,60);
	tree.insert(25,25);
	tree.insert(20,20);
	tree.insert(28,28);
			
	tree.begin();
	int key;
	cout << endl << "Next my son:" << endl;
// 	tree.next(key, std::cout);
// 	cout << "in main " << key << endl;
// 	tree.next(key, std::cout);
// 	cout << "in main " << key << endl;
// 	tree.next(key, std::cout);
// 	cout << "in main " << key << endl;
// 	tree.next(key, std::cout);
// 	cout << "in main " << key << endl;
// 	tree.next(key, std::cout);
// 	cout << "in main " << key << endl;
	
	while (tree.next(key))
       cout << key << endl;
	
	
	//tree.dump(std::cout);
	
	
	//tree.clear();
	//REQUIRE(tree.size() == 0);
}


TEST_CASE("(11) insert tests") 
{
	//  <key, data>
	bstt<int, int>  tree;
	//int value;
	
	tree.insert(30,30);
	tree.insert(15,15);
	tree.insert(8,8);
	tree.insert(6,6);
	tree.insert(7,7);
	tree.insert(4,4);
	tree.insert(50,50);
	tree.insert(70,70);
	tree.insert(25,25);
	tree.insert(20,20);
	tree.insert(18,18);
	tree.insert(19,19);
	tree.insert(28,28);
	tree.insert(29,29);
	tree.insert(2,2);
	tree.insert(3,3);
	tree.insert(75,75);
	tree.insert(45,45);
	tree.insert(35,35);
	tree.insert(46,46);
	tree.insert(73,73);
	tree.insert(69,69);
	tree.insert(74,74);
	
	REQUIRE(tree(2) == 3);
	REQUIRE(tree(3) == 4);
	REQUIRE(tree(4) == 6);
	REQUIRE(tree(6) == 7);
	REQUIRE(tree(7) == 8);
	REQUIRE(tree(8) == 15);
	REQUIRE(tree(15) == 25);
	REQUIRE(tree(18) == 19);
	REQUIRE(tree(19) == 20);
	REQUIRE(tree(20) == 25);
	REQUIRE(tree(25) == 28);
	REQUIRE(tree(28) == 29);
	REQUIRE(tree(29) == 30);
	REQUIRE(tree(30) == 50);
	REQUIRE(tree(70) == 75);
	REQUIRE(tree(50) == 70);
	REQUIRE(tree(35) == 45);
	REQUIRE(tree(45) == 46);
	REQUIRE(tree(46) == 50);
	REQUIRE(tree(75) == 0);
	REQUIRE(tree(69) == 70);
	REQUIRE(tree(74) == 75);
	REQUIRE(tree(73) == 74);
		
	tree.begin();
	int key;
	cout << endl << "Next my son:" << endl;
	// 23
	
	for (int i = 0; i < 23; i++) {
		
	}
	while (tree.next(key))
       cout << key << endl;
	
	
	//tree.dump(std::cout);
	
	
	//tree.clear();
	//REQUIRE(tree.size() == 0);
}