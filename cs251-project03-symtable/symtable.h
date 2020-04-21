/*symtable.h*/

// 
// << Frank Kasper >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  deque<Scope> myscope;   // stores scopes in deque:
						  // .front() is the lowest level ie.global
						  // .back() is the highest/ deepest level
  int numKeys;            // tracks number of keys in symtable
	
public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
	numKeys = 0;
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const
  {	
    return numKeys;
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  {    
	// returns # scopes within myscope deque
    return myscope.size();
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  {
	// adds new scope onto back of the deque
	myscope.push_back(name);
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
	// check if there is a scope to exit from
	if (myscope.size() == 0) {
		return;
	}
	  
	// removes (pops) scope from back of deque
	if (myscope.size() > 0) {
		numKeys = numKeys - myscope.back().Symbols.size();
		myscope.pop_back();
	}
  }

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
	// check if there is a scope to exit from
	if (myscope.size() < 0) {
		throw invalid_argument("symtable.h::curScope");
	}
	
	return myscope.back();
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {	
	// insert new key if it doesnt already exist
	if (myscope.back().Symbols.count(key) == 0) {
		myscope.back().Symbols[key] = symbol;
		numKeys++;
	}
	
	// if key already exists just replace the symbol
	else {
		myscope.back().Symbols[key] = symbol;
	}
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
	Scope tempScope;
	
	// FOR "ALL"
	if (option == ScopeOption::ALL) 
	{
		// search through list of scopes starting from the deepest level (current)
		for (int i = myscope.size(); i > 0; i--) 
		{
			tempScope = myscope[i-1];
			// if the key was found return its symbol
			if (!(tempScope.Symbols.find(key) == tempScope.Symbols.end()) ) 
			{
				symbol = tempScope.Symbols.find(key)->second;
				return true;
			}
		}
	}
	  
	// FOR "CURRENT"
	else if (option == ScopeOption::CURRENT) 
	{
		// only search deepest (current) scope
		tempScope = myscope.back();
		// if the key was found return its symbol
		if (!(tempScope.Symbols.find(key) == tempScope.Symbols.end()) ) 
		{
			symbol = tempScope.Symbols.find(key)->second;
			return true;
		}
	}
	  
	// FOR "GLOBAL"
	else 
	{
		// only search lowest level (global) scope
		tempScope = myscope.front();
		// if the key was found return its symbol
		if (!(tempScope.Symbols.find(key) == tempScope.Symbols.end()) ) 
		{
			symbol = tempScope.Symbols.find(key)->second;
			return true;
		}
	}
	
	return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL) {
      output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  // prints whole table
	  Scope scopes;
	  for (int i = myscope.size(); i > 0; i--) 
	  {
	    scopes = myscope[i-1];
		output << "** " << scopes.Name << " **" << endl;
		for (auto& maps: scopes.Symbols) 
		{
			output << maps.first << ": " << maps.second << endl;
		}
	  }
	}
	
	else if (option == ScopeOption::CURRENT) 
	{
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
      output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  output << "** " << myscope.back().Name << " **" << endl;
	    // prints current scope
		for (auto& maps: myscope.back().Symbols) 
		{
			output << maps.first << ": " << maps.second << endl;
		}
	}
	  
	else // global:
	{ 
      output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
      output << "** " << myscope.front().Name << " **" << endl;
		// prints first scope
		for (auto& maps: myscope.front().Symbols) 
		{
			output << maps.first << ": " << maps.second << endl;
		}
	}
	
    output << "**************************************************" << endl;
  }

};
