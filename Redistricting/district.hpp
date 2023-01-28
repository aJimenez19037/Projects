#include "voter.hpp"
#pragma once
class District
{
private:
  vector<Voter> voters;
  int size = 0;
  int lean = 0;
  double majority = 0;

  double positive = 0;
  double negative = 0;
  int undecided = 0;

public:
  District(Voter voter);//constructing district out of single voter
  District(vector<Voter>listOfVoters);//constructing out of a vector of voters
  District(string affiliations);//constructing district from string
  int getLean ();//return lean
  District sub (int first, int last);//create sub district out of the bigger distric. Inputs are the first and last voter.
  void extend_district(Voter voter);
  int getPositive();//return number of + voters
  int getNegative();//return number of - voters
  Voter getVoter(int i);//return the voter at that int val
  int getSize();
  double efficiencyGap();
  void print();//print out district information

};
