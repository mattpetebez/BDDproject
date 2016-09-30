#include <iostream>

#include "XMLParserOut.h"

using namespace std;

int main()
{
    vector<string> rules;
    string test = "000000010000000001010000000000000101000011000000101010000000000000000100";
    cout << test.size() << endl;
    rules.push_back(test);
    XMLParserOut xmlparserout;
    xmlparserout.setRules(rules);
    
    Direction _direction = Direction::out;
    Accept_Deny _accept_deny = Accept_Deny::deny;
    vector<string> xmlrules;
    
    xmlparserout.buildGroupRules();
    
    xmlrules = xmlparserout.outputRule(_direction,_accept_deny);
    
    cout << xmlrules[0] << endl;
    
    
    return 0;
}