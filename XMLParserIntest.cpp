#include <iostream>
#include "XMLParserIn.h"

using namespace std;

int main()
{
    string filename = "/home/BDDproject/XMLRuleFormat";
    XMLParserIn parserIn(filename);
    parserIn.buildStringRules();
    parserIn.buildBinRules();
    parserIn.sortBinGroupedRule();
    parserIn.printRulesConsole();
    return 0;
}