/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/14/22
Class: COE 311K 14405
*/

#include "beam.hpp"
int main(int argc, char *argv[])
{
    if ((argc != 6) && (argc !=5))
    {
        cout << "\n ---------------------------------------\nBeam Solver 9003\n   -> Solving a simply supported beam \n---------------------------------------\n\nUsage: beam [n] [L] [EI] [q] <turbo>\n\nwhere\n  [n]            number of points\n  [L]            length of the beam\n  [EI]           (Young's modulus)*(2nd moment of interia)\n  [q]            distributed load per unit length\n  <turbo>        optional argument (1=turbo mode)" << endl;
        exit(1);
    }
    int n = atoi(argv[1]);
    if (n <=0)
    {
        cout << "[ERROR] Cannot solve with 0 or negative points" << endl;
        exit(1);
    }
    double l = atof(argv[2]);
    if (l<=0)
    {
        cout << "[ERROR] Cannot solve with 0 or negative length" << endl;
        exit(1);
    }
    double EI = atof(argv[3]);
    if (EI<=0)
    {
        cout << "[ERROR] EI cannot be 0 or negative"<< endl;
        exit(1);
    }
    double q = atof(argv[4]);
    Beam a(n,l,EI,q);
    if (argc == 6)
    {
        int turbo = atoi (argv[5]);
        if ((turbo != 0)&&(turbo !=1))
        {
            cout << "[ERROR] Turbo mode must be either 0 or 1" << endl;
            exit(1);
        }
        a.setTurbo(turbo);
    }
    Vector approx = a.getApproxSoln();
    cout << "------------------------------" << endl;
    cout << "Iters: " << a.getSolveIters() << endl;
    cout << "Time to solve: " << a.getSolveTime() << endl;
    cout << "l2 norm: " << a.l2norm(a.getExactSoln(),approx) << endl;//made approx so we didnt have to recalculate approx solution when using getApproxSoln
    cout << "h: " << a.getConstantMesh() << endl;
    cout << "------------------------------" << endl;
    return 0;

}