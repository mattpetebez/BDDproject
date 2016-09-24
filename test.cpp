#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "cudd.h"

using namespace std;

int main(int argv, char ** argc) 
{
    string rule = "10101010";
    DdManager* manager;
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
            var = Cudd_Complement(var);
            temp = Cudd_bddAnd(manager, var,f);
            var = Cudd_Regular(var);
        }
        Cudd_Ref(temp);
        //Cudd_RecursiveDeref(manager, f);
        f = temp;
        
    }   
    BDDDiag = fopen("test","w");
    Cudd_DumpDot(manager, 1, &f, NULL,NULL,BDDDiag);
    //Cudd_DumpFactoredForm(manager, 1, &f, NULL, NULL, BDDDiag);
    
    
    
    
    DdNode* curr = f;
    DdNode* curr2 = Cudd_E(curr);
    DdNode* curr3 = Cudd_T(curr2);
    DdNode* curr4 = Cudd_E(curr3);
    DdNode* curr5 = Cudd_T(curr4);
    DdNode* curr6 = Cudd_E(curr5);
    DdNode* curr7 = Cudd_T(curr6);
    //DdNode* curr8 = Cudd_E(curr7);
    cout << "Node " << Cudd_NodeReadIndex(f) << " is complemented: " << Cudd_IsComplement(f) << endl;
//    cout << "Node 2 is complemented: " << Cudd_IsComplement(curr2) << endl;
//    cout << "Node 4 is complemented: " << Cudd_IsComplement(curr4) << endl;
    
    
    return 0;
}