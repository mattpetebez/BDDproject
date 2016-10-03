#include "BDDBuilder.h"
#include "RuleReturner.h"
#include "cudd.h"
#include "XMLParserOut.h"
#include "XMLParserIn.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
//    string rule1 = "111111111111111111111111111111000000000000000000000000000000111111000000";
    //cout<<rule1.size();
    //string rule2 = "101010101";
    //string rule3 = "101010101";
    string filename = "/home/BDDproject/XMLRuleFormat";
    XMLParserIn parserIn(filename);
    parserIn.buildStringRules();
    parserIn.buildBinRules();
    parserIn.sortBinGroupedRule();
  //  parserIn.printRulesConsole();
    
    vector<string> testRules;
//    
//    testRules.push_back(rule1);
//    //testRules.push_back(rule2);
//
////    testRules.push_back(rule3);
//
//    
    BDDBuilder bddbuilder(parserIn.returnInRules());
    bddbuilder.buildBDD();
//    
    RuleReturner rulereturner(bddbuilder.returnHead(), Direction::in);
    rulereturner.startRuleReturn();
    string lekker = "Lekker2";
    bddbuilder.printBDD(lekker);
//    string lekker3 = "Lekker3";
//    string accept = "accept";
//    bddbuilder.addRule(rule1, accept);
//    bddbuilder.printBDD(lekker3);
//    RuleReturner test(bddbuilder.returnHead(), Direction::in);
//    test.startRuleReturn();
/*    cout << test.validNoRules() << endl;
    cout << test.returnRules()[0] << endl;*/
//    cout << test.returnRules()[1] << endl;
//    cout << test.returnRules()[2] << endl;
//    cout << rulereturner.returnRules()[2] << endl;

    XMLParserOut parserOut(rulereturner.returnRules());
//    cout<<test.returnRules()[0].returnBinRule()<<endl;
    string barry = "Barry";
    parserOut.ruleCreater();
    parserOut.printoutputRule(barry);
    
    
    return 0;
}