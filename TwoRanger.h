#ifndef TWORANGER_H
#define TWORANGER_H

#include <iostream>
#include <vector>

using namespace std;

class TwoRanger
{
public:
    TwoRanger(vector<string>&);
    void eradicateTwoRange(string);
    vector<string> returnNewRules();
    ~TwoRanger();

private:
    void populateNewRule();
    vector<string> binRules;
    vector<string> newRules;
};

#endif // TWORANGER_H
