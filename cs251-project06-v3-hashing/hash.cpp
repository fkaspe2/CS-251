/*hash.cpp*/

//
// Frank Kasper
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Hash functions for project 6
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/
#include <climits>

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}

//
// hashById()
// 
// Hashes given a station id. Direct hash using % operator
// 
int HashById(string input, int N)
{	
	if (!isNumeric(input)) {return -1;}
	int id = stoi(input);
	int index = id % N;

	return index;
}

//
// HashByAbb
//
// Dan Bernstein method
//
int HashByAbb(string input, int N)
{
	unsigned long long hash = 5381;
	for(char c : input) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash % N;
}

//
// HashByTrip
//
// Find hash for tripid, already omitted "Tr"
//
int HashByTrip(string input, int N)
{
	int id = stoi(input);
	int index = id % N;

	return index;
}

//
// HashByBike
//
// Find hash for bikeid, already omitted "B"
//
int HashByBike(string input, int N)
{
	int id = stoi(input);
	int index = id % N;

	return index;
}

//
// Hash
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int Hash(string input, int N)
{
	// hash by station id
	if (isNumeric(input)) {return HashById(input, N);}
	
	// trip id
	else if (input[0] == 'T' && input[1] == 'r') 
	{
		string temp = input.erase(0,2);
		if (isNumeric(temp)) {return HashByTrip(temp, N);}
	}
	
	// bike id
	else if (input[0] == 'B' ) 
	{
		string temp = input.erase(0,1);
		if (isNumeric(temp)) {return HashByBike(temp, N);}
	}
	
	// hash by abbrev
	else {return HashByAbb(input, N);}
	
	return -1;
}

