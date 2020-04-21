//
// test case DUMP
//
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


TEST_CASE("(10) dump") 
{
	symtable<string, string>  table;
	
	// enter arbitrary data
	table.enterScope("global");
	table.insert("x", "int");
	table.insert("y", "int");
	table.insert("z", "int");
	
	table.enterScope("s1");
	table.insert("x", "char");
	table.insert("y", "char");
	table.insert("z", "char");
	
	table.enterScope("s2");
	table.insert("x", "int");
	table.insert("y", "char");
	table.insert("z", "[|B^)-/-<");
	
	// print it all out!
	table.dump(std::cout, symtable<string,string>::ScopeOption::ALL);
	table.dump(std::cout, symtable<string,string>::ScopeOption::CURRENT);
	table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
	
}