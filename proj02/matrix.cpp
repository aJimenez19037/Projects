/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/14/22
Class: COE 311K 14405
*/

//contains only implementation for class functions found in the hpp file
#include "matrix.hpp"

const double EulerConstant = std::exp(1.0);
using namespace std;


//----------------------------------------------
// matrix support class definition (matrix.hpp)
//----------------------------------------------

Matrix::Matrix() // constructor
{};                       


int Matrix::numRows()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    return this -> ROWS_;
}

int Matrix::numCols()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    return this -> COLS_;
}
vector<vector<double>> Matrix::getData()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    return this -> data_;
};

void Matrix::Print()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    vector<vector<double>> data;
    data = this -> data_;
    int ROWS = this -> ROWS_;
    int COLS = this -> COLS_;
    cout << endl;
    for (int i =0; i < ROWS; i++)
    {
        cout << "|" << setw(7);
        for (int j =0;j<COLS;j++)
        {
            if (j==(COLS-1))
            {
                cout << data[i][j];
            }
            else
            {
                cout << data[i][j] << setw(8);
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
};
void Matrix::Print(string name)
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    cout << endl;
    cout << name << " = ";
    int stringLength = name.length() + 4;
    vector<vector<double>> data;
    data = this -> data_;
    int ROWS = this -> ROWS_;
    int COLS = this -> COLS_;
    for (int i =0; i < ROWS; i++)
    {
        if (i != 0)
        {
            cout << setw(stringLength);
        }
        cout << "|" << setw(7);
        for (int j =0;j<COLS;j++)
        {
            if (j==(COLS-1))
            {
                cout << data[i][j];
            }
            else
            {
                cout << data[i][j] << setw(8);
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
};
void Matrix::initFromFile(string fileName)// read the matrix from a file
{   
    string myString;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        //get size of matrix
        myfile >> myString;
        int ROWS = stod(myString);
        if (ROWS <= 0)
        {
            cout << "[Error]: cannot create a matrix of negative size or size 0" << endl;
            exit(1);
        }
        this -> ROWS_ = ROWS;
        myfile >> myString;
        int COLS = stof(myString);
        if (COLS <= 0)
        {
            cout << "[Error]: cannot create a matrix of negative size or size 0" << endl;
            exit(1);
        }
        this -> COLS_ = COLS;
        //allocate space 
        vector<vector<double>> data;
        data.resize(ROWS);//makes rows
        for (int j = 0; j < ROWS; j++)//for every row it makes number of columns. (makes empty memory spaces 0)
        {
            data[j].resize(COLS);
        }
        for (int i = 0 ;i<ROWS;i++)
        {
            for (int j = 0;j<COLS;j++)
            {
                myfile >> myString;
                data[i][j] = stod(myString);
            }
        }
        if (COLS == ROWS)
        {
            this -> isSquare_ = true;
        }
        this -> data_ = data;
        this -> isInitialized_ = true;
    }
};        
bool Matrix::isSquare()//test if matrix is square
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    int ROWS = numRows();
    int COLS = numCols();

    if (ROWS == COLS)
    {
        this -> isSquare_ = true;
        return true;//returns 1
    }
        
    else 
    {
        this -> isSquare_ = false;
        return false;//returns 0
    }
};
void Matrix::initIdentity(int n)// initialize as an identity matrix of size nxn
{
    if (n <= 0)
    {
        cout << "[Error]: cannot create a matrix of negative size or size 0" << endl;
        exit(1);
    }
    int COLS = n;
    int ROWS = n;
    vector<vector<double>> data;
    this -> ROWS_ = ROWS;
    this -> COLS_ = COLS;
    this -> isSquare_ = true;
    this -> isInitialized_ = true;

    data.resize(n);//makes rows
    for (int j = 0; j < n; j++)//for every row it makes number of columns. (makes empty slots = 0)
    {
        data[j].resize(COLS);
    }
    for (int i = 0 ;i<ROWS;i++)
    {
        for (int j = 0;j<COLS;j++)
        {
            if (i == j)
                data[i][j] = 1;
        }
    }
    this -> data_ = data;
};
void Matrix::initialize(int row, int col)
{
    if ((row <= 0)||(col <= 0))
    {
        cout << "[Error]: cannot create a matrix of negative size or size 0" << endl;
        exit(1);
    }

    vector<vector<double>> data;
    this -> ROWS_ = row;
    this -> COLS_ = col;
    if (row == col)
        this -> isSquare_ = true;
    this -> isInitialized_ = true;
    data.resize(row);//makes rows
    for (int j = 0; j < row; j++)//for every row it makes number of columns. (makes empty memory spaces 0)
    {
        data[j].resize(col);
    }
    this -> data_ = data;
};
double Matrix::getVal(int row, int col)
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    if((row> this -> ROWS_-1)||(col > this ->COLS_-1)||(col<0)||(row<0))
    {
        cout << "[Error]: element you are trying to access is out of the vectors scope" << endl;
        exit(1);
    }
    return this -> data_[row][col];
};     
void Matrix::setVal(int row, int col, double val)
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    if((row> this -> ROWS_-1)||(col > this ->COLS_-1)||(col<0)||(row<0))
    {
        cout << "[Error]: element you are trying to access is out of the vectors scope" << endl;
        exit(1);
    }
    this -> data_[row][col] = val;
}; 
Matrix Matrix::Transpose()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    int r2;
    int c2;
    Matrix transposed;
    transposed.isInitialized_ = true;
    vector<vector<double>> data1 = this -> data_;
    vector<vector<double>> data2;
    c2 = this -> ROWS_;
    r2 = this -> COLS_;
    

    //if matrix is mxn it makes transposed matrix's dimension nxm
    
    //allocate space for m2
    data2.resize(r2);//makes rows
    for (int j = 0; j < r2; j++)//for every row it makes number of columns. (makes empty memory spaces 0)
    {
        data2[j].resize(c2);
    }
    for (int i = 0 ;i<r2;i++)
    {
        for (int j = 0;j<c2;j++)
        {
            data2[i][j] = data1[j][i];
        }
    }    
    
    transposed.data_ = data2;
    transposed.ROWS_ = r2;
    transposed.COLS_ = c2;
    transposed.isSquare();//sets property to true or false
    return transposed;
};   
Matrix Matrix::Multiply(double A)
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    Matrix m2;
    m2.isInitialized_ = true;
    vector<vector<double>> data = this -> data_;
    int ROWS = this -> ROWS_;
    int COLS = this -> COLS_;
    for (int i = 0 ;i<ROWS;i++)
    {
        for (int j = 0;j<COLS;j++)
        {
            data[i][j] = (A*data[i][j]);
        }
    }    
    m2.data_ = data;
    m2.ROWS_ = ROWS;
    m2.COLS_ = COLS;
    m2.isSquare();//sets property to true or false
    return m2;
};
Matrix Matrix::Multiply(Matrix B)//A*B
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    if ((B.isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize input matrix first" << endl;
        exit(1);
    }

    int rowsA, colsA, rowsB, colsB;
    Matrix product;
    vector<vector<double>> dataA = this -> data_;
    vector<vector<double>> dataB = B.getData();
    colsA = this -> COLS_;
    rowsA = this -> ROWS_;
    colsB = B.numCols();
    rowsB = B.numRows();
    product.isInitialized_ = true;
    product.ROWS_ = rowsA;
    product.COLS_ = colsB;
    //A(rowsxcol)B(rowsxcol)
    if (colsA != rowsB)
    {
        cout << "[Error] Not able to multiply based on dimensions of both matrices." << endl;
        exit(1);
    }
    vector<vector<double>> data;
    data.resize(rowsA);//makes rows
    for (int j = 0; j < rowsA; j++)//for every row it makes number of columns. (makes empty slots = 0)
    {
        data[j].resize(colsB);
    }
    double total;
    for (int i = 0 ;i<rowsA;i++)
    {
        for (int j = 0;j<colsB;j++)
        {
            for (int k = 0;k<rowsB;k++)
            {
                total +=  (dataA[i][k])*(dataB[k][j]);                
            }
            data[i][j] = total;
            total = 0;
        }
    }
    
    product.data_ = data;
    product.isSquare();//sets property to true or false
    return product;
};
vector<double> Matrix::Diagonal()
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    vector<vector<double>> data;
    data = this -> data_;
    int ROWS = this -> ROWS_;
    int COLS = this -> COLS_;
    vector<double> dVector;
    for (int i = 0 ;i<ROWS;i++)
    {
        for (int j = 0;j<COLS;j++)
        {
            if (i == j)
                dVector.push_back(data[i][j]);
        }
    }
    cout <<"Diagonal Vector is: " << endl;

    for (int i =0;i<dVector.size();i++)
    {
        cout << dVector[i] << " " ;
    }
    cout << endl;
    return dVector;
}; 
void Matrix::mulitplyRow(int row, double value)
{
    //this -> Print("being multiplied");
    for (int i = 0;i<this->COLS_;i++)
    {
        
        double num = this -> getVal(row,i);
        //cout << "Val(" << row << "," << i <<"):"<< num<<endl;
        this -> setVal(row,i, value * num);
        //cout << "multiplying:" << value << " * " << num << " = "<< value * num<<  endl;
        if (num==-0)
        {
            this -> setVal(row,i,0);
        }
    }
};
void Matrix::subtractRow(int row1,int row2)           //subtract row2 from row1
{
    for (int i = 0;i<this->COLS_;i++)
    {
        double num = this -> getVal(row1,i) - this -> getVal(row2,i);
        this -> setVal(row1,i,num);
    }
};
void Matrix::setSolveMaxIters(int iters)
{
    this -> maxIterations_ = iters;
};
void Matrix::setSolveTolerance(double tolerance)
{
    this -> solveTolerance_ = tolerance;
};
int Matrix::getSolveIters()
{
    return this -> solveIters_;
}
void Matrix::setSolveDebugMode(int mode)
{
    this -> debugFlag_ = mode;
};
void Matrix::setTurbo(bool mode)
{
    this -> turbo_ = mode;
};
Vector Matrix::Solve(Vector b, int mode)          // return solution of [A]x=b using desired solver mode
{
    if (! this->isSquare_)
    {
        cout << "[Error]: matrix is not square" << endl;
        exit(1);
    }
    if (b.numElems()!=this-> ROWS_)
    {
        cout << "[Error]: vector elements do not match matrix rows" << endl;
        exit(1);
    }
    Timer atimer;
    Vector x;
    x.allocateData(this -> ROWS_);
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    }
    if (b.isInitialized()==false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    if (mode == GAUSS_ELIM)
    {
        atimer.Start();
        if (this -> debugFlag_ == 1)
        {
            cout << "Solving [A]x = b using naive Gaussian elimination" << endl;
            cout << "\n Initial system: \n" << endl;
            this -> Print("[A]");
            cout << endl;
            b.Print("b");
            cout << endl;
        }
        double scalar;
        for (int i = 0;i<this->COLS_-1;i++)//column
        {
            //this -> Print("OG");
            for (int j =i+1;j<this->ROWS_;j++)//row
            {
                double num = this->getVal(j,i);
                double den = this->getVal(i,i);
                //cout << "den: " << den << endl;
                if (num==0)
                {
                    continue;
                }
                
                scalar = (num/den);
                //cout << num << "/" << den << endl;
                //cout << "Scalar: " << scalar << endl;
                this -> mulitplyRow(i,scalar);//multiply matrix row by scalar
                b.setVal(i,(b.getVal(i) * scalar));//multiply b by scalar
                //this -> Print(" post multiply");
                this -> subtractRow(j,i);
                //this -> Print(" post subtract");
                b.setVal(j,(b.getVal(j) - b.getVal(i)));
                //need to change row 1 back 
                //cout << "Scalar: " << 1/scalar << endl;
                this -> mulitplyRow(i,(1/scalar));
                b.setVal(i,(b.getVal(i)/scalar));
                //this -> Print(" post return row1 back:");
            }  
        } 
        if (this -> debugFlag_ == 1)
        {
            cout << "Updated system after forward elimination: \n" << endl;
            this -> Print("[A]");
            cout << endl;
            b.Print("b");
            cout << endl;
        }
        
        int length = b.numElems()-1;

        double val = b.getVal(length)/this -> getVal(length,length); //just for the last row to start of backwards sub
        //cout <<  b.getVal(length) << "/"  << this -> getVal(length,length) << endl;
        x.setVal(length,val);
        //x.Print();
        double totalSub;
        for (int i = length-1;i >= 0;i--)
        {
           scalar = (1/this -> getVal(i,i));
           totalSub=0;
           
           for (int j = length;j>=0; j--)
           {
                totalSub +=  this -> getVal(i,j) * x.getVal(j);
                
                //cout << this -> getVal(i,j) * x.getVal(j) << " = " << this -> getVal(i,j) << "*" << x.getVal(j) <<endl;
                //cout << totalSub << endl;
           }
           //cout << totalSub << endl;
           val = b.getVal(i) - totalSub;
           //cout << b.getVal(i) << " - " << totalSub <<endl;
           //cout << val << endl;
           b.setVal(i,val); 
           //cout << scalar << endl;
           val =  scalar *  b.getVal(i);
           x.setVal(i,val);
           //x.Print("x:");
        }
        atimer.Stop();
        this -> solveTime_ =  atimer.ElapsedTime();
        //cout << "Time to solve using [Gaussian elimination] = " << atimer.ElapsedTime() << "(secs)"<<endl;
        x.Print("soln");
        return x;
    }

    else if (mode == JACOBI)
    {
        atimer.Start();
        if (this -> debugFlag_ == 1)
        {
            cout << "Solving [A]x = b using Jacobi" << endl;
        }
        Vector xOld;
        xOld.allocateData(this->ROWS_);
        x.setAllVals(0);
        double val=0;
        double scalar;
        int iters;
        //this -> Print("Matrix");
        //b.Print("b");

        for (iters = 0;iters<this->maxIterations_;iters++)
        {
            for (int i = 0;i<this->ROWS_;i++)
            {
                
                //cout << "Row: " << i << endl;
                double total=0;
                for (int j = 0;j<this->ROWS_;j++)
                {
                    if (i==j)
                        continue;
                    total = total + (this->getVal(i,j) * xOld.getVal(j));
                    //cout << (this->getVal(i,j) * xOld.getVal(j)) << " = " << this -> getVal(i,j) << " * "<< xOld.getVal(j) << endl;
                }
                //cout << "Total: " << total << endl;
                scalar = (1/this->getVal(i,i));
                val = b.getVal(i) - total;
                //cout << "b - total: "<< val << endl;
                //cout << "val*scalar: " << (val*scalar) << endl;
                x.setVal(i,(val*scalar));
                //this -> Print();
                //x.Print("X temp");
            }
            Vector numerator;
            numerator = x.subtractVector(xOld);
            double norm = numerator.l2norm()/x.l2norm();
            
            //xOld.Print("Old");
            //x.Print("X"); 
            xOld=x;
            if (this -> debugFlag_ == 1)
            {
                cout << "--> Iteration:       " << iters+1 << " norm = " << norm << endl; 
            }
            if (norm < this -> solveTolerance_)
            {
                atimer.Stop();
                cout << "Converged!" << endl;
                cout << "Time to solve using [Jacobi] = " << atimer.ElapsedTime()<<" (secs), (" << iters << " iters)" << endl;
                x.Print("soln");
                return x;
            }
        }
        atimer.Stop();
        this -> solveTime_ =  atimer.ElapsedTime();
        this -> solveIters_ = iters;
        //cout << "Time to solve using [Jacobi] = " << atimer.ElapsedTime()<<" (secs), (" << iters << " iters)" << endl;
        //x.Print("soln");
        return x;

    }
    else if (mode == GAUSS_SEIDEL)
    {
        atimer.Start();
        if (this -> debugFlag_ == 1)
        {
            cout << "Solving [A]x = b using naive Gaussian Seidel" << endl;
        }
        Vector xOld;
        xOld.allocateData(this->ROWS_);
        double val=0;
        double scalar;
        int iters;

        for (iters = 0;iters<this->maxIterations_;iters++)
        {
            for (int i = 1;i<this->ROWS_-1;i++)
            {
                
                double total=0;
                double total2=0;
                
                if (this -> turbo_ == 1)
                {
                    total += (this->getVal(i,i-1) * x.getVal(i-1));
                    if (i+1<this -> ROWS_)
                    {
                        total2 += (this->getVal(i,i+1) * xOld.getVal(i+1));
                    }
                    
                }
                else if (this -> turbo_ == 0)
                {
                    for (int j = 0;j<i;j++)//sum 1
                    {
                        total += (this->getVal(i,j) * x.getVal(j));
                    }
                    for (int j = (i+1);j<this ->ROWS_;j++)//sum2
                    {
                        total2 += (this->getVal(i,j) * xOld.getVal(j));
                    }
                }
                x.setVal(i,((b.getVal(i) - total - total2)*(1/this->getVal(i,i))));
                
            }
            Vector numerator;
            numerator = x.subtractVector(xOld);
            double norm = numerator.l2norm()/x.l2norm();
            if (this -> debugFlag_ == 1)
            {
                cout << "--> Iteration:       " << iters+1 << " norm = " << norm << endl; 
            }
            if (norm < this -> solveTolerance_)
            {
                atimer.Stop();
                this -> solveTime_ =  atimer.ElapsedTime();
                this -> solveIters_ = iters;
                //cout << "Converged!" << endl;
                //cout << "Time to solve using [naive Gaussian Seide] = " << atimer.ElapsedTime()<<" (secs), (" << iters << " iters)\n" << endl;
                //x.Print("soln");
                return x;
                
            }
            
            xOld=x;
        }
        atimer.Stop();
        this -> solveTime_ =  atimer.ElapsedTime();
        this -> solveIters_ = iters;
        cout << iters << endl;
        //cout << "Time to solve using [naive Gaussian Seide] = " << atimer.ElapsedTime()<<" (secs), (" << iters << " iters)" << endl;
        //x.Print("soln");
        return x;
    }
    else 
    {
        cout << "[Error]: slow your roll. Mode must be between 1-3. [1] - Gauss elim, [2] - Jacobi, [3] - Gauss Seidel" << endl;
        exit(1);
    }
    
    return x;
};
double Matrix::getSolveTime()                     // wall clock time (in secs) required for last solve
{
    return this -> solveTime_;
};

