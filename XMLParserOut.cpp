#include "XMLParserOut.h"

XMLParserOut::XMLParserOut(vector<GroupedRule> _outRules)
{
    outRules = _outRules;
}

XMLParserOut::~XMLParserOut()
{
}

/*void XMLParserOut::setRules(vector<GroupedRule>& _rules)
{
    rules = _rules;
}*/

void XMLParserOut::orderByIPDesc()
{
    
}

string XMLParserOut::BinToDec()
{
    return "something";
}

/*void XMLParserOut::buildGroupRules()
{
    vector<GroupedRule>::iterator iter = rules.begin();
    
    while(iter != rules.end())
    {
        binDecConverter converter;
        string prot = (*iter).returnBinRule().substr(0,8);
        if(prot = "22222222")
        {
            prot = "00000000";
        }
        string srcPort = (*iter).returnBinRule().substr(8,16);
        if(srcPort = "2222222222222222")
        {
            srcPort = "0000000000000000"; //then later in rule creater we check were its zero and make it blank. nwfilter will remove it automatically.
            //coming now
        }
        string destPort = (*iter).substr(24, 16);
        string ip1 = (*iter).substr(40, 8);
        string ip2 = (*iter).substr(48, 8);
        string ip3 = (*iter).substr(56, 8);
        string ip4 = (*iter).substr(64, 8);
        (*iter).setFields(converter.returnInt(prot),converter.returnInt(srcPort),converter.returnInt(destPort),converter.returnInt(ip1)
        ,converter.returnInt(ip2),converter.returnInt(ip3),converter.returnInt(ip4));
        groupedRules.push_back(currGrpRule);
        ++iter;
    }
}*/

vector<string> XMLParserOut::ruleCreater()
{
    string wholerule = "";

    string ruleaction = "<rule action='accept'";
    
	string priority = " priority='500'";
    
	string direct = "direction=";
 

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
    vector<GroupedRule>::iterator iter = outRules.begin();
    
    while(iter != outRules.end())
    {
        GroupedRule currRule = (*iter);
        ip = currRule.returnWholeIP();
        if(currRule.returnDirection() == Direction::in)
        {
            ip = srcip + ip;
            direct += "'in'";
        }
        else
        {
            ip = dstip + ip;
            direct += "'out'";
        }
        protocol=currRule.returnProt();
        
        string destportstart = currRule.returnDestPort();
        //cout<<destportstart<<endl;
        string destportend = destportstart;//no range implementation yet
        string sourceportstart = currRule.returnSrcPort();
      //  cout<<sourceportstart<<endl;
        string sourceportend = sourceportstart;//no range implementation yet
        
        wholerule = ruleaction+direct+priority+">\n<"+protocol+ip+dstportstart+destportstart
        +dstportend+destportend+srcportstart+sourceportstart+srcportend+sourceportend+"/"+">\n"+endrule;
        xmlrules.push_back(wholerule);
        cout<<wholerule<<endl;
        
        direct = "direction=";
        ++iter;
    }
    
    return xmlrules;
} 

void XMLParserOut::printoutputRule(string& username)
{
    ofstream xmlOutputRules("/home/matt/" + username);
	if (xmlOutputRules.is_open())
	{
		xmlOutputRules << "<filter name='"+username+"-rules' chain='root'>\n";
        for(auto i: xmlrules)
        {
            xmlOutputRules <<"\t" << i << "\n";
           // cout<<i<<endl;
        }
        xmlOutputRules << "<rule action='reject' direction='inout' priority='100'/>\n";
        xmlOutputRules << "</filter>";
		xmlOutputRules.close();
	}
    else cerr << "Could not open file!" << endl;
}