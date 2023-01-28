#include "district.hpp"
#pragma once

class Districting 
{
private:
  vector<District>districts;
  int size = 0;
  int lean = 0;

  int positive = 0;
  int negative = 0;
  int undecided = 0;
public:
  Districting();
  Districting (vector<District>listOfDistricts);//making district out of vector of districts
  void extend_with_new_district(Voter voter);//make new district with one voter and add it to districts in districitng
  void extend_with_new_district(District district);
  void extend_last_district(Voter voter);//add voter to last district
  void extend_last_district(District district);
  int getPositive();
  int getNegative();
  vector<District> getDistricts();
  int getPopulationLean();
  void reverseDistricts(vector<District>districts);
  void print();
};
