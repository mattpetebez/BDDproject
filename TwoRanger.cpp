#include "TwoRanger.h"

TwoRanger::TwoRanger(vector<string>& _binRules)
{
    binRules = _binRules;
}

TwoRanger::~TwoRanger()
{
    
}

void TwoRanger::eradicateTwoRange(string twoFound)
{
    size_t finder;
    
    finder = twoFound.find('2');
    if(finder != string::npos)
    {
        twoFound.at(finder) = '0';
        string temp = twoFound;
        
        eradicateTwoRange(temp);
        
        twoFound.at(finder) = '1';
        eradicateTwoRange(twoFound);
    }
    else
    {
        newRules.push_back(twoFound);
    }
}

void TwoRanger::populateNewRule()
{
    size_t finder;
    auto it = binRules.begin();
    while(it != binRules.end())
    {
        finder = (*it).find('2');
        if(finder != string::npos)
        {
            eradicateTwoRange(*it);
        }
        else
        {
            newRules.push_back(*it);
        }
        ++it;
    }
}

vector<string> TwoRanger::returnNewRules()
{
    populateNewRule();
    return newRules;
}