#include "XMLParserIn.h"

BinGroupedRule::BinGroupedRule(Accept_Deny _accept_deny, int _priority, Direction _direction, string _binRule)
{
    accept_deny = _accept_deny;
    direction = _direction;
    priority = priority;
    binRule = _binRule;    
}

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
//    cout << token << endl;
    allRules.erase(0, pos + ruleDelimiter.size());
}



void XMLParserIn::buildBinRules()
{
    //For these rules, need action, direction, priority, protocol, dstipaddr, srcipaddr, srcportstart, srcportend, dstportstart, dstportend (srcmask?)
    string priority;
    string srcip;
    string destip;
    string srcport;
    string destport;
    
    Direction direction;
    Accept_Deny accept_deny;
    Protocol protocol;
    
    vector<string>::iterator iter = StringRules.begin();
    
    while(iter != StringRules.end())
    {
        bool protFound = false;
        size_t finder;
        string currRule = *iter;
        
        
        //Finding action:
        finder = currRule.find("accept");
        if(finder != string::npos)
        {
            accept_deny = Accept_Deny::accept;
//            cout << "accept" << endl;
        }
        else 
        {
            accept_deny = Accept_Deny::deny;
//            cout << "deny" << endl;
        }

        
        //Need to find direction:
        finder = currRule.find("direction='in'");
        if(finder != string::npos)
        {
            direction = Direction::in;
//            cout << "direction in " << endl;
        }
        else
        {
         direction = Direction::out;
//         cout << "direction out" << endl;
        }
        
        //Need to find priority:
        string priorityDeleter = "priority='";
        deleter(priorityDeleter,currRule,priority);
//        cout<<priority<<endl;
        int intPriority = atoi(priority.c_str());
        
        //Need to find protocol:
        finder = currRule.find("tcp");
        if(finder != string::npos)
        {
            protocol = Protocol::tcp;
            protFound = true;
        }
        if(!protFound)
        {
            finder = currRule.find("udp");
            if(finder != string::npos)
            {
                protocol = Protocol::udp;
                protFound = true;
            }
            else
            {
                protocol = Protocol::icmp;
            }
        }
        
        //Need to search for srcipaddress
        string srcIpDeleter = "srcipaddr='";
        if(deleter(srcIpDeleter,currRule,srcip))
        {
            iptobin(srcip);
//            cout << srcip <<endl;
        }
        cout << currRule << endl;
        //Need to search for dstipaddress
        
        string dstIpDeleter = "dstipaddr='";
        if(deleter(dstIpDeleter,currRule,destip))
        {
            iptobin(destip);
            cout << dstIpDeleter << " Lekker Man " << destip << endl;
        }
        cout << currRule << endl;
        //Need to find source port:
        
   /*     string srcPortDeleter = "srcport='";
        if(de)
        */
        ++iter;
    }
    
}

bool XMLParserIn::deleter(string& find, string& currentRule,string &rulepiece)
{
        string srcIpDeleter = find;
        size_t finder = currentRule.find(srcIpDeleter);
        if(finder != string::npos)
        {
            currentRule.erase(0, finder + srcIpDeleter.size());
            finder = currentRule.find_first_of(find);
            rulepiece = currentRule.substr(0, finder);
            currentRule.erase(0, finder + 1);
            return true;
        }
        else return false;
}

void XMLParserIn::iptobin(string &ip)
{
    size_t finder;
    string delimiter = ".";
    string ipAsBin = "";
    
    while(finder != string::npos)
    {
        finder = ip.find(delimiter);
        int tmpDecIp =atoi(ip.substr(0, finder).c_str());
        ipAsBin += _decToBin.returnStr(tmpDecIp, 8);
        ip.erase(0, finder + delimiter.size());
    }
    ip = ipAsBin;
}
