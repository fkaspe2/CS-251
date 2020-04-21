//
// test case insert in different scopes
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


TEST_CASE("(2) check scope layers test") 
{
	symtable<string, string>  table;
	string symbol;
	
	// add j to global
	table.enterScope("global");
	table.insert("j", "double");
	
	// overwrite j in x
	table.enterScope("x");
	table.insert("k", "char");
	table.insert("j", "int");
	
	// check if j is int in x
	REQUIRE(table.lookup("j", symbol));
    REQUIRE(symbol == "int");
    REQUIRE(table.lookup("k", symbol));
    REQUIRE(symbol == "char");
	
	table.exitScope();
	
	// check if j is double in global
	REQUIRE(table.lookup("j", symbol));
    REQUIRE(symbol == "double");
		
}