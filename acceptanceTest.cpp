#include <iostream>
#include <vector>

#include "BDDBuilder.h"
#include "GroupedRule.h"
#include "RuleReturner.h"
#include "GroupedRuleSorter.h"
#include "XMLParserIn.h"
#include "XMLParserOut.h"
#include "RangeHelper.h"

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
    for(auto i: inRules)
    {
        i.debugReturnEnglishRule();
    }
    BDDBuilder BDDin(inRules);
    
    BDDin.buildBDD();
    
    string inBDDGraph = "/home/matt/LekkerMan";
   
    BDDin.printBDD(inBDDGraph);

    RuleReturner inRuleReturner(BDDin.returnHead(), Direction::in);
    
    inRules = inRuleReturner.returnRules();
    if(inRuleReturner.validNoRules())
    {
        
    }
    
    GroupedRuleSorter inSorter(inRules);
//    vector<GroupedRule> inRulesTemp;
//    inRulesTemp = inSorter.sortRules();
    inRules = inSorter.sortRules();

    XMLParserOut out;
    string username = "Barry";
    out.parseOutGroupedRules(inRules, username);
    
    return 0;
}