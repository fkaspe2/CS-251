//
// test case .curr()
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


TEST_CASE("(6) curr empty") 
{
	symtable<string, string>  table;
	symtable<string, string>::Scope  scope;
	
	// checks that each scope has its own variables at the currscopes...
	// in global
	table.enterScope("global");	
	table.insert("i", "int");
	table.insert("j", "double");
	REQUIRE(table.size() == 2);	
	
	scope = table.curScope();
	REQUIRE(scope.Symbols.size() == 2);	
	REQUIRE(scope.Symbols.at("i") == "int");
	REQUIRE(scope.Symbols.at("j") == "double");
	
	
	// in "x"
	table.enterScope("x");
	table.insert("i", "int");
	table.insert("j", "int");
	REQUIRE(table.size() == 4);	
	
	scope = table.curScope();
	REQUIRE(scope.Symbols.size() == 2);	
	REQUIRE(scope.Symbols.at("i") == "int");
	REQUIRE(scope.Symbols.at("j") == "int");
	
	
	// in "y"
	table.enterScope("y");
	table.insert("i", "char");
	table.insert("j", "char");
	REQUIRE(table.size() == 6);	

	scope = table.curScope();
	REQUIRE(scope.Symbols.size() == 2);	
	REQUIRE(scope.Symbols.at("i") == "char");
	REQUIRE(scope.Symbols.at("j") == "char");
	
	
	// in "x" again
	table.exitScope();
	table.insert("i", "string");
	table.insert("j", "char");
	REQUIRE(table.size() == 4);	

	scope = table.curScope();
	REQUIRE(scope.Symbols.size() == 2);	
	REQUIRE(scope.Symbols.at("i") == "string");
	REQUIRE(scope.Symbols.at("j") == "char");
	
}