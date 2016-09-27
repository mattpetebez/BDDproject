#include "BDDBuilder.h"
#include "RuleReturner.h"
//#include "cudd.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
    string rule1 = "01012222222201222201";
//    string rule2 = "11101010";
    string rule3 = "10102222222210122220";
    
    vector<string> testRules;
    
    testRules.push_back(rule1);
//    testRules.push_back(rule2);
    testRules.push_back(rule3);
    
    BDDBuilder bddbuilder(testRules);
    bddbuilder.buildBDD();
    
    RuleReturner rulereturner(bddbuilder.returnHead());
    rulereturner.startRuleReturn();
    
    bddbuilder.printBDD();
    cout << rulereturner.validNoRules() << endl;
    cout << rulereturner.returnRules()[0] << endl;
    
    
    return 0;
}