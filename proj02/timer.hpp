/*
Name: Antonio Jimenez
EID:aoj268
Date: 5/12/22
Class: COE 311K 14405
*/
//----------------------------------------------------------------
// A basic timer class to measure wall-clock execution time
// of specific code blocks.
//
// Graciously gifted to the students of COE 311K for use on their
// journey to coding zen.
// 
// This example is a header-only implementation. To use, simply:
//
// #include "timer.hpp"
//----------------------------------------------------------------
#include <chrono>
#include <cassert>

class Timer
{
private:
    std::chrono::time_point<std::chrono::system_clock> tstart_;
    std::chrono::time_point<std::chrono::system_clock> tend_;

public:
    void Start() { tstart_ = std::chrono::system_clock::now();};
    void Stop()  {   tend_ = std::chrono::system_clock::now();};
    double ElapsedTime()
    {
        return(std::chrono::duration_cast<std::chrono::microseconds>(tend_ - tstart_).count()/1000000.0);
    }
};


