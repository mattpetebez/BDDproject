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
 }//What do we need to do still?
//Need to manage the range requirements. This can be done using a range helper class that takes in a grouped rule and returns a vector of grouped rules.
//Need to deal with 444444444444444444444444444444444444444 fuck you science
//Need to make the super machine and fire wall classes. Firewall will hold the machines and deal with rule requests. Machines will host the rule sets for themselves as well as being responsible for developing their own BDDs.
//Ned to make a BDD node checker/helper for the firewall class for validating rules that may conflict with the administrative rules.
//Need to implement a parser out helper class that assists output range grouping. 
//Need to think of a way to manage the BDDs in memory constantly, and also consider the rebuilding of BDDs as required (provided they are a rule that has a higher priority than some check we perfomr to prevent the invalidation of rules desired to be kept.
//At some point, need to get the web server up and running. Lekker man.