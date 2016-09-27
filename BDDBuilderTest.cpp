#include "BDDBuilder.h"
#include "RuleReturner.h"
//#include "cudd.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
    string rule1 = "012222010";
    string rule2 = "101010122";
    string rule3 = "222011100";
    
    vector<string> testRules;
    
    testRules.push_back(rule1);
    testRules.push_back(rule2);
    testRules.push_back(rule3);
    
    BDDBuilder bddbuilder(testRules);
    bddbuilder.buildBDD();
    
    RuleReturner rulereturner(bddbuilder.returnHead());
    rulereturner.startRuleReturn();
    string lekker = "Lekker2";
    bddbuilder.printBDD(lekker);
    cout << rulereturner.validNoRules() << endl;
    cout << rulereturner.returnRules()[2] << endl;
    
    
    return 0;
}