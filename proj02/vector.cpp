/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/14/22
Class: COE 311K 14405
*/

//contains only implementation for class functions found in the hpp file
#include "vector.hpp"


Vector::Vector(){};
void Vector::allocateData(int nelems)            // allocate space for nelem entries (of double type)
{
    if (nelems<=0)
    {
        cout << "[Error]: cannot create a vector of negative size or size 0" << endl;
        exit(1);
    }
    this -> data_ = vector<double>(nelems);
    this -> isInitialized_ = true;
};
void Vector::initFromFile(string fileName)        // read the vector from a file
{
    string myString;
    ifstream myfile(fileName);
    if (this -> isInitialized_)
    {
        cout << "[Error]: this vector has already been initialized" << endl;
        exit(1);
    }
    vector<double> data;
    if (myfile.is_open())
    {
        //get size of matrix
        myfile >> myString;
        int size = stod(myString);
        if (size <= 0)
        {
            cout << "[Error]: cannot create a vector of negative size or size 0" << endl;
            exit(1);
        }
        this -> size_ = size;
        for (int i = 0 ;i<size;i++)
        {
            myfile >> myString;
            data.push_back(stod(myString));
        }
        //if (data.size() != size)
        //{
        //    cout << "[Error]: the size and number of vector elements in the input file does not match" << endl;
        //    exit(1);
        //}
        this -> data_ = data;
        this -> isInitialized_ = true;
        myfile.close();
    }
}

int Vector::numElems()                                  // return number of elements
{      
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }                             
    return this -> data_.size();
};       
double Vector::l2norm()                           // return l2 norm
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    } 
    double total=0;
    vector<double> data = this -> data_;
    for (int i = 0;i<data.size();i++)
    {
        total = total + pow(data[i],2);
        
    }
    return sqrt(total);
};
double Vector::getVal(int i)                           // return the ith element   
{
    if((i> this -> data_.size()-1)||(i<0))
    {
        cout << "[Error]: element you are trying to access is out of the vectors scope" << endl;
        exit(1);
    }
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    return this -> data_[i];//if they say the first element it will use slot 0
};   

void Vector::setVal(int i, double val)            // set the ith element to val        
{
    if(i> this -> data_.size()-1)
    {
        cout << "[Error]: element you are trying to access is out of the vectors scope" << endl;
        exit(1);
    }
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    if (i<0)
    {
        cout << "[Error]: element you are trying to access is out of the vectors scope" << endl;
        exit(1);
    }
    this -> data_[i] = val;
};                   
void Vector::setAllVals(double val)               // set all elements of the vector to val
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    int size = this -> data_.size();
    this -> data_ = vector<double> (size, val);
};
void Vector::Print()                              // print the vector contents to stdout
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    vector<double> data;
    data = this -> data_;
    int size = data.size();
    cout << endl;
    for (int i =0; i < size; i++)
    {
        cout << "|" << setw(7) << data[i] << "|" << endl;
    }
    cout << endl;
}
void Vector::Print(string name)                   // print the vector contents to stdout with a name prefix
{
    if ((this -> isInitialized_) == false)
    {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    }
    cout << endl;
    cout << name << " = ";
    int stringLength = name.length() + 4;
    vector<double> data;
    data = this -> data_;
    int size = data.size();
    for (int i =0; i < size; i++)
    {
        if (i != 0)
        {
            cout << setw(stringLength);
        }
        cout << "|" << setw(7) << data[i] << "|" << endl;
    }
    cout << endl;
}


bool Vector::isInitialized()
{
    return this -> isInitialized_;
};

Vector Vector::subtractVector(Vector b)
{
    if (this -> numElems() != b.numElems())
    {
        cout << "[Error]: Cannot subtract vectors of different length" << endl;
        exit(1);
    }
    vector<double> data = this -> data_;
    Vector c;
    c.allocateData(data.size());
    for (int i = 0;i<data.size();i++)
    {
        c.setVal(i,(this -> getVal(i) - b.getVal(i)));
        
    }
    return c;
};
// regression support
double Vector::sum()         // return the sum of vector elements
{
    double total = 0;
    for (int i =0 ; i < this-> numElems() ; i++)
    {
        total += this -> data_[i];
    }
    return total;
};
double Vector::sumSquared()  // return the sum of (vector elements)^2
{
    double total = 0;
    for (int i =0 ; i < this-> numElems() ; i++)
    {
        total += pow(this -> data_[i],2);
    }
    return total;
};
double Vector::sum(Vector y) // return sum of (current vector)*(y vector) elements
{
    if (this -> numElems() != y.numElems())
    {
        cout << "[Error]: Cannot dot vectors of different length" << endl;
        exit(1);
    }
    double total = 0;
    for (int i = 0;i<this -> numElems();i++)
    {
        total += this -> getVal(i) * y.getVal(i);
    }
    return total;
};
void Vector::saveToFile(string fileName)
{
    fstream ostream;
   ostream.open(fileName, ios::out);
   int numElem = this -> numElems();
   ostream << numElem << endl;
   for (int i = 0; i < numElem ; i++)
    {
        ostream << this -> data_[i]<< endl;//setw 2 lines up first COL with (-) sign
    }
    
   ostream.close();
};
