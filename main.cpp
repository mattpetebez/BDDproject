#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "cudd.h"
#include "RuleReturner.h"
using namespace std;


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
    string rule = "11101110";
    //cout << rule.at(20) << endl;
    DdManager* manager;
    
    vector<DdNode>* BDDs;
    FILE* BDDDiag;
    
    manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    
    DdNode* temp, *var, *f, *g, *h;
    int bit = 28;
    int i;
    
    f = Cudd_ReadOne(manager);
    Cudd_Ref(f);
    for (i = bit; i >= 21; i--)
    {
        var = Cudd_bddIthVar(manager, i);
        if (rule.at(i-21) == '1')
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
    for (i = bit; i >= 21; i--)
    {
        var = Cudd_bddIthVar(manager, i);
        if (rule.at(i-21) == '1')
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
    
    rule = "01010101"; //Tyron coded this part :P
    h = Cudd_ReadOne(manager);
    Cudd_Ref(h);
    for (i = bit; i >= 21; i--)
    {
        var = Cudd_bddIthVar(manager, i);
        if (rule.at(i-21) == '1')
        {
            temp = Cudd_bddAnd(manager, var, h);
        }
        else
        {
            temp = Cudd_bddAnd(manager, Cudd_Not(var), h);
        }
        Cudd_Ref(temp);
        Cudd_RecursiveDeref(manager, h);
        h = temp;
    }
    
    
    
   
    
    DdNode * combined = Cudd_bddOr(manager,f,g);//All Tyron
    DdNode * threerules = Cudd_bddOr(manager,combined,h);
    BDDit bddit;
    bddit.setCurr(threerules);
    RuleReturner rulereturner(threerules);
    rulereturner.findBddRules(bddit);
    
    bool valid = rulereturner.validNoRules();
    vector <string> r = rulereturner.returnRules();
    
    cout<<valid<<endl;
    cout<<r[2]<<endl;
    cout<<r[1]<<endl;
    cout<<r[0]<<endl;
    cout<<Cudd_NodeReadIndex(g) << endl;
    
    DdNode * Curr = Cudd_T(combined);
    DdNode * Curr2 = Cudd_E(Curr);
    DdNode * Curr3 = Cudd_E(Curr2);
//    cout << Cudd_CountPathsToNonZero(combined) << endl;
//    cout << Cudd_NodeReadIndex(combined) << endl;

//    cout << Cudd_NodeReadIndex(Curr) << endl;
//    cout << Cudd_IsConstant(Curr) << endl;
    //cout << Cudd_IsComplement(Curr3) << endl;
   /* while(!curr.IsEnd())
    {
        curr->current
    }*/
    
    //Cudd_PrintSummary(manager, f, 8, 0);
//    cout << Cudd_IsConstant(f)<< endl;
    BDDDiag = fopen("Lekker","w");
    Cudd_DumpDot(manager, 1, &threerules, NULL,NULL,BDDDiag);
    
    return 0;
}
//Project day 4812 Matt and Ty nearly killed themselves trying to figure out how to traverse a CUDD BDD. However brilliance on Tyron's part saw them 
//figure out a solution and they unloaded the guns.
//Project day 4813. Solution turned out to be bogus. Guns reloaded.