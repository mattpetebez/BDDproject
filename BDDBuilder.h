#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include "cudd.h"

#ifndef BDDBUILDER_H
#define BDDBUILDER_H

using namespace std;

class BDDBuilder
{
public:
    BDDBuilder(vector<string>& binRules);
    void buildBDD();
    ~BDDBuilder();
    void printBDD();
    DdNode* returnHead();
private:
    int inRuleCount;
    vector<string> inRules;
    DdNode* mainBdd;
    DdNode* addedBDD;
    DdManager* manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    FILE * BDDDiag;
};


#endif // BDDBUILDER_H
