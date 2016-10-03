#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include "cudd.h"
#include "GroupedRule.h"

#ifndef BDDBUILDER_H
#define BDDBUILDER_H

using namespace std;

class BDDBuilder
{
public:
    BDDBuilder(vector<GroupedRule> binRules);
    void addRule(string& rule, string& action);
    void buildBDD();
    ~BDDBuilder();
    void printBDD(string& filename);
    DdNode* returnHead();
private:
    int inRuleCount;
    vector<GroupedRule> inRules;
    DdNode* mainBdd;
    DdNode* addedBDD;
    DdManager* manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    FILE * BDDDiag;
};


#endif // BDDBUILDER_H
