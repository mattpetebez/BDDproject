#include "XMLParserIn.h"

XMLParserIn::XMLParserIn(string& _filename)
{
    filename = _filename;
}



XMLParserIn::~XMLParserIn()
{
}

void XMLParserIn::buildStringRules()
{
    string line = "";\
    string ruleDelimiter = "<rule";
    string allRules = "";
    ifstream infile;
        /*
     *   .0\\
     * iprange ??
     */
    infile.open(filename);
    {
        while(getline(infile, line))
        {
            allRules += line;
        }
    }
	infile.close();

    string beginRuleDelimeter = "</uuid>";
    size_t initial = allRules.find(beginRuleDelimeter);
    allRules.erase(0, initial+beginRuleDelimeter.size());
    
    size_t pos = 0;
    string token;
    while ((pos = allRules.find(ruleDelimiter)) != std::string::npos)
    {
    token = allRules.substr(0, pos);
    cout << token << endl;
    allRules.erase(0, pos + ruleDelimiter.size());
    StringRules.push_back(token);
    }
    token = allRules.substr(0, pos);
    cout << token << endl;
    allRules.erase(0, pos + ruleDelimiter.size());
}

void XMLParserIn::buildBinRules()
{
    string protocol;
    string srcip;
    string destip;
    string srcport;
    string destport;
    string action;
    
}
