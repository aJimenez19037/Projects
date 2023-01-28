/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/14/22
Class: COE 311K 14405
*/
#include "beam.hpp"

Beam::Beam(int n, double L, double EI, double q)
{
    this -> n_ = n;
    this -> L_ = L;
    this -> EI_ = EI;
    this -> q_ = q;

    //setting discretized x coords

    Vector xVal;
    xVal.allocateData(n);
    double changeInX = (L) / ( n - 1 );
    double x1 = 0;
    xVal.setVal(0,x1);
    for (int i = 1;i<n;i++)
    {
        x1+=changeInX;
        xVal.setVal(i,x1);
    }
    this -> x_ = xVal;

    // set exact solution 
    Vector yExact;
    yExact.allocateData(n);
    for (int i = 0;i<n;i++)
    {
        if (i == 0||i == n-1)
        {
            yExact.setVal(i,0);
            continue;
        }
        double val = (((-q/(24*EI)) * (pow(xVal.getVal(i),4) - (2*L*pow(xVal.getVal(i),3)))) + (xVal.getVal(i)*-q*pow(L,3))/(24*EI));
        yExact.setVal(i,val);
    }
    //yExact.Print("Exact");
    this -> yExact_ = yExact;

    //set stiff matrix
    Matrix K;
    K.initialize(n,n);
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if ((i == 0)&&(j==0))//first row
            {
                K.setVal(i,j,1);
                continue;
            }
            if ((i == n-1)&&(j==n-1))//last row
            {
                K.setVal(i,j,1);
                break;
            }
            if ((i==j))
            {
                
                K.setVal(i,j,-2);
                K.setVal(i,j-1,1);
                K.setVal(i,j+1,1);
            }
        }
    }
    //K.Print("K");
    this -> K_ = K;
    this -> K_.setSolveMaxIters(100000);
    this -> K_.setSolveTolerance(1e-8);
    this -> K_.setSolveDebugMode(0);

    //set RHS/ forcing Vector

    Vector forcing;
    forcing.allocateData(n);
    for (int i =0;i<n-1;i++)// minus one because it will leave last value as 0 as it should be
    {
        double val = (((-q*pow(changeInX,2))/(2*EI)) * (pow(xVal.getVal(i),2) - (xVal.getVal(i) * L)));
        forcing.setVal(i,val);
    }
    //forcing.Print("f");
    this -> f_ = forcing;
    //set constant mesh interval
    this -> mesh_ = changeInX;

    

}; // constructor
double Beam::l2norm(Vector exact, Vector approx) // return l2 error norm between exact and approx. solutions
{
    Vector numerator;
    numerator = approx.subtractVector(exact);
    double norm = numerator.l2norm()/exact.l2norm();
    return norm;
};
Matrix Beam::getStiffnessMatrix()                // return system stiffness matrix
{
    return this -> K_;
};
Vector Beam::getSystemRHS()                      // return system forcing vector
{
    return this -> f_;
};
Vector Beam::getExactSoln()                      // return exact solution
{
    return this -> yExact_;
};
double Beam::getSolveTime()// return solver time (secs)
{
    if (solved_ == 1)
    {
        return this -> solveTime_;
    }
    else 
    {
        cout << "[ERROR] Solution has not been calculated. Can't return solve time. Call getApprox first." << endl;
        exit(1);
    }
   
}; 
int Beam::getSolveIters()// return number of solver iterations
{
    if (solved_ == 1)
    {
        return this -> solveIters_;
    }
    else 
    {
        cout << "[ERROR] Solution has not been calculated. Can't return solver iterations.  Call getApprox first." << endl;
        exit(1);
    }

};
Vector Beam::getCoordValues()                    // retun discretized x-coord values
{
    return this -> x_;
};

 // additional method suggestions to potentially make your life easier                
void Beam::setTurbo(bool mode)// set turbo mode setting
{
    this -> turbo_ = mode;
    this -> K_.setTurbo(mode);
};          
double Beam::getConstantMesh()// return constant mesh interval
{
    return this -> mesh_;
}; 
Vector Beam::getApproxSoln()                     // return finit-difference solution
{
    //set approx 
    Vector yApprox = this -> K_.Solve(this -> f_,3);
    this -> approx_ = yApprox;
    //giving beam info about solve time and iters
    this -> solveTime_= this -> K_.getSolveTime();
    this -> solveIters_ =  this -> K_.getSolveIters();
    this -> solved_ = 1;
    return this -> approx_;
};
       
