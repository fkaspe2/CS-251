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

TEST_CASE("(4.1) big tree -- 1..N, balanced?")
{
  avlt<int, int>  tree;

  //
  // insert in order, which will trigger lots of rotations:
  //
  for (int i = 1; i < 4096; ++i)
  {
    tree.insert(i, -i);
  }

  REQUIRE(tree.size() == 4095);
  REQUIRE(tree.height() == 11);  // N = 4096, lgN - 1

  //
  // check the values, stored properly?
  //
  for (int i = 1; i < 4096; ++i)
  {
    int value;

    REQUIRE(tree.search(i, value));
    REQUIRE(value == -i);
    REQUIRE(tree[i] == -i);
  }
  
  REQUIRE((tree % 4094) == 1);
  REQUIRE(tree(4094) == 4095);

  REQUIRE((tree % 4095) == 0);
  REQUIRE(tree(4095) == 0);

  //
  // walk the tree and make sure values in order, i.e. it was
  // rotated properly:
  //
  int key;
  int i = 1;

  tree.begin();
  while (tree.next(key))
  {
    REQUIRE(key == i);
    ++i;
  }

  REQUIRE(i == (tree.size() + 1));

  REQUIRE(tree[0] == 0);
  REQUIRE(tree(0) == 0);
  REQUIRE((tree % 0) == -1);

  REQUIRE(tree[4096] == 0);
  REQUIRE(tree(4096) == 0);
  REQUIRE((tree % 4096) == -1);
}


TEST_CASE("(4.2) big tree 2 -- N..1, balanced?")
{
  avlt<int, int>  tree;

  //
  // insert in order, which will trigger lots of rotations:
  //
  for (int i = 4095; i > 0; --i)
  {
    tree.insert(i, -i);
  }

  REQUIRE(tree.size() == 4095);
  REQUIRE(tree.height() == 11);  // N = 4096, lgN - 1

  //
  // check the values, stored properly?
  //
  for (int i = 4095; i > 0; --i)
  {
    int value;

    REQUIRE(tree.search(i, value));
    REQUIRE(value == -i);
    REQUIRE(tree[i] == -i);
  }
  
//   REQUIRE((tree % 1) == 0);
//   REQUIRE(tree(0) == 0);

//   REQUIRE((tree % 0) == -1);
//   REQUIRE(tree(4095) == 0);

  //
  // walk the tree and make sure values in order, i.e. it was
  // rotated properly:
  //
  int key;
  int i = 1;

  tree.begin();
  while (tree.next(key))
  {
    REQUIRE(key == i);
    ++i;
  }

  REQUIRE(i == (tree.size() + 1));

//   REQUIRE(tree[0] == 0);
//   REQUIRE(tree(0) == 0);
//   REQUIRE((tree % 0) == -1);

//   REQUIRE(tree[4096] == 0);
//   REQUIRE(tree(4096) == 0);
//   REQUIRE((tree % 4096) == -1);
}





TEST_CASE("(4.3) big tree -- get funky?")
{
  avlt<int, int>  tree;

  //
  // insert in order, which will trigger lots of rotations:
  //
  for (int i = 1; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
  for (int i = 5; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 3; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 2; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 8; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 4; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 9; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 7; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 6; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
	for (int i = 10; i < 4096; i = i + 10)
  {
    tree.insert(i, -i);
  }
	
//   REQUIRE(tree.size() == 4095);
//   REQUIRE(tree.height() == 11);  // N = 4096, lgN - 1

//   //
//   // check the values, stored properly?
//   //
//   for (int i = 1; i < 4096; ++i)
//   {
//     int value;

//     REQUIRE(tree.search(i, value));
//     REQUIRE(value == -i);
//     REQUIRE(tree[i] == -i);
//   }
  
// //   REQUIRE((tree % 4094) == 1);
// //   REQUIRE(tree(4094) == 4095);

// //   REQUIRE((tree % 4095) == 0);
// //   REQUIRE(tree(4095) == 0);

//   //
//   // walk the tree and make sure values in order, i.e. it was
//   // rotated properly:
//   //
//   int key;
//   int i = 1;

//   tree.begin();
//   while (tree.next(key))
//   {
//     REQUIRE(key == i);
//     ++i;
//   }

//   REQUIRE(i == (tree.size() + 1));

//   REQUIRE(tree[0] == 0);
//   REQUIRE(tree(0) == 0);
//   REQUIRE((tree % 0) == -1);

//   REQUIRE(tree[4096] == 0);
//   REQUIRE(tree(4096) == 0);
//   REQUIRE((tree % 4096) == -1);
 }
