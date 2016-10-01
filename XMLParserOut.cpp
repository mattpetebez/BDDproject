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
        part of seperate rule <udp dstportstart='53'/>
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

/*void XMLParserOut::printOutputrules()
{
    
}*/
string GroupedRule::returnProt()
{
    switch(prot)
    {
        case ((int)Protocol::tcp):
        {
            cout << "true you bitch" << endl;
            return "tcp";
            break;
        }
        case (int)Protocol::udp:
        {
            return "udp";
            break;
        }
        case (int)Protocol::icmp:
        {
            return "icmp";
            break;
        }
        default:
        return "Switch isn't working you cunt";
    }
}

string GroupedRule::returnSrcPort()
{
    return "'"+to_string(srcPort)+"'";
}

string GroupedRule::returnDestPort()
{
    return  "'"+to_string(destPort)+"'";
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

string GroupedRule::returnWholeIP()
{
    return "'"+returnIp1()+"."+returnIp2()+"."+returnIp3()+"."+returnIp4()+"'";
}