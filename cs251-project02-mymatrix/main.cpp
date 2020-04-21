// 
// Frank Kasper
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//
//
// main.cpp 
// (for testing purposes only)
//
// This file was used to test the functionality of 
// my mymatrix.h file. There are only basic tests here, such as
// inserting elements, adding empty spaces to a row/ column, 
// or returning specific attributes of the matrix (size, etc)
// 

#include <iostream>
#include <fstream>
#include <string>
#include "mymatrix.h"

using namespace std;

void printM_int(mymatrix<int> M) {
    for (int r = 0; r < M.numrows(); ++r)
    {
     for (int c = 0; c < M.numcols(r); ++c)
        cout << M(r, c) << " ";
        cout << endl;
    }
    cout << endl;
}

int main () {
	cout << "Testing mymatrix.h" << endl << endl;
	mymatrix<int>  M;  // 4x4 matrix, initialized to 0
	mymatrix<int>  MM(15,10);  // 20x30 matrix, initialized to 0
    
	// insert elements
	M(0, 0) = 123;
	M.at(1, 1) = 456;
	M(2, 2) = 789;
	M(3, 3) = -99;

    // testing mymatrix(int R, int C)
    // PARAMETERIZED CONSTRUCTOR
    cout << "testing mymatrix PARAMETERIZED CONSTRUCTOR" << endl;
    printM_int(M);
    printM_int(MM);
    // finish param constr test
  
    // testing mymatrix(const mymatrix<T>& other)
    // COPY CONTRUCTOR
    cout << "testing mymatrix PARAMETERIZED CONSTRUCTOR" << endl;
    mymatrix<int>  Mcopy1 = M;  // 4x4 matrix, initialized to 0
    printM_int(Mcopy1);
    mymatrix<int>  Mcopy2 = MM;  // 4x4 matrix, initialized to 0
    printM_int(Mcopy2);
    // finish copy constr test
    
    // testing int numrows() const
    // numrows
    cout << "testing mymatrix NUMROWS" << endl;
    cout << "numrows: " << M.numrows() << endl;    
    cout << endl;
    // finish numrows test
    
    // testing int numcols(int r) const
    // numcols
    cout << "testing mymatrix NUMCOLS" << endl;
    for (int r = 0; r < M.numrows(); r++) {
        cout << "colnum at row " << r+1 << ": " << M.numcols(r) << endl;        
    }
    cout << endl;
    // finish numcols test
    
    // testing void growcols(int r, int C)
    // growcols
    cout << "testing mymatrix GROWCOLS" << endl;
    M.growcols(1, 12);  // increase # of cols in row 1 to 12
    printM_int(M);
    M.growcols(0, 10);
    printM_int(M);
    M.growcols(2, 15);  
    printM_int(M);
    M.growcols(3, 2);
    printM_int(M);
    MM.growcols(5, 5);
    printM_int(MM);
    
    for (int r = 0; r < 4; ++r)
    for (int c = 0; c < 4; ++c)
      M(r, c) = (r * 4) + c + 1;
    // finish growcols test
    
    // testing void grow(int R, int C)
    // grow
    cout << "testing mymatrix GROW" << endl;
    cout << "GROWING" << endl;
    mymatrix<int>  Mgrow;  // 4x4 matrix, initialized to 0
    for (int r = 0; r < 4; ++r)
       for (int c = 0; c < 4; ++c)
          Mgrow(r, c) = (r * 4) + c + 1;
    Mgrow.grow(8,8);
    printM_int(Mgrow);
    Mgrow.grow(3,11);
    printM_int(Mgrow);
    Mgrow.grow(11,11);
    printM_int(Mgrow);
    Mgrow.grow(11,3);
    printM_int(Mgrow);
    
    MM.grow(11,3);
    printM_int(MM);
    MM.grow(1,30);
    printM_int(MM);
    // finish grow test
    
    // testing int size() const
    // size
    cout << "testing mymatrix SIZE" << endl;
    cout << "size of mymatrix: " << M.size() << endl;      
    cout << endl;
    // finish size test
    
    // testing T& at(int r, int c)
    // at
    cout << "testing mymatrix AT" << endl;
    for (int r = 0; r < M.numrows(); r++) {
        for (int c = 0; c < M.numcols(r); c++) {
            cout << "(" << r << "," << c << "): " 
                 << M.at(r,c) << endl;
        }
        
    }
    cout << endl;
    // finish at test
    
    // testing T& operator()(int r, int c)
    // M(r, c) = ...
    cout << "testing mymatrix T& OPERATOR" << endl;
    M(1,1) = 8888;
    cout << "M(1,1) = " << M(1,1) << endl; 
    M(3,2) = 2222;
    cout << "M(3,2) = " << M(3,2) << endl;  
    M(2,9) = 4444;
    cout << "M(2,9) = " << M(2,9) << endl;  
    cout << "-----printing it all . . . " << endl;  
    printM_int(M);
    // finish T& test
    
    // testing mymatrix<T> operator*(T scalar)
    // scalar multiplication
    cout << "testing mymatrix SCALAR MULT" << endl;
    mymatrix<int>  Mtemp;
    M = M * -1;
    cout << "-----printing M = M * -1 . . . " << endl;  
    printM_int(M);
    Mtemp = M * -2;
    cout << "-----printing Mtemp = M * -2 . . . " << endl;  
    printM_int(Mtemp);
    MM = Mtemp * 2;
    cout << "-----printing MM = Mtemp * 2 . . . " << endl;  
    printM_int(MM);
    Mtemp = MM * -4;
    cout << "-----printing Mtemp = MM * -4 . . . " << endl;  
    printM_int(Mtemp);
    // finish scalar mult test
    
    // testing mymatrix<T> operator*(const mymatrix<T>& other)
    // matrix multiplication
    cout << "testing mymatrix MATRIX MULT" << endl;
    mymatrix<int>  M1;
    mymatrix<int>  M2;
    mymatrix<int>  M3;
    
    for (int r = 0; r < M1.numrows(); r++) {
        for (int c = 0; c < M1.numcols(r); c++) {
            M1(r,c) = 1;
        }
    }
    for (int r = 0; r < M2.numrows(); r++) {
        for (int c = 0; c < M2.numcols(r); c++) {
            M2(r,c) = 1;
        }
    }
    M1(0, 0) = 1;
    M1(0, 1) = 2;
    M1(0, 2) = 3;
    M1(1, 0) = 4;
    M1(1, 1) = 5;
    M1(1, 2) = 6;    
    M2(0, 0) = 7;
    M2(0, 1) = 8;
    M2(1, 0) = 9;
    M2(1, 1) = 10;
    M2(2, 0) = 11;
    M2(2, 1) = 12;
    
    M3 = M1 * M2;
    cout << "result:" << endl;
    printM_int(M3);
    
    mymatrix<int>  M4(5,2);
    mymatrix<int>  M5(2,3);
    mymatrix<int>  M6;
    
    M4(0,0) = 1;
    M4(1,0) = 2;
    M4(2,0) = 3;
    M4(3,0) = 4;
    M4(4,0) = 4;
    M4(0,1) = 1;
    M4(1,1) = 2;
    M4(2,1) = 3;
    M4(3,1) = 4;
    M4(4,1) = 4;
    M5(0,0) = 7;
    M5(0,1) = 8;
    M5(0,2) = 9;
    M5(1,0) = 7;
    M5(1,1) = 8;
    M5(1,2) = 9;
    
    M6 = M4 * M5;
    cout << "result:" << endl;
    printM_int(M6);
    // finish matrix mult test
    
    return 0;
}