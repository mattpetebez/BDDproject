#include <iostream>

#include "RangeHelper.h"
#include "XMLParserOut.h"
#include "GroupedRule.h"

using namespace std;

int main()
{
    GroupedRule one(Protocol::tcp, 80,100,80,100,192,168,1,1,500,Direction::out,Accept_Deny::accept);
    GroupedRule two(Protocol::tcp, 80,100,80,100,10,10,1,2,500,Direction::in,Accept_Deny::accept);
    GroupedRule three(Protocol::tcp, 80,100,80,100,10000,1000,100,1,500,Direction::in,Accept_Deny::accept);
    
    one.GenericSet(Field::ip4Lower, 1);
    one.GenericSet(Field::ip4Upper, 8);
    
    two.GenericSet(Field::ip4Lower, 1);
    two.GenericSet(Field::ip4Upper, 8);
    
    three.GenericSet(Field::ip4Lower, 1);
    three.GenericSet(Field::ip4Upper, 8);
    
    vector<GroupedRule> temp2;
    
    vector<GroupedRule> temp4;
    RangeHelper helper;
    
    temp2.push_back(one);
    temp2.push_back(two);
    temp2.push_back(three);
    
    XMLParserOut out;
    string username = "Barry";
    out.parseOutGroupedRules(temp2, username);
}