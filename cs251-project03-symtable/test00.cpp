//
// empty test!
//
// << Frank Kasper >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include <string>
#include "symtable.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("(0) initially empty") 
{
	symtable<string, string> table;
	
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
}