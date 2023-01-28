#include "districting.hpp"

Districting::Districting(){}
Districting::Districting (vector<District>listOfDistricts)//making district out of vector of districts
{
  districts = listOfDistricts;
  size = listOfDistricts.size();
  for (int i = 0;i<size;i++)
    {
      int currentLean = listOfDistricts.at(i).getLean();
      if (currentLean == 1)
	{positive++;}
      else if (currentLean == -1)
	{negative++;}
      else if (currentLean == 0)//undecided
	{undecided++;}
    }
  if(positive > negative)
    {
      lean = 1;
      //majority = positive/size;
    }
  else if (negative > positive)
    {
      lean = -1;
      // majority = negative/size;
    }
  else if (positive == negative)
    {
      lean = 0;
    }
}
void Districting::extend_with_new_district(Voter voter) //adding new district with one voter
{
  District newDistrict(voter);
  districts.push_back(newDistrict);
  size++;
  if (voter.getAffiliation() == 1)
    positive++;
  else if (voter.getAffiliation() == -1)
    negative++;
  if(positive > negative)
      lean = 1;
  else if (negative > positive)
      lean = -1;
  else if (positive == negative)
      lean = 0;
}
void Districting::extend_with_new_district(District district)
{
  districts.push_back(district);
  size++;
  if (district.getLean() == 1)
    positive++;
  else if (district.getLean() == -1)
    negative++;
  if(positive > negative)
    lean = 1;
  else if (negative > positive)
    lean = -1;
  else if (positive == negative)
    lean = 0;
}
void Districting::extend_last_district(Voter voter)//adding voter to the last district
{
  if(districts.empty())
    cout << "[Error] Cannot extend last district because there is no district \n";
  else 
    districts.back().extend_district(voter);
  positive = 0;
  negative = 0;
  //recalculate the lean
  for (int i = 0;i<size;i++)
    {
      int currentLean = districts.at(i).getLean();
      if (currentLean == 1)
        {positive++;}
      else if (currentLean == -1)
        {negative++;}
      else if (currentLean == 0)//undecided
        {undecided++;}
    }
  if(positive > negative)
    {
      lean = 1;
      //majority = positive/size;
    }
  else if (negative > positive)
    {
      lean = -1;
      // majority = negative/size;
    }
  else if (positive == negative)
    {
      lean = 0;
    }
  cout << "Printing district with new changes \n";
  districts.back().print(); 
}
int Districting::getPositive()
{
  return positive;
}
int Districting::getNegative()
{
  return negative;
}
int Districting::getPopulationLean()
{
  int voterPositive = 0;
  int voterNegative = 0;
  for(int i = 0; i < districts.size(); i++)//for each district
    {
      for (int j = 0;j<districts.at(i).getSize();j++)//for each voter
	{
	  if (districts.at(i).getVoter(j).getAffiliation() == 1)
	    {
	      voterPositive++;
	    }
	  else if (districts.at(i).getVoter(j).getAffiliation() == -1)
	    {
	      voterNegative++;
	    }
	} 
    }
  if (voterPositive>voterNegative)
    return 1;
  else if (voterNegative>voterPositive)
    return -1;
  else 
    return 0;
}
vector<District> Districting::getDistricts(){return districts;}


void Districting::reverseDistricts(vector<District>newDistricts)
{
  reverse(newDistricts.begin(),newDistricts.end());
  districts = newDistricts;
}  

void Districting::print()
{
  cout << "------------   Districting    --------------- \n";
  cout << "[" << size;
  for (int i = 0; i<size;i++)//for each district
    {
      cout << "[";
      for (int j = 0;j<districts.at(i).getSize();j++)//print voters and affiliation
        {
          cout << j << ":" << districts.at(i).getVoter(j).getAffiliation() << ",";
        }
      cout << "],";
    }
  cout << "] \n";
  cout << "minority rule: ";
  if (getPopulationLean() == 1)
    cout << negative - positive  << "\n";
  else if (getPopulationLean() == -1)
    cout << positive - negative << "\n";
  else
    {cout << "Population has no lean";}
  cout << "\n";
}
