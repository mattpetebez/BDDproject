#include "BDDBuilder.h"
#include "RuleReturner.h"
//#include "cudd.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
<<<<<<< Updated upstream
    string rule1 = "000101010";
    string rule2 = "101010101";
    string rule3 = "101111001";
=======
    string rule1 = "0000000000";
	string rule2 = "1111111111";
    string rule3 = "2222222222";
>>>>>>> Stashed changes
    
    vector<string> testRules;
    
    testRules.push_back(rule1);
    testRules.push_back(rule2);
<<<<<<< Updated upstream
    testRules.push_back(rule3);
=======
    //testRules.push_back(rule3);
>>>>>>> Stashed changes
    
    BDDBuilder bddbuilder(testRules);
    bddbuilder.buildBDD();
    
    RuleReturner rulereturner(bddbuilder.returnHead());
    rulereturner.startRuleReturn();
    string lekker = "Lekker2";
    bddbuilder.printBDD(lekker);
    cout << rulereturner.validNoRules() << endl;
    cout << rulereturner.returnRules()[0] << endl;
    cout << rulereturner.returnRules()[1] << endl;
    cout << rulereturner.returnRules()[2] << endl;
    
    
    
    return 0;
}