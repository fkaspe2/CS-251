//
// test case basic enterScope, exit scope, and numscopes
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


TEST_CASE("(4) basic enterScope, exitScope, and numscopes") 
{
	symtable<string, string>  table1;
	
	// check if starts empty
	REQUIRE(table1.numscopes() == 0);
	
	// check if enterScope() adds scope
	table1.enterScope("global");
	REQUIRE(table1.numscopes() == 1);
	
	table1.enterScope("x");
	REQUIRE(table1.numscopes() == 2);
	
	// checks to add scopes of same name
	table1.enterScope("x");
	REQUIRE(table1.numscopes() == 3);
	
	
	// now remove one from the back
	table1.exitScope();
	REQUIRE(table1.numscopes() == 2);
	table1.exitScope();
	REQUIRE(table1.numscopes() == 1);	
	table1.exitScope();
	REQUIRE(table1.numscopes() == 0);		
	table1.exitScope();
	REQUIRE(table1.numscopes() == 0);
	
}

