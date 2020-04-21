//
// test case overwrite variable in scopes
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


TEST_CASE("(3) overwrite scope variables test") 
{
	symtable<string, string>  table;
	string symbol;
	
	//
	// inside global scope
	//
	table.enterScope("global");
	
	table.insert("i", "int");
	table.insert("j", "double");
	
	//
	// inside x scope
	//
	table.enterScope("x");
	
	// make sure size stays same and k is just overwritten
	table.insert("k", "char");
	REQUIRE(table.size() == 3);
	
	table.insert("k", "string");
	REQUIRE(table.size() == 3);
}

