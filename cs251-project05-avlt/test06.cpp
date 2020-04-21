#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) big boy -- EFFICIENCY")
{
  avlt<int, int>  tree;

  //
  // insert in order, which will trigger lots of rotations:
  //
  for (int i = 1; i < 1000001; ++i)
  {
    tree.insert(i, -i);
  }

  REQUIRE(tree.size() == 1000000);
  //REQUIRE(tree.height() == 11);  // N = 4096, lgN - 1

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
