#include "XMLParserOut.h"

XMLParserOut::XMLParserOut(Direction _direction, Accept_Deny _accept_deny)
{
    direction   = _direction;
    accept_deny = _accept_deny;
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

void XMLParserOut::buildGroupRules()
{
    vector<string>::iterator iter = rules.begin();
    
    while(iter != rules.end())
    {
        binDecConverter converter;
        string prot = (*iter).substr(0,8);
        if(prot = "22222222")
        {
            prot = "00000000";
        }
        string srcPort = (*iter).substr(8,16);
        if(srcPort = "2222222222222222")
        {
            srcPort = "00000000"; //then later in rule creater we check were its zero and make it blank. nwfilter will remove it automatically.
            //coming now
        }
        string destPort = (*iter).substr(24, 16);
        string ip1 = (*iter).substr(40, 8);
        string ip2 = (*iter).substr(48, 8);
        string ip3 = (*iter).substr(56, 8);
        string ip4 = (*iter).substr(64, 8);
        GroupedRule currGrpRule(converter.returnInt(prot),converter.returnInt(srcPort),converter.returnInt(destPort),converter.returnInt(ip1)
        ,converter.returnInt(ip2),converter.returnInt(ip3),converter.returnInt(ip4));
        groupedRules.push_back(currGrpRule);
        ++iter;
    }
}

vector<string> XMLParserOut::ruleCreater()
{
    string wholerule = "";

    string ruleaction = "<rule action=";
    if(accept_deny == Accept_Deny::accept)
    {
        ruleaction += "'accept' ";
    }
    else ruleaction += "'reject' ";
    
	string priority = " priority='500'";
    
	string direct = "direction=";
    if(direction == Direction::in)
    direct += "'in'";
    else direct += "'out'";

	string endrule= "</rule>";
    string srcip = " srcipaddr=";
    string dstip =" dstipaddr=";
    string ip = "";
    string protocol="";

    string dstportstart = " dstportstart=";
    string dstportend = " dstportend=";
    string srcportstart = " srcportstart=";
    string srcportend =" srcportend=";

    /*
     *  <rule action='accept' direction='in' priority='400'>
        <tcp srcipaddr='196.44.24.27' dstipaddr='192.168.1.16' srcipmask='16' dstportstart='80' dstportend='100' srcportstart='80' srcportend='100'/>
        </rule>
     * iprange ??
     */
    vector<GroupedRule>::iterator iter = groupedRules.begin();
    
    while(iter != groupedRules.end())
    {
        GroupedRule currRule = (*iter);
        ip = currRule.returnWholeIP();
        if(direction == Direction::in)
        {
            ip = srcip + ip;
        }
        else
        {
            ip = dstip + ip;
        }
        protocol=currRule.returnProt();
        
        string destportstart = currRule.returnDestPort();
        string destportend = destportstart;//no range implementation yet
        string sourceportstart = currRule.returnSrcPort();
        string sourceportend = sourceportstart;//no range implementation yet
        
        wholerule = ruleaction+direct+priority+">\n<"+protocol+ip+dstportstart+destportstart
        +dstportend+destportend+srcportstart+sourceportstart+srcportend+sourceportend+"/"+">\n"+endrule;
        xmlrules.push_back(wholerule);
        
        ++iter;
    }
    
    return xmlrules;
} 
