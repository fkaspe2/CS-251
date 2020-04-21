//
// test case insert and lookup CURRENT
//
// << Frank Kasper >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

// #include <iostream>
// #include "symtable.h"
// #include "catch.hpp"
// using namespace std;

// // THESE WERE USED FOR TESTING OPTION = CURRENT FOR LOOKUP
// TEST_CASE("(8) insert and lookup CURRENT") 
// {
// 	symtable<string, string>  table;
// 	string symbol;
	
// 	//
// 	// inside global scope
// 	//
// 	table.enterScope("global");
// 	table.insert("i", "int");
// 	REQUIRE(table.size() == 1);	
// 	REQUIRE(table.lookup("i", symbol));	
// 	REQUIRE(symbol == "int");	
	
	
// 	// in s1
// 	table.enterScope("s1");
// 	table.insert("i", "char");
// 	REQUIRE(table.size() == 2);	
// 	REQUIRE(table.lookup("i", symbol));
// 	REQUIRE(symbol == "char");
	
	
// 	// in s2
// 	table.enterScope("s2");
// 	table.insert("i", "double");
// 	REQUIRE(table.size() == 3);	
// 	REQUIRE(table.lookup("i", symbol));	
// 	REQUIRE(symbol == "double");	
	
	
// 	// back in s1
// 	table.exitScope();
// 	REQUIRE(table.size() == 2);	
// 	REQUIRE(table.lookup("i", symbol));	
// 	REQUIRE(symbol == "char");	
	
		
// }