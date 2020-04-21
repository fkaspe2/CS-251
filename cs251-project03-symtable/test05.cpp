//
// test case .size() empty
//
// << Frank Kasper >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include "symtable.h"
#include "catch.hpp"
using namespace std;


TEST_CASE("(5) size myscope.maps is empty") 
{
	symtable<string, string>  table;
	
	// check if starts empty
	REQUIRE(table.size() == 0);
	
	// enter empty scopes
	table.enterScope("global");
	REQUIRE(table.size() == 0);	
	table.enterScope("x");
	REQUIRE(table.size() == 0);	
	
	// exit scopes
	table.exitScope();
	REQUIRE(table.size() == 0);	
	
}