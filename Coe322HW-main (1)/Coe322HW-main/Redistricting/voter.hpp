#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <random>
#include <cmath>
using std::abs;
#include<algorithm>
using std::reverse;
#pragma once
class Voter
{
private:

  int ID = 0;
  int affiliation = 0;//2 party system. Can be +1, 0, -1. 0 Being undecided

public:
  Voter(int ID, int affiliation); //constructor
  void Print(); //print voter info
  int getAffiliation(); //return Affiliation
};

