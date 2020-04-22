/*hashmap.h*/

//
// <<Frank Kasper>>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #06: hashing
//
// References: original non-collision code written by Prof. Hummel (UIC)
// 
// hashmap implements a hash table that allows collision (via linear probing).
// The class provides the underlying hash table along with insert() and search() 
// functions; the user of this class must provided a Hash(key, N) function that 
// hashes the given key and returns an integer in the range 0..N-1, 
// inclusive, if the key is valid.  If the key is invalid, the Hash() 
// function must return a negative value.
//
// The hash function is provided in the calls to insert and search.
// Pass the name of your hash function as the 3rd parameter.  Example:
//
//   int myHash(string key, int N)
//   { ... }
//
//   int N = 10000;
//   hashmap<string, double>  hmap(N);  
//
//   if (hmap.insert("deep-dish pizza", 19.99, myHash))
//     cout << "inserted" << endl;
//   else
//     cout << "not inserted?!" << endl;
// 

#pragma once

#include <iostream>
#include <functional>
#include <set>

using namespace std;

template<typename KeyT, typename ValueT>
class hashmap
{
private:
  struct HashEntry
  {
    bool   ContainsData;  // false => empty, true => contains data
    KeyT   Key;           // (key, value)
    ValueT Value;

    HashEntry()
    {
      ContainsData = false;
    }
  };

  HashEntry* HT;  // hash table array of structs
  int        N;   // capacity of hash table (# of locations or array size)

public:
  //
  // constructor: N is the size of the underlying hash table
  //
  hashmap(int N)
  {
    this->N = N;
    this->HT = new HashEntry[N];
  }
  
  //
  // destructor
  //
  virtual ~hashmap()
  {
    delete[] this->HT;
  }
  
  //
  // copy constructor
  //
  hashmap(const hashmap& other)
  {	
	this->N = other.N;
	this->HT = new HashEntry[N];
	
	for (int i = 0; i < N; i++) {
		this->HT[i].ContainsData = other.HT[i].ContainsData; 
		if (other.HT[i].ContainsData) {
			this->HT[i].Key = other.HT[i].Key;                    
			this->HT[i].Value = other.HT[i].Value;
		}
	}
  }
  
  //
  // operator=
  //
  hashmap& operator=(const hashmap& other)
  {
    delete[] this->HT;
	
	this->N = other.N;
	this->HT = new HashEntry[N];
	
	for (int i = 0; i < N; i++) {
		this->HT[i].ContainsData = other.HT[i].ContainsData; 
		if (other.HT[i].ContainsData) {
			this->HT[i].Key = other.HT[i].Key;                    
			this->HT[i].Value = other.HT[i].Value;
		}
	}
	
	return *this;
  }

  //
  // getN
  //
  // Returns the capacity of the hash table, i.e. the value N that
  // was passed to the constructor.
  //
  int getN() const
  {
    return this->N;
  }

//
// insert
//
// Inserts the given (key, value) pair into the hash table, overwriting
// the previous value if already inserted.  If the insert was successful
// then true is returned, otherwise false is returned (meaning the key
// was not hashed successfully, e.g. due to improper formatting).
//
// NOTE: the caller must provide a function Hash(key, N) that returns
// an integer in the the range 0..N-1, inclusive, if the key is valid.
// If the key is invalid, the hash function must return a negative
// integer. The hash function is provided by simply calling insert
// with the name of your hash function.  Example:
//
//   int myHash(string key, int N)
//   { ... }
//
//   int N = 10000;
//   hashmap<string, double>  hmap(N);  
//
//   if (hmap.insert("deep-dish pizza", 19.99, myHash))
//     cout << "inserted" << endl;
//   else
//     cout << "not inserted?!" << endl;
//
bool insert(KeyT key, ValueT value, function<int(KeyT,int)> Hash)
{
	//
	// Call the provided hash function with the key, and N, the size
	// of our hash table:
	//
	
	int index = Hash(key, N);
	
	//
	// insert:
	//
	if (index < 0 || index >= N)  // invalid key or hash function:
	{
		return false;
	}
	
	// searches for open index
	while (HT[index].ContainsData ) 
	{
		// overwrites if key is in table
		if (HT[index].Key == key) {
			HT[index].Value = value;        
			return true;
		}
		
		index++;
		if (index == N ) {index = 0;}	
		
	}
	
	// stores data
	HT[index].Key = key;
	HT[index].Value = value;
	HT[index].ContainsData = true;  
	return true;
}

  //
  // search
  //
  // Searches the hash table for the matching key, and if found then
  // (1) the value is returned via the reference parameter and (2) true
  // is returned.  If the key could not be found, or if the hash 
  // function returned an invalid value (e.g. due to an improperly 
  // formatted key), then false is returned.
  //
  // NOTE: the caller must provide a function Hash(key, N) that returns
  // an integer in the the range 0..N-1, inclusive, if the key is valid.
  // If the key is invalid, the hash function must return a negative
  // integer. The hash function is provided by simply calling search
  // with the name of your hash function.  Example:
  //
  //   int myHash(string key, int N)
  //   { ... }
  //
  //   int N = 10000;
  //   hashmap<string, double>  hmap(N);
  //   ...
  //   double price;
  //   if (hmap.search("deep-dish pizza", price, myHash))
  //     cout << "deep-dish piazza costs " << price << endl;
  //   else
  //     cout << "not found?!" << endl;
  //
  bool search(KeyT key, ValueT& value, function<int(KeyT,int)> Hash) const
  {
    //
    // Call the provided hash function with the key, and N, the size
    // of our hash table:
    //
    
	int index = Hash(key, N);
	int initialIndex = index; // will track for empty hash table
	
    //
    // search:
    //
    if (index < 0 || index >= N)  // invalid key or hash function:
    {
      return false;
    }
	
	while (HT[index].ContainsData )
	{
		if (HT[index].Key == key) {
			value = HT[index].Value;        
			return true;
		}

		index++;
		if (index == N ) { index = 0; }
		if (index == initialIndex) { return false; } // if table is empty / full
	}
	
	return false;
  }
  
  
  //
  // collect()
  // 
  // gets keys from hashtable, returns values in set form
  // 
  set<KeyT> collect() 
  {
	  set<KeyT> s;
	  
	  for (int i = 0; i < N ; i++) {
		  if (HT[i].ContainsData)
			  s.insert(HT[i].Key);
	  }
	  
	  return s;
  }
  
};