Vector Matrix::extract(int col)                     // extract vector from matrix corresponding to the col index
{
    if ((col>this->COLS_-1)||(col<0))
    {
        cout << "[Error]: column indicated does not exist." << endl;
        exit(1);
    }
    Vector v;
    v.allocateData(this->ROWS_);
    for (int i=0;i<this->ROWS_;i++)
    {
        
        v.setVal(i,this->data_[i][col]);
    }
    return v;
};
void Matrix::saveToFile(string fileName)            // save matrix to file (same file format as initFromFile)
{
   fstream ostream;
   ostream.open(fileName, ios::out);
   ostream << this -> ROWS_ << " " << this -> COLS_ << endl;
   for (int i = 0; i < this->ROWS_ ; i++)
   {
       for (int j = 0; j < this->COLS_;j++)
       {
           if (j==0)
           {
               ostream <<this -> data_[i][j] << " ";//setw 2 lines up first COL with (-) sign
               continue;
           }
           ostream << this -> data_[i][j] << " ";
       }
       ostream << endl;
   } 
   ostream.close();
};
 // regression support (for Nx2 matrices)
Vector Matrix::linFit(int mode)                     // linear regression fit (mode=LINEAR, EXPONENTIAL, or POWER)
{
    Vector xValues = this -> extract(0);
    Vector yValues = this -> extract(1);
    if (this -> COLS_ != 2)
    {
        cout << "[ERROR] can not find the linear fit for a matrix that does not have two columns" << endl;
        exit(1);
    }
    if (mode == 1)//linear
    {
        //calculating a1
        
        double n = this -> ROWS_;
        double a1 = (((n*xValues.sum(yValues))-(xValues.sum()*yValues.sum()))/((n*xValues.sumSquared()) - pow(xValues.sum(),2)));// = 80
        //calculating a0 
        double a0 = ( (1/n) * (yValues.sum()-(a1*xValues.sum())));
        Vector v;
        v.allocateData(2);
        v.setVal(0, a0);
        v.setVal(1,a1);
        return v;//returns a0 and a1
    }
    else if (mode == 2)//exponential
    {
        for (int i = 0; i< this -> ROWS_; i++)// get logy and logx vectors
        {
            yValues.setVal(i,log(yValues.getVal(i)));
        }
        double n = this -> ROWS_;
        double a1 = (((n*xValues.sum(yValues))-(xValues.sum()*yValues.sum()))/((n*xValues.sumSquared()) - pow(xValues.sum(),2)));// = 80
        //calculating a0 
        double a0 = ( (1/n) * (yValues.sum()-(a1*xValues.sum())));
        double alpha = pow(EulerConstant, a0);
        Vector v;
        v.allocateData(2);
        v.setVal(0, alpha);
        v.setVal(1,a1);
        return v;//returns alpha and beta
    }
    else if (mode ==3)//power
    {
        for (int i = 0; i< this -> ROWS_; i++)// get logy and logx vectors
        {
            xValues.setVal(i,log(xValues.getVal(i)));
            yValues.setVal(i,log(yValues.getVal(i)));
        }
        double n = this -> ROWS_;
        double a1 = (((n*xValues.sum(yValues))-(xValues.sum()*yValues.sum()))/((n*xValues.sumSquared()) - pow(xValues.sum(),2)));// = 80
        //calculating a0 
        double a0 = ( (1/n) * (yValues.sum()-(a1*xValues.sum())));
        double alpha = pow(EulerConstant, a0);
        Vector v;
        v.allocateData(2);
        v.setVal(0, alpha);
        v.setVal(1,a1);
        return v;//returns alpha and beta
    }
    else
    {
        cout << "--------------------------------------\nData Fitting Wizard 9002\n   -> A linear regression fitting tool!\n---------------------------------------\n\nUsage: regression [mode] [matrix.input] [output]\n\nwhere:\n [mode]            fit method (1=linear 2=exponential, 3=power)\n [matrix.input]    name of text input file housing Nx2 matrix [A]\n [output]          name of text output file with fitting results (Nx2 matrix)\n" << endl;
        exit(1);
    }
};
Matrix Matrix::evalLinFit(int mode, Vector fit)     // evaluate linear fit - ouput is an Nx2 matrix
{ 
    double a0 = fit.getVal(0);
    double a1 = fit.getVal(1);
    Vector xValues = this -> extract(0);
    Vector yValues;
    yValues.allocateData(this -> ROWS_);
    Matrix m;

    m.initialize(this -> ROWS_, this -> COLS_);

    if(mode == 1)//linear
    {
        for (int i = 0; i < this -> ROWS_ ;i++)//sets new matrix y values
        {
            m.setVal(i,1, a0 + a1 * xValues.getVal(i));//sets new y values
            m.setVal(i,0,xValues.getVal(i));//copies over x values
        }
        return m;
    }
    else if (mode == 2)//exponential
    {
        for (int i = 0; i < this -> ROWS_ ;i++)//sets new matrix y values
        {
            m.setVal(i,1, pow(EulerConstant,(log(a0) + a1 * xValues.getVal(i))));//sets new y values
            m.setVal(i,0,xValues.getVal(i));//copies over x values
        }
        return m;
    }
    else if (mode ==3)//power
    {
        for (int i = 0; i < this -> ROWS_ ;i++)//sets new matrix y values
        {
            m.setVal(i,1, (a0 * pow(xValues.getVal(i),a1)));//sets new y values
            m.setVal(i,0,xValues.getVal(i));//copies over x values
        }
        return m;
    }
    else 
    {
        cout << "[Error]: mode must be [1] Linear [2] Exponential [3] Power " << endl;
        exit(1);
    }
    
};

