/*bstt.h*/

// 
// << Frank Kasper >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #04: Threaded BST
//
// Threaded binary search tree
//
// This project creates a threaded binary search tree where each parent with an empty
// rigt child is threaded its parent, or inherits another parent. This allows for 
// inorder traversal through the tree. The purpose of this is to emulate the structure
// of the map data class and understand the architecture behind it in 
// a more meaningful way.
//

#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* InternalState;   // tracks leftmost node in tree for begin()/next()
  bool firstState;       // tracks first condition of InternalState

public:
	//
	// default constructor:
	//
	// Creates an empty tree.
	//
	bstt()
	{
		Root = nullptr;
		Size = 0;
		firstState = true;
	}

	//
	// COPY HELPER
	// called in copy constructor, operator=
	void _copyHelper (NODE* &cur, const NODE* other) {
		if (other == nullptr) {
			cur = nullptr;
			return;
		}
		else {
			// copy data from other
			cur = new NODE();
			cur->Key = other->Key;
			cur->Value = other->Value;
			cur->Left = other->Left;
			cur->Right = other->Right;
			cur->isThreaded = other->isThreaded;
			// recurse
			_copyHelper(cur->Left, other->Left);
			if (other->isThreaded == false){
				_copyHelper(cur->Right, other->Right);
			}
		}
	}

	//
	// copy constructor
	//
	bstt(const bstt& other)
	{
		_copyHelper(this->Root, other.Root);
		this->Size = other.Size;
		this->InternalState = other.InternalState;
		this->firstState = other.firstState;
	}
	
	//
	// DESTRUCTOR HELPER
	// called in destructor, operator=, clear
	void _bsttDestructorHelper (NODE* cur) {
		if (cur == nullptr) {
			return;
		}
		else {
			// recurse
			_bsttDestructorHelper(cur->Left);
			if (!cur->isThreaded){
				_bsttDestructorHelper(cur->Right);
			}
			delete cur;
		}
		this->Size = 0;
	}
	
	//
	// destructor:
	//
	// Called automatically by system when tree is about to be destroyed;
	// this is our last chance to free any resources / memory used by
	// this tree.
	//
	virtual ~bstt()
	{
		 _bsttDestructorHelper(Root);
	}
    
	//
	// operator=
	//
	// Clears "this" tree and then makes a copy of the "other" tree.
	//
	bstt& operator=(const bstt& other)
	{
		_bsttDestructorHelper(Root);
		
		_copyHelper(this->Root, other.Root);
		this->Size = other.Size;

		return *this;
	}
	
	//
	// clear:
	//
	// Clears the contents of the tree, resetting the tree to empty.
	//
	void clear()
	{    
		_bsttDestructorHelper(Root);
		Root = nullptr;
	}


	// 
	// size:
	//
	// Returns the # of nodes in the tree, 0 if empty.
	//
	// Time complexity:  O(1) 
	//
	int size() const
	{
		return Size;
	}


	// 
	// search:
	//
	// Searches the tree for the given key, returning true if found
	// and false if not.  If the key is found, the corresponding value
	// is returned via the reference parameter.
	//
	// Time complexity:  O(lgN) on average
	//
	bool search(KeyT key, ValueT& value) const
	{	
		NODE* cur = Root;
		while (cur != nullptr) {
			if (key == cur->Key) {
				value = cur->Value;
				return true;
			}
			// searches left:
			else if (key < cur->Key) {    
				cur = cur->Left;
			}
			// searches right:
			else {    
				if (cur->isThreaded == false) {
					cur = cur->Right;
				}
				else {
					cur = nullptr;
				}
			}
		} // end while

		return false;
	}


	//
	// insert
	//
	// Inserts the given key into the tree; if the key has already been insert then
	// the function returns without changing the tree.
	//
	// Time complexity:  O(lgN) on average
	//
	void insert(KeyT key, ValueT value)
	{
		NODE* prev = nullptr;
		NODE* cur = Root;
		stack<NODE*> nodes;
		
		// SEARCH
		while (cur != nullptr) {
			// returns if found
			if (key == cur->Key) {
				return;
			}
			// stacks nodes to traverse later
			// stacks until cur = null
			nodes.push(cur);
			
			// search left:
			else if (key < cur->Key) {    
				prev = cur;
				cur = cur->Left;
			}
			// search right:
			else {    
				if (cur->isThreaded == false) {
					prev = cur;
					cur = cur->Right;
				}
				else {
					prev = cur;
					cur = nullptr;
				}
			}
		} // end while
		
		// NEW NODE
		// create node to be inserted
		NODE* newNode = new NODE();
		newNode->Key = key;
		newNode->Value = value;
		newNode->Left = NULL;
		newNode->Right = NULL;
		newNode->isThreaded = true;
		newNode->Height = 0;
		
		// INSERT
		// inserts to Root
		// if tree is empty
		if (prev == NULL) {
			Root = newNode;
		}
		// inserts to left
		// thread newNode to parent
		else if (key < prev->Key) {
			prev->Left = newNode;	
			newNode->Right = prev;   
		}
		// inserts to right
		// thread newNode to wherever parent was threaded
		else {
			newNode->Right = prev->Right;
			prev->Right = newNode;
			prev->isThreaded = false;
		}
		(this->Size)++;
		
		// HEIGHTS
		// update the heights of the tree`
		int HL, HR, newH;
		while (!nodes.empty() ) {
		  cur = nodes.top();
		  nodes.pop();
		  
		  // store height of the left branch of cur
		  if (cur->Left == nullptr) {
			 HL = -1;
		  }
		  else {
			 HL = cur->Left->Height;
		  }
		  // store height of the right branch of cur
		  if (cur->Right == nullptr) {
			 HR = -1;
		  }
		  else {
			 HR = cur->Right->Height;
		  }
		  
		  // take larger of the two
		  if (HL >= HR) {
			 cur->Height = HL + 1;
		  }
		  else {
			 cur->Height = HR + 1;
		  }
		}
		
	}


	//
	// []
	//
	// Returns the value for the given key; if the key is not found,
	// the default value ValueT{} is returned.
	//
	// Time complexity:  O(lgN) on average
	//
	ValueT operator[](KeyT key) const
	{    
		NODE* cur = Root;
		
		while (cur != nullptr) {
			// returns when found
			if (key == cur->Key) {
				return cur->Value;
			}
			// search left:
			else if (key < cur->Key) {    
				cur = cur->Left;
			}
			// search right:
			else {    
				if (cur->isThreaded == false) {
					cur = cur->Right;
				}
				else {
					cur = nullptr;
				}
			}
		} // end while
		return ValueT{ };
	}


	//
	// ()
	//
	// Finds the key in the tree, and returns the key to the "right".
	// If the right is threaded, this will be the next inorder key.
	// if the right is not threaded, it will be the key of whatever
	// node is immediately to the right.
	//
	// If no such key exists, or there is no key to the "right", the
	// default key value KeyT{} is returned.
	//
	// Time complexity:  O(lgN) on average
	//
	KeyT operator()(KeyT key) const
	{
		NODE* cur = Root;
		
		while (cur != nullptr) {
			// need this to stay within tree bounds
			if (cur->Right == nullptr && cur->Key == key) {  
				break;
			}
			// returns when found
			if (key == cur->Key ) {
				return cur->Right->Key;
			}
			// search left:
			else if (key < cur->Key) {    
				cur = cur->Left;
			}
			// search right:
			else {    
				if (cur->isThreaded == false) {
					cur = cur->Right;
				}
				else {
					cur = nullptr;
				}
			}
		} // end while
	
	// no existing key to the right
	return KeyT{ };
	}


	//
	// begin
	//
	// Resets internal state for an inorder traversal.  After the 
	// call to begin(), the internal state denotes the first inorder
	// key; this ensure that first call to next() function returns
	// the first inorder key.
	//
	// Space complexity: O(1)
	// Time complexity:  O(lgN) on average
	//
	// Example usage:
	//    tree.begin();
	//    while (tree.next(key))
	//      cout << key << endl;
	//
	void begin()
	{
		NODE* cur = Root;

		// return if empty
		if (cur == nullptr) {
			InternalState = nullptr;
			return;
		}

		// goes left in tree until NULL is reached
		// this way we can store/access smallest key in next()
		while (cur->Left != nullptr) {
			cur = cur->Left;
		}
		// InternalState is now leftmost node
		InternalState = cur;
	}
		
		
	//
	// next
	//
	// Uses the internal state to return the next inorder key, and 
	// then advances the internal state in anticipation of future
	// calls.  If a key is in fact returned (via the reference 
	// parameter), true is also returned.
	//
	// False is returned when the internal state has reached null,
	// meaning no more keys are available.  This is the end of the
	// inorder traversal.
	//
	// Space complexity: O(1)
	// Time complexity:  O(lgN) on average
	//
	// Example usage:
	//    tree.begin();
	//    while (tree.next(key))
	//      cout << key << endl;
	//  
	bool next(KeyT& key) 
  	{
		// if emptree
		if (Root == nullptr) {
			return false;
		}
		
		// for first node
		if (firstState == true) {
			key = InternalState->Key;
			firstState = false;
			return true;
		}
		
		// if threaded go right
		if (InternalState->isThreaded) {
			InternalState = InternalState->Right;
			if (InternalState != nullptr) {
				key = InternalState->Key;
				return true;
			}
		} 
		
		// if not threaded go left
		else if (InternalState->isThreaded == false) {
			InternalState = InternalState->Right;
			while (InternalState->Left != nullptr) 
			{
				InternalState = InternalState->Left;
			}
			key = InternalState->Key;
			return true;
		}
		
		firstState = true;
		return false;		
	}
  
  
  
	// INORDER HELPER
	// prints all nodes in ascending order
	void _inorder(NODE* cur, ostream& output) const
	{
		if (cur == nullptr) {
			return;  
		}
		// traverse left
		_inorder(cur->Left, output); 
		
		// prints threaded value as well
		if (cur->isThreaded && cur->Right != nullptr) {
			output << "(" << cur->Key 
				   << "," << cur->Value 
				   << "," << cur->Right->Key 
				   << ")" << endl;
		}
		// prints when no thread
		else {
			output << "(" << cur->Key 
				   << "," << cur->Value 
				   << ")" << endl;
		}
		
		// traverse right
		if (cur->isThreaded == false) {
			_inorder(cur->Right, output);
		}
	}
  
  
	//
	// dump
	// 
	// Dumps the contents of the tree to the output stream, using a
	// recursive inorder traversal.
	//
	void dump(ostream& output) const
	{
		output << "**************************************************" << endl;
		output << "********************* BSTT ***********************" << endl;

		output << "** size: " << this->size() << endl;

		//
		// inorder traversal, with one output per line: either 
		// (key,value) or (key,value,THREAD)
		//
		// (key,value) if the node is not threaded OR thread==nullptr
		// (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
		//
		
		// prints everything inorder
		_inorder(Root, output);
		output << "**************************************************" << endl;
	}

};

