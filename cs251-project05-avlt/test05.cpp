#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(13) case 4 right of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 29, 76, 17, 35, 60, 81, 80, 100, 107,  110 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }
	
	
	vector<int> temp;
	
	
	
	//inorder
	//vector<int> keys = { 17, 29, 35, 46, 60, 76, 80, 81, 100, 107, 110 };
	
	// exact to exact
	temp = tree.range_search(35, 100);
	cout << "35-100" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 7);
	
	temp = tree.range_search(33, 100);
	cout << endl << "33-100" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 7);
	
	temp = tree.range_search(36, 100);
	cout << endl << "36-100" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 6);
	
	temp = tree.range_search(35, 105);
	cout << endl << "35-105" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 7);
	
	temp = tree.range_search(35, 110);
	cout << endl << "35-110" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 9);
	
	temp = tree.range_search(35, 120);
	cout << endl << "35-120" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 9);
	
	temp = tree.range_search(35, 99);
	cout << endl << "35-99" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 6);
	
	temp = tree.range_search(250, 300);
	cout << endl << "250-300" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 0);
	
	temp = tree.range_search(5, 10);
	cout << endl << "5-10" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 0);
	
	temp = tree.range_search(0, 46);
	cout << endl << "0-46" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 4);
	
	temp = tree.range_search(17, 110);
	cout << "17-110" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 11);
	
	temp = tree.range_search(17, 120);
	cout << "17-120" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 11);
	
	temp = tree.range_search(16, 110);
	cout << "16-110" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 11);
	
	temp = tree.range_search(16, 120);
	cout << "16-120" << endl;
	for (int key : temp) {
    cout << key << endl;
	}
	REQUIRE(temp.size() == 11);
	
	
// 	avlt<int, int> bigtree;
// 	vector<int>  big;
	
// 	for (int i = 1; i < 4096; ++i)
//     {
// 	bigtree.insert(i, -i);
//     }
// 	REQUIRE(bigtree.size() == 4095);
	
	
// 	big = bigtree.range_search(0, 0);
// 	cout << endl << "0-0" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 0);
	
	
// 	big = bigtree.range_search(0, 1);
// 	cout << endl << "0-1" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 1);
	
	
// 	big = bigtree.range_search(0, 2);
// 	cout << endl << "0-2" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 2);
	
	
// 	big = bigtree.range_search(1, 2);
// 	cout << endl << "0-2" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 2);
	
	
// 	big = bigtree.range_search(0, 2);
// 	cout << endl << "0-2" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 2);
	
	
// 	big = bigtree.range_search(-1, 0);
// 	cout << endl << "0-2" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 0);
	
	
// 	big = bigtree.range_search(1, 1);
// 	cout << endl << "0-2" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 1);
	
//   avlt<int, int>  tree;
//   vector<int> keys = { 46, 29, 76, 17, 35, 60, 81, 80, 100, 107,  110 };

//   for (int key : keys)
//   {
//     tree.insert(key, -key);
//   }
// 	vector<int> temp;
	
	
	
	avlt<int, int> bigtree;
	
	for (int i = 1; i < 21; ++i)
    {
	bigtree.insert(i, -i);
    }
	REQUIRE(bigtree.size() == 20);
	for (int i = 1; i < 21; ++i)
    {
    int value;
    REQUIRE(bigtree.search(i, value));
    REQUIRE(value == -i);
    REQUIRE(bigtree[i] == -i);
    }
	
// 	vector<int> data = {100, 50, 150, 25, 75, 125, 200, 110, 175};
// 	for (int key : data)
//     {
//     bigtree.insert(key, -key);
//     }
	
	vector<int>  big;
		
	for (int i = 1; i < 19; ++i)
    {
	cout << endl << i << "-" << i+2 << endl;
	big = bigtree.range_search(i, i+2);
	REQUIRE(big.size() == 3);
    }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
// 	big = bigtree.range_search(5, 24);
// 	cout << endl << "5-24" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 0);
	
// 	big = bigtree.range_search(5, 25);
// 	cout << endl << "5-25" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 1);
	
	
	
	
// 	big = bigtree.range_search(125, 180);
// 	cout << endl << "125-180" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 3);
	
// 	big = bigtree.range_search(126, 180);
// 	cout << endl << "126-180" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 2);
	
// 	big = bigtree.range_search(151, 175);
// 	cout << endl << "151-175" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 1);
	
// 	big = bigtree.range_search(151, 200);
// 	cout << endl << "151-200" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 2);
	
// 	big = bigtree.range_search(151, 174);
// 	cout << endl << "151-174" << endl;
// 	for (int key : big) {
//     cout << key << endl;
// 	}
// 	REQUIRE(big.size() == 0);
	
	
	
	
	
	
	
	
	
	
}