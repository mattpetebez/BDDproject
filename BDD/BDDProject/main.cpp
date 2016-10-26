#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "cudd.h"

using namespace std;

struct BDDit{ //Matt did not think of making this struct. Was all me (Tyron)
  DdNode * current;
  void setCurr(DdNode * curr);
  string ThisRule = "";
  bool isEnd = false;
  bool IsEnd();
};

void BDDit::setCurr(DdNode * curr)
{
    current = curr;
}

bool BDDit::IsEnd()
{
    return isEnd;
}


int main(int argv, char ** argc) 
{
/*    string rule;
    vector<string> rules;
    rules = argc[1];
    
    for (int i = 1; i < argv; i++)
    {
        rule = argv.at(i);
        rules.push_back(rule);
    }*/
    string rule = "10101010";
    //cout << rule.at(20) << endl;
    DdManager* manager;
    
    vector<DdNode>* BDDs;
    FILE* BDDDiag;
    
    manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    
    DdNode* temp, *var, *f, *g;
    int bit = 7;
    int i;
    
    f = Cudd_ReadOne(manager);
    Cudd_Ref(f);
    for (i = bit; i >= 0; i--)
    {
        var = Cudd_bddIthVar(manager, i);
        if (rule.at(i) == '1')
        {
            temp = Cudd_bddAnd(manager, var, f);
        }
        else
        {
            temp = Cudd_bddAnd(manager, Cudd_Not(var), f);
        }
        Cudd_Ref(temp);
        Cudd_RecursiveDeref(manager, f);
        f = temp;
    }
    rule = "10010101"; //Tyron coded this part :P
    g = Cudd_ReadOne(manager);
    Cudd_Ref(g);
    for (i = bit; i >= 0; i--)
    {
        var = Cudd_bddIthVar(manager, i);
        if (rule.at(i) == '1')
        {
            temp = Cudd_bddAnd(manager, var, g);
        }
        else
        {
            temp = Cudd_bddAnd(manager, Cudd_Not(var), g);
        }
        Cudd_Ref(temp);
        Cudd_RecursiveDeref(manager, g);
        g = temp;
    }
    
    DdNode * combined = Cudd_bddOr(manager,f,g);//All Tyron
    DdNode * Curr = Cudd_T(combined);
    DdNode * Curr2 = Cudd_E(Curr);
    DdNode * Curr3 = Cudd_E(Curr2);
//    cout << Cudd_CountPathsToNonZero(combined) << endl;
//    cout << Cudd_NodeReadIndex(combined) << endl;

//    cout << Cudd_NodeReadIndex(Curr) << endl;
//    cout << Cudd_IsConstant(Curr) << endl;
    cout << Cudd_IsComplement(Curr3) << endl;
   /* while(!curr.IsEnd())
    {
        curr->current
    }*/
    
    //Cudd_PrintSummary(manager, f, 8, 0);
//    cout << Cudd_IsConstant(f)<< endl;
    BDDDiag = fopen("Lekker","w");
    Cudd_DumpDot(manager, 1, &combined, NULL,NULL,BDDDiag);
    
    return 0;
}
//Project day 4812 Matt and Ty nearly killed themselves trying to figure out how to traverse a CUDD BDD. However brilliance on Tyron's part saw them 
//figure out a solution and they unloaded the guns.
//Project day 4813. Solution turned out to be bogus. Guns reloaded.