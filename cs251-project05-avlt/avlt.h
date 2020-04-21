/*avlt.h*/

//
// Threaded AVL tree
//

#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

template<typename KeyT, typename ValueT>
class avlt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded; // true => Right is a thread, false => non-threaded
    int    Height;     // height of tree rooted at this node
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
  avlt()
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
		cur = other;
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
		cur->Height = other->Height;
		// recurse
		_copyHelper(cur->Left, other->Left);
		if (other->isThreaded == false){
			_copyHelper(cur->Right, other->Right);
		}
	}
  }
	
  //
  // DESTRUCTOR HELPER
  // called in destructor, operator=, clear
  void _avltDestructorHelper (NODE* cur) {
	if (cur == nullptr) {
		return;
	}
	else {
		// recurse
		_avltDestructorHelper(cur->Left);
		if (!cur->isThreaded){
			_avltDestructorHelper(cur->Right);
		}
		delete cur;
	}
	this->Size = 0;
  }
	
  //
  // copy constructor
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt (const avlt& other)
  {
    _copyHelper(this->Root, other.Root);
	this->Size = other.Size;
	this->InternalState = other.InternalState;
	this->firstState = other.firstState;
  }
		
  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~avlt()
  {
     _avltDestructorHelper(Root);
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt& operator=(const avlt& other)
  {
    _avltDestructorHelper(Root);
	_copyHelper(this->Root, other.Root);
	this->Size = other.Size;
	this->InternalState = other.InternalState;
	this->firstState = other.firstState;

	return *this;
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    _avltDestructorHelper(Root);
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
  // height:
  //
  // Returns the height of the tree, -1 if empty.
  //
  // Time complexity:  O(1) 
  //
  int height() const
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) worst-case
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
  // range_search
  //
  // Searches the tree for all keys in the range [lower..upper], inclusive.
  // It is assumed that lower <= upper.  The keys are returned in a vector;
  // if no keys are found, then the returned vector is empty.
  //
  // Time complexity: O(lgN + M), where M is the # of keys in the range
  // [lower..upper], inclusive.
  //
  // NOTE: do not simply traverse the entire tree and select the keys
  // that fall within the range.  That would be O(N), and thus invalid.
  // Be smarter, you have the technology.
  //
  vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
    vector<KeyT>  keys;
	
	// first, search for lower in (threaded) tree
	// if lower is not in the tree, find closest value GREATER than lower
	NODE* cur = Root;
	NODE* prev = nullptr;
	bool foundLower = false;
	
	while (cur != nullptr) {    // check if lower is in tree
		if (lower == cur->Key) {
			keys.push_back(cur->Key);
			foundLower = true;
			break;
		}
		// searches left:
		else if (lower < cur->Key) {
			prev = cur;
			cur = cur->Left;
		}
		// searches right:
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
	} // end search	
	
	if (lower == upper) {
		return keys;
	}
	
	if (foundLower == false) {    // if lower not in tree
		// if range too low
		if (prev->Key > upper) {
			return keys;
		}
		// if lower < prevKey, where prev is within bounds
		if (lower < prev->Key) {
			keys.push_back(prev->Key);
		}
		cur = prev->Right;
	} // end edge cases
	
	// traverse range until curKey <= upper or hits the end
	while ( cur != nullptr && cur->Key <= upper) 
	{			
			// if threaded go right
			if (cur->isThreaded) {
				cur = cur->Right;
			}
			// if not threaded go left
			else if (cur->isThreaded == false) {
				cur = cur->Right;
				while (cur->Left != nullptr) 
				{
					cur = cur->Left;
				}
			}
			
			if (cur != nullptr && cur->Key <= upper) {
				keys.push_back(cur->Key);
			}
	}
	
    return keys;
  }
  
  //
  // Rotation helpers
  //
  // Still need to check if they work and update the threaded nodes 
  // 
  // RR HELPER
  void _rightRotate (NODE* Parent, NODE* N ) 
  {
	 // label & rotate
     NODE* L = N->Left;
	 if (L->isThreaded == false) {
		 NODE* B = L->Right;
		 L->Right = N;
		 N->Left = B;
	 }
	 else {
		 L->Right = N;
		 L->isThreaded = false;
		 N->Left = nullptr;
	 } 
     
     // update parent, link to L
     if (Parent == nullptr) {
        Root = L;
     }
     else if (L->Key < Parent->Key) {
        Parent->Left = L;
     }
     else {
        Parent->Right = L;
     }
     
     //heights    
     int LH, RH, newH;     
     LH = -1;
	 RH = -1;
     if (N->Left != nullptr) {
        LH = N->Left->Height;
     }
     if (N->isThreaded == false && N->Right != nullptr) {
        RH = N->Right->Height;
     }
	 newH = max(LH, RH) + 1;
     N->Height = newH;
     
     
	 LH = -1;
	 RH = -1;
     if (L->Left != nullptr) {
        LH = L->Left->Height;
     }
     
     if (L->isThreaded == false && L->Right != nullptr) {
        RH = L->Right->Height;
     }
     newH = max(LH, RH) + 1;
     L->Height = newH;
	 
  }
  
  //
  // LR HELPER
  void _leftRotate (NODE* Parent, NODE* N) 
  {
     // label & rotate
     NODE* R = N->Right;
	 if (R->Left != nullptr) {
		 NODE* B = R->Left;
		 R->Left = N;
		 N->Right = B;
	 }
	 else {
		 R->Left = N;
		 N->isThreaded = true;
		 N->Right = R;
	 } 
     
     // update parent, link to L
     if (Parent == nullptr) {
        Root = R;
     }
     else if (R->Key > Parent->Key) {
        Parent->Right =R;
     }
     else {
        Parent->Left = R;
     }
         
     //heights     
     int LH, RH, newH;     
     LH = -1;
	 RH = -1;
     if (N->Left != nullptr) {
        LH = N->Left->Height;
     }
     if (N->isThreaded == false && N->Right != nullptr) {
        RH = N->Right->Height;
     }
	 newH = max(LH, RH) + 1;
     N->Height = newH;
     
     LH = -1;
	 RH = -1;
     if (R->Left != nullptr) {
        LH = R->Left->Height;
     }
     
     if (R->isThreaded == false && R->Right != nullptr) {
        RH = R->Right->Height;
     }
     newH = max(LH, RH) + 1;
     R->Height = newH;
	
  }
  
  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.  Rotations are performed
  // as necessary to keep the tree balanced according to AVL definition.
  //
  // Time complexity:  O(lgN) worst-case
  //
  void insert(KeyT key, ValueT value )
  {
		NODE* prev = nullptr;
		NODE* cur = Root;
		stack<NODE*> nodes;
		
		// SEARCH
		while (cur != nullptr) {	
			// insert cur and prev to check heights
			nodes.push(prev);
			nodes.push(cur);
			
			// returns if found
			if (key == cur->Key) {
				return;
			}
			
			// search left:
			if (key < cur->Key) {    
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
		
		nodes.push(prev);
		nodes.push(newNode);
		(this->Size)++;
		
		// HEIGHTS
		// update the heights of the tree`
		while (nodes.size() > 0) {
			NODE* N = nodes.top();
			nodes.pop();
			NODE* Parent = nodes.top();
			nodes.pop();
			
			// compute new height
			int HL = -1;
			int HR = -1;
			int newH;
			if (N->Left != nullptr) {
				HL = N->Left->Height;
			}
			if (N->isThreaded == false && N->Right != nullptr) { 
				HR = N->Right->Height;
			}
			newH = max(HL, HR) + 1;
			N->Height = newH;
			
			// rotate if height diff.=2
			if (HL - HR > 1 || HL - HR < -1) 
			{
				// cases 1-2
				if (newNode->Key < N->Key) {
					NODE* L = N->Left;
					int LLeft = -1;
					int LRight = -1;
					
					if (L->Left != nullptr) 
						LLeft = L->Left->Height;
					if (L->isThreaded == false && L->Right != nullptr)     
						LRight = L->Right->Height;
					
					// case 1
					if (LLeft > LRight) {
						_rightRotate(Parent, N);  
					}
					// case 2
					else if (LLeft < LRight) {
						_leftRotate(N, L);    
						_rightRotate(Parent, N);
					}
				}
				
				// cases 3-4
				else {
					NODE* R = N->Right;
					int RLeft = -1;
					int RRight = -1;
					
					if (R->Left != nullptr)
						RLeft = R->Left->Height;
					if (R->isThreaded == false && R->Right != nullptr )      
						RRight = R->Right->Height;
										
					// case 4
					if (RRight > RLeft) {
						_leftRotate(Parent, N);
					}
					// case 3
					else if (RRight < RLeft) {
						_rightRotate(N, R); 
						_leftRotate(Parent, N);
					}
					
				}
				
			} // end rotate check
			
		} // end height while loop
		
  } // end insert

  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) worst-case
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
  // Time complexity:  O(lgN) worst-case
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
  // %
  //
  // Returns the height stored in the node that contains key; if key is
  // not found, -1 is returned.
  //
  // Example:  cout << tree%12345 << endl;
  //
  // Time complexity:  O(lgN) worst-case
  //
  int operator%(KeyT key) const
  {	
	NODE* cur = Root;

	while (cur != nullptr) {
		// returns when found
		if (key == cur->Key) {
			return cur->Height;
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
	
	// returns if not found
    return -1;
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
  // Time complexity:  O(lgN) worst-case
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
  // Time complexity:  O(lgN) worst-case
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
			   << "," << cur->Height 
			   << "," << cur->Right->Key 
			   << ")" << endl;
	}
	// prints when no thread
	else {
		output << "(" << cur->Key 
			   << "," << cur->Value 
			   << "," << cur->Height 
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
    output << "********************* AVLT ***********************" << endl;

    output << "** size: " << this->size() << endl;
    output << "** height: " << this->height() << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value,height) or (key,value,height,THREAD)
    //
    // (key,value,height) if the node is not threaded OR thread==nullptr
    // (key,value,height,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
	
    // prints everything inorder
	_inorder(Root, output);
	output << "**************************************************" << endl;
  }
 
	
};

