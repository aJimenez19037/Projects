#include "district.hpp"


District::District(Voter voter)//constructing district out of single voter
  {
    voters.push_back(voter);
    size = 1;
    lean = voter.getAffiliation();
    if (lean = 1)
      positive++;
    else if (lean = -1)
      negative++;
    else 
      undecided++;
  }
District::District (vector<Voter>listOfVoters)//constructing out of a vector of voters
  {
    voters = listOfVoters;
    size = listOfVoters.size();
    for (int i = 0;i<size;i++)
      {
	int currentAffiliation = listOfVoters.at(i).getAffiliation();
	if (currentAffiliation == 1)    
	  { 
	    positive++;                                                             
	  }                                                                                     
	else if (currentAffiliation == -1)                                                   
	  {                                                                                   
	    negative++;                                                                     
	  }                                                                                   
	else if (currentAffiliation == 0)//undecided                                        
	  {                                                                                   
	    undecided++;                                                                    
	  }
      }
    if(positive > negative){
      lean = 1;
      majority = positive/size;}
    else if (negative > positive){
      lean = -1;
      majority = negative/size;}
    else if (positive == negative){
      lean = 0;
      majority = .5;}
  }
District::District(string affiliations)//constructing district from string
  {
    size = affiliations.size();
    char pos = '+';
    char neg = '-';
    char div = '/';
    for (int i = 0;i<size;i++)
      {
	if (affiliations.at(i) == pos)
	  {
	    Voter voter(i,1);
	    voters.push_back(voter);
	    positive++;
	  }
	else if (affiliations.at(i) == neg)
          {
            Voter voter(i,-1);
            voters.push_back(voter);
	    negative++;
          }
	else if (affiliations.at(i) == div)//undecided
          {
            Voter voter(i,0);
            voters.push_back(voter);
	    undecided++;
          }
	else {}//we dont allow weirdos to vote
      }
    if(positive > negative){
      lean = 1;
      majority = positive/size;}
    else if (negative > positive){
      lean = -1;
      majority = negative/size;}
    else if (positive == negative){
      lean = 0;
      majority = .5;}
  }
int District::getLean ()
  {
    return lean;
  }

District District::sub (int first, int last)//create sub district out of the bigger distric. Inputs are the first and last voter.
  {
    vector<Voter> newVoters = {voters.begin()+first, voters.begin()+last};
    District newDistrict(newVoters);
    return newDistrict;//we might want to have a vector with all the different subdistricts in the future
  }
void District::extend_district(Voter voter)
{
  voters.push_back(voter);
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
int District::getPositive()
{
  return positive;
}
int District::getNegative()
{
  return negative;
}
Voter District::getVoter(int i)
{
  return voters.at(i);
}
int District::getSize()
{return size;}
double District::efficiencyGap()
{
  double minorityWasted = 0;
  double majorityWasted = 0;
  double efficiencyGap = 0;
  for (int i = 0;i<size;i++)//print voters and affiliation
    {
      int leanDistrict = this -> getLean();
      if (leanDistrict == 1 )
        {
          //count minority wasted votes
          minorityWasted = this ->getNegative();
          majorityWasted = double (this -> getPositive()) - (((this -> getSize())/2)+1);
          efficiencyGap = ((majorityWasted - minorityWasted)/double (this -> getSize()));
	  return efficiencyGap;
        }
      else if (leanDistrict == -1)
        {
          minorityWasted = this -> getPositive();
          majorityWasted = double (this -> getNegative()) - (((this -> getSize())/2)+1);
          efficiencyGap = ((majorityWasted - minorityWasted)/double(this -> getSize()));
	  return efficiencyGap;
        }
      else 
	return 0;
    }
}
void District::print()
  {
    cout << "---------------     District   -----------------\n";
    cout << "Size: " << size << "\n";
    cout << "Majority: " << majority << "\n";
    cout << "Positive: " << positive << "\n";
    cout << "Negative: " << negative << "\n";
    cout << "Efficiency Gap: " << this -> efficiencyGap() << "\n";
    cout << "[ ";
    for(int i = 0;i< size;i++)
      {
	cout << voters.at(i).getAffiliation() << " , "; 
      }
    cout << "]";
    cout << "\n";
  }

