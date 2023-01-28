/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/14/22
Class: COE 311K 14405
*/

//class defintions
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "vector.hpp"
#include "timer.hpp"
#pragma once

using namespace std;

//----------------------------------------------
// matrix support class definition (matrix.hpp)
//----------------------------------------------

// supported solver modes
enum solveModes {GAUSS_ELIM = 1,JACOBI = 2,GAUSS_SEIDEL = 3};
enum fitModes {LINEAR=1,EXPONENTIAL=2,POWER=3}; // supported linear regression fitting modes

class Matrix
{
   public:
      Matrix();                                 // constructor
      void Print();                             // print the matrix to stdout
      void Print(string name);                  // print the matrix to stdout with a name prefix
      void initIdentity(int n);                 // initialize as an identity matrix of size nxn
      int numRows();                            // return number of rows
      int numCols();                            // return number of columns
      vector<vector<double>> getData();         //return data
      void initFromFile(string fileName);       //read in from file
      void initialize(int row, int col);   
      bool isSquare();                          //test if matrix is square
      double getVal(int row, int col);          //return value in that row and column
      void setVal(int row, int col, double val);//set value for specific element in matrix
      Matrix Transpose();                       // return transpose of matrix
      Matrix Multiply(double A);                // multiply by a scalar and return resulting matrix
      Matrix Multiply(Matrix B);                // post-multiply by B and return resulting matrix aka A*B
      vector<double> Diagonal();                // return a vector containing diagonal elements of the matrix
      void mulitplyRow(int row, double value);    //multiply row of matrix by a value
      void subtractRow(int row1,int row2);           //subtract row 2 from row 1

      // Linear solver support
      Vector Solve(Vector b, int mode);          // return solution of [A]x=b using desired solver mode
      double getSolveTime();                     // wall clock time (in secs) required for last solve
      void setSolveDebugMode(int flag);         // set flag to toggle debug output mode for linear solves

      // Support methods for iterative methods
      void setSolveMaxIters(int iters);          // set cap on max # of iterations
      void setSolveTolerance(double tol);        // set desired stopping tolerance
      int  getSolveIters();                      // return number of iters completed from last solve

       // regression support (for Nx2 matrices)
      Vector linFit(int mode);                     // linear regression fit (mode=LINEAR, EXPONENTIAL, or POWER)
      Matrix evalLinFit(int mode, Vector fit);     // evaluate linear fit - ouput is an Nx2 matrix
      // additional utilities to aid in regression
      Vector extract(int col);                     // extract vector from matrix corresponding to the col index
      void saveToFile(string fileName);            // save matrix to file (same file format as initFromFile)
      void setTurbo(bool mode);
      
   private:
      vector<vector<double>> data_;
      double ROWS_;
      double COLS_;
      bool isSquare_;
      bool isInitialized_ = false;
      int maxIterations_;
      double solveTolerance_;
      int debugFlag_ = 0;
      double solveTime_;
      double solveIters_;
      bool turbo_ = 0;

      
      
};