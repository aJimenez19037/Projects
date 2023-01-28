#include "voter.hpp"


Voter::Voter(int ID, int affiliation)
  {
    this -> ID = ID;
    this -> affiliation = affiliation;
  }
void Voter::Print()
  {
    if (affiliation == 1)
      cout << "Voter " << ID << " Positive \n" ;
    else if (affiliation == -1)
      cout << "Voter " << ID << " Negative\n" ;
    else if (affiliation == 0)
      cout << "Voter " << ID << " Undecided\n";
    else
      cout << "Voter is weirdo \n";
  }
int Voter::getAffiliation()
  {
    return affiliation;
  }
