#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H
#include <vector>
#include <fstream>
#include "GroupedRule.h"

enum class HTMLType
{
  viewFileRules = 1,
  viewActualRules
};

class HTMLBuilder
{
public:
    HTMLBuilder(string& _user, HTMLType _type, vector<GroupedRule> _rules);
    ~HTMLBuilder();
    void buildHTML();
private: 
    void printFileRules();
    void printActualRules();

    HTMLType type;
    string user;
    vector<GroupedRule> rules;
};

#endif // HTMLBUILDER_H
