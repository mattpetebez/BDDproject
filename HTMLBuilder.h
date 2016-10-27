#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H
#include <vector>
#include <fstream>
#include "GroupedRule.h"

enum class HTMLType
{
  viewFileRules = 1,
  viewActualRules,
  deleteRule
};

class HTMLBuilder
{
public:
    HTMLBuilder(string& _user, HTMLType _type, vector<GroupedRule> _rules);
	HTMLBuilder();
    ~HTMLBuilder();
    void buildHTML();
	void allowedRules(vector<GroupedRule> _rules, string _user);
private: 
    void printFileRules();
    void printActualRules();
    void printDeleteRulePage();

    HTMLType type;
    string user;
    vector<GroupedRule> rules;
};

#endif // HTMLBUILDER_H
