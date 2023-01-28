#include "voter.hpp"
#include "districting.hpp"
#pragma once


class Population 
{
private:
  vector<Voter> voters;
  int size = 0;
  int lean = 0;
  double majority = 0;

  double positive = 0;
  double negative = 0;
  double undecided = 0;


public:

  Districting gerryFinal;
  Population (string affiliations);//constructing population from string
  Population (int population_size, int lean, double majority);//construct random popu based on inputs
  Population (vector<Voter>listOfVoters);//constructing out of a vector of voters
  //  Population sub (int first, int last);//create sub district out of the bigger distric. Inputs are the first and last voter.
  vector<Voter> sub (int first, int last);
  Voter getVoter(int i);
  void updateGerryFinal(Districting gerryFinal);
  void minority_rules( int ndistricts );
  void print();//print out population info

};
