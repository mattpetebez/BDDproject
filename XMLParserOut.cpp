#include "XMLParserOut.h"

XMLParserOut::XMLParserOut()
{
}

XMLParserOut::~XMLParserOut()
{
}

void XMLParserOut::setRules(vector<string>& _rules)
{
    rules = _rules;
}

void XMLParserOut::orderByIPDesc()
{
    
}

string XMLParserOut::BinToDec()
{
    return "something";
}


GroupedRule::GroupedRule(int _prot,int _srcPort,int _destPort,int _ip1,int _ip2 ,int _ip3, int _ip4)
{
/*    if(wholeRule.size() != 72)
    {
        cerr << "Shit's fucked with this rule yo." << endl;
        return;
    }
    else
    {
       
    }*/
    
    prot = _prot;
    srcPort = _srcPort;
    destPort = _destPort;
    ip1 = _ip1;
    ip2 = _ip2;
    ip3 = _ip3;
    ip4 = _ip4;
}

void XMLParserOut::buildGroupRules()
{
    vector<string>::iterator iter = rules.begin();
    
    
    while(iter != rules.end())
    {
        binDecConverter converter;
        string prot = (*iter).substr(0,7);
        string srcPort = (*iter).substr(8,23);
        string destPort = (*iter).substr(24, 39);
        string ip1 = (*iter).substr(40, 47);
        string ip2 = (*iter).substr(48, 55);
        string ip3 = (*iter).substr(56, 63);
        string ip4 = (*iter).substr(64, 71);
        
        GroupedRule currGrpRule(converter.returnInt(prot),converter.returnInt(srcPort),converter.returnInt(destPort),converter.returnInt(ip1)
        ,converter.returnInt(ip2),converter.returnInt(ip3),converter.returnInt(ip4));
        groupedRules.push_back(currGrpRule);
        ++iter;
    }
}

vector<string> XMLParserOut::outputRule()
{
    string wholerule = "";
    string ruleaction = " <rule action=";
	string singlequote = "'";
	string priority = " priority=";
	string direction = " direction=";
	string nextline = "\n";
	string portstart = "<tcp dstportstart=";
	string endtag = "/>";
	string endarr =">";
	string endrule= " </rule>";
    
    /*
     * 
     * 
     * 
     * 
     * 
     * 
     */
    vector<GroupedRule>::iterator iter = groupedRules.begin();
    
    while(iter != groupedRules.end())
    {
        GroupedRule currRule = (*iter);
        
        
        
        ++iter;
    }
    
    return xmlrules;
} 

string GroupedRule::returnProt()
{
    return to_string(prot);
}

string GroupedRule::returnSrcPort()
{
    return to_string(srcPort);
}

string GroupedRule::returnDestPort()
{
    return to_string(destPort);
}

string GroupedRule::returnIp1()
{
    return to_string(ip1);
}

string GroupedRule::returnIp2()
{
    return to_string(ip2);
}

string GroupedRule::returnIp3()
{
    return to_string(ip3);
}

string GroupedRule::returnIp4()
{
    return to_string(ip4);
}
