/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;

//////////////////////////////
//case 1
//

TEST_CASE("(2) case 1 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 60 };
  vector<int> heights = { 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;
	
//   for (int key : keys)
//   {
// 	cout << key << endl;
//   }
//   
  //tree.dump(cout);
	
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	
	for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }
}

TEST_CASE("(3) case 1 left of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 76, 29, 100, 31, 17, 20, 12, 5 };
  vector<int> heights = { 3, 1, 1, 0, 0, 2, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }
	
  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(4) case 1 right of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 76, 29, 100, 31, 17, 60, 55, 65, 54 };
  vector<int> heights = { 3, 1, 1, 0, 0, 0, 2, 1, 0, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

////////////////////////////
//case 2
//
// check again
TEST_CASE("(5) case 2 at root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 90};
  vector<int> heights = { 0, 0, 1 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }
	
	//tree.dump(cout);
	
  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	
	for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }
}

TEST_CASE("(6) case 2 left of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 29, 76, 60, 100, 35, 38 };
  vector<int> heights = { 2, 0, 1, 0, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(7) case 2 right of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 50, 150, 125, 130 };
  vector<int> heights = { 2, 0, 0, 0, 1 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	
	
  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  
}



////////////////////////////
//case 3
//

TEST_CASE("(8) case 3 at root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 120, 110, 130, 111 };
  vector<int> heights = { 1, 0, 1, 2, 0, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(9) case 3 left of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 29, 76, 75, 81, 17, 35, 32, 36, 33 };
  vector<int> heights = { 3, 1, 1, 0, 0, 0, 1, 2, 0, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(10) case 3 right of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 50, 150, 200, 175 };
  vector<int> heights = { 2, 0, 0, 0, 1};

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	
  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  
}


////////////////////////////
//case 4
//

TEST_CASE("(11) case 4 at root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 120, 110, 130, 140 };
  vector<int> heights = { 1, 0, 2, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(12) case 4 left of parent")
{
  avlt<int, int>  tree;

  vector<int> keys = { 46, 29, 76, 17, 35, 75, 81, 32, 36, 37 };
  vector<int> heights = { 3, 1, 1, 0, 2, 0, 0, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(13) case 4 right of parent")
{
  avlt<int, int>  tree;
	
  vector<int> keys = { 46, 29, 76, 17, 35, 60, 81, 80, 100, 110 };
  vector<int> heights = { 3, 1, 1, 0, 0, 0, 2, 0, 1, 0};

  for (int key : keys)
  {
    tree.insert(key, -key, cout);
	//cout << key << endl;
  }
	
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

REQUIRE(tree.search(46, value));
REQUIRE(value == -46);
REQUIRE(tree.search(29, value));
REQUIRE(value == -29);
REQUIRE(tree.search(76, value));
REQUIRE(value == -76);
REQUIRE(tree.search(17, value));
REQUIRE(value == -17);
REQUIRE(tree.search(35, value));
REQUIRE(value == -35);
REQUIRE(tree.search(60, value));
REQUIRE(value == -60);
REQUIRE(tree.search(81, value));
REQUIRE(value == -81);
REQUIRE(tree.search(80, value));
REQUIRE(value == -80);
REQUIRE(tree.search(100, value));
REQUIRE(value == -100);
REQUIRE(tree.search(110, value));
REQUIRE(value == -110);
 
//vector<int> keys = { 46, 29, 76, 17, 35, 60, 81, 80, 100, 110 };
//vector<int> heights = { 3, 1, 1, 0, 0, 0, 2, 0, 1, 0};

//REQUIRE((tree % keys[i]) == heights[i]);
	
  //
  // heights correct after rebalance?
  //
//   for (size_t i = 0; i < keys.size(); ++i)
//   {
//     cout << (tree % keys[i]) << "  " << heights[i] << endl;
//   }
//   cout << "test 13?" << endl;
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
	//cout << "test 13?" << endl;
}