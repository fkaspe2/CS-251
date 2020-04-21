/*mymatrix.h*/

// 
// Frank Kasper
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");
       
    Rows = new ROW[R];
    NumRows = R;
    
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  // an array with C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }  
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  { 
    NumRows = other.NumRows;
    Rows = new ROW[NumRows];
    Rows = other.Rows;    
  }

  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
  
  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");
    
    // checks because size colsize shouldn't decrease
    if (C > Rows[r].NumCols) 
	{
        T *temp = new T[C];    // create temp array of desired size
        
		// copy over data from Rows to temp
        for (int c = 0; c < Rows[r].NumCols; ++c) 
		{
            temp[c] = Rows[r].Cols[c];
        }
		
		// free memory
        Rows[r].NumCols = C;
        delete [] Rows[r].Cols;
        Rows[r].Cols = temp;
    }
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");
        
    int r;
    int c;
    
	//
    // take this route if we want to grow the number of rows
    //
	if (R > NumRows) {
        // creates a temporary empty matrix of desired size
        ROW* temp = new ROW[R];
        
		// loops thru rows
        for (r = 0; r < R; r++) 
		{
			temp[r].NumCols = Rows[r].NumCols;
			
            // grows # of columns if it's less than C
            if (C < temp[r].NumCols) 
			{
                temp[r].Cols = new T[temp[r].NumCols];
                // allows the creation of new rows
                if (r >= NumRows) {
                    temp[r].NumCols = C;
                }
            }
            // else keep # of columns the same
            else 
			{
                temp[r].Cols = new T[C];
                temp[r].NumCols = C;
            }
        } // end for

        // copies data from Rows to temp
        for (r = 0; r < NumRows; r++) {
            for (c = 0; c < Rows[r].NumCols; c++) {
                temp[r].Cols[c] = Rows[r].Cols[c];
            }
        }

        // replaces Rows with temp
        Rows = new ROW[R];
        for (r = 0; r < R; r++) 
		{
            Rows[r].Cols = temp[r].Cols;
            Rows[r].NumCols = temp[r].NumCols;
        }
        
        NumRows = R;
        delete [] temp;
    }
    
	//
    // alternatively, take this route if we DON'T want to grow the number of rows
    //
	if (R < NumRows) {
        ROW* temp = new ROW[NumRows];
        
        for (r = 0; r < NumRows; r++) 
		{
			temp[r].NumCols = Rows[r].NumCols;
			
            // grows # of columns if it's less than C
            if (C < temp[r].NumCols) 
			{
                temp[r].Cols = new T[temp[r].NumCols];
            }
            // else keep # of columns the same
            else 
			{
                temp[r].Cols = new T[C];
                temp[r].NumCols = C;
            }
        } // end for

        // copies data from Rows to temp
        for (r = 0; r < NumRows; r++) {
            for (c = 0; c < Rows[r].NumCols; c++) {
                temp[r].Cols[c] = Rows[r].Cols[c];
            }
        }

        // replaces Rows with temp
        for (r = 0; r < NumRows; r++) {
            Rows[r].Cols = new T[C];
            Rows[r].Cols = temp[r].Cols;
            Rows[r].NumCols = temp[r].NumCols;
        }
        delete [] temp;
    }    
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int N = 0;
    // counts the total number of elements
    for (int r = 0; r < NumRows; ++r)
	{
       N += Rows[r].NumCols;
    }
    return N;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");
    
    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result;
        
    // matches result to number of rows in matrix
    result.grow(NumRows, 1);
    
    // grows each column and copies over data from Rows
    for (int r = 0; r < result.numrows(); r++) 
	{
        for (int c = 0; c < result.numcols(r); c++) 
		{
            result.growcols(r, Rows[r].NumCols);
            result(r,c) = scalar * Rows[r].Cols[c];
        }    
    }
    return result;
  }

  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result(NumRows, other.numcols(0));

    //
    // both matrices must be rectangular for this to work:
    //
    int r;
    for (r = 0; r < NumRows; r++) 
	{
        if (Rows[0].NumCols != Rows[r].NumCols)
            throw runtime_error("mymatrix::*: this not rectangular");
    }
    for (r = 0; r < other.numrows(); r++) 
	{
        if (other.numcols(0) != other.numcols(r))
            throw runtime_error("mymatrix::*: other not rectangular");
    }
    
    //
    // Both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    // if (this matrix's # of columns != other matrix's # of rows)
    //   throw runtime_error("mymatrix::*: size mismatch");
    
    if (Rows[0].NumCols != other.numrows()) 
          throw runtime_error("mymatrix::*: size mismatch");
          
    //
    // Okay, we can multiply:
    //
 
    T product = T{};   // holds product between matrix elements
    T sum = T{};       // holds the sums of the products
                       // gets put into results 
    
    int i = 0;
    int j = 0;
    int k = 0;
    int rM1 = 0;   // scans rows of M1
    int cM1 = 0;   // scans cols of M1
    int rM2 = 0;   // scans rows of M2
    int cM2 = 0;   // scans cols of M2
    
    while (i < NumRows) // loops thru M1 rows
	{ 
        while (j < other.Rows[0].NumCols) // loops thru M2 cols
		{      
            while (k < other.NumRows) // loops thru M2 rows
			{          
                product = Rows[rM1].Cols[cM1] * other.Rows[rM2].Cols[cM2];
                sum += product;
                cM1++;   //advance col in M1
                rM2++;   //advance row in M2
                product = 0;
                k++;
            }   
			
            result.Rows[rM1].Cols[cM2] = sum;
            sum = 0;     // resets the sum for each row/col operation
            cM1 = 0;     // advances to next col in M2
            rM2 = 0;
            k = 0;
            cM2++;       
            j++;
        }
		
        cM2 = 0;    // advances to next row in M1
        j = 0;
        rM1++;   
        i++;
    }
	
    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
