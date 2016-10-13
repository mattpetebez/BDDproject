#include <iostream>
#include <vector>

#include "BDDBuilder.h"
#include "GroupedRule.h"
#include "RuleReturner.h"
#include "GroupedRuleSorter.h"
#include "XMLParserIn.h"
#include "XMLParserOut.h"

//First, rules are parsed from a file containing the XML rules into the grouped rule format.
//Need to add an addrule function to parserin at some point that adds priority?

//Second: A bdd is built using all the rules parsed in. (BDDBUilder Review)

using namespace std;

int main()
{
    vector<GroupedRule> inRules, outRules;
    string filename = "/home/matt/Larry-rules";
    
    XMLParserIn xmlparserin(filename);
    xmlparserin.buildInOutRules(inRules, outRules);


    BDDBuilder BDDin(inRules);
//    BDDBuilder BDDout(outRules);
    
    BDDin.buildBDD();
//    BDDout.buildBDD();
    
    
    string inBDDGraph = "/home/matt/Documents/inBDDBgraph";
//    string outBDDGraph = "outBDDgraph";
    
    
     BDDin.printBDD(inBDDGraph);
//     BDDout.printBDD(outBDDGraph);
    
    RuleReturner inRuleReturner(BDDin.returnHead(), Direction::in);
//    RuleReturner outRuleReturner(BDDout.returnHead(), Direction::out);
    
    inRules = inRuleReturner.returnRules();
    for (auto i: inRules)
    {
        i.debugReturnEnglishRule();
    }
//    outRules = outRuleReturner.returnRules();
    
/*    GroupedRuleSorter inSorter(inRules);
//    GroupedRuleSorter outSorter(outRules);
    vector<GroupedRule> inRulesTemp;
//    inRules = inSorter.sortRules();
//    outSorter.sortRules();
//    inRules = inRulesTemp;
    for(auto i: inRules)
    {
        
        i.debugReturnEnglishRule();
    }
    
    vector<vector<GroupedRule>> testeing = inSorter.returnGroup();*/
/*    cout<<"The size of testeing is: "<<testeing.size()<<endl;
    cout<<"The size of the one ip vector is: "<<testeing[0].size()<<endl;
    cout<<"The size of the other ip vector is: "<<testeing[1].size()<<endl;
    testeing[0][0].debugReturnEnglishRule();
    testeing[0][1].debugReturnEnglishRule();
    testeing[1][0].debugReturnEnglishRule();*/
    return 0;
}