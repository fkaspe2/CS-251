// //
// // test case insert and lookup GLOBAL
// //
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


// // THESE WERE USED FOR TESTING OPTION = GLOBAL FOR LOOKUP
// TEST_CASE("(9) insert and lookup GLOBAL") 
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
// 	REQUIRE(symbol == "int");	
	
	
// 	// in s2
// 	table.enterScope("s2");
// 	table.insert("i", "double");
// 	REQUIRE(table.size() == 3);	
// 	REQUIRE(table.lookup("i", symbol));	
// 	REQUIRE(symbol == "int");	
	
	
// 	// back in s1
// 	table.exitScope();
// 	REQUIRE(table.size() == 2);	
// 	REQUIRE(table.lookup("i", symbol));	
// 	REQUIRE(symbol == "int");	
		
// }