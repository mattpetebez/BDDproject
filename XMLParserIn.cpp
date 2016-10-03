#include "XMLParserIn.h"

BinGroupedRule::BinGroupedRule(Accept_Deny _accept_deny, int _priority, Direction _direction, string _binRule)
{
    accept_deny = _accept_deny;
    direction = _direction;
    priority = _priority;
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
            //cout << line << endl;
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

    allRules.erase(0, pos + ruleDelimiter.size());
    StringRules.push_back(token);
    }
    token = allRules.substr(0, pos);
    StringRules.push_back(token);

    allRules.erase(0, pos + ruleDelimiter.size());
}



void XMLParserIn::buildBinRules()
{
    //For these rules, need action, direction, priority, protocol, dstipaddr, srcipaddr, srcportstart, srcportend, dstportstart, dstportend (srcmask?)
    Accept_Deny accept_deny;
    Direction direction;
    string priority;
    Protocol protocol;
    string ip;
    string srcportstart;
    string srcportend;
    string destportstart;
    string destportend;    
    
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
        }
        finder = currRule.find("drop");
        if(finder != string::npos)
        {
           // cout << "found a deny rule" << endl;
            accept_deny = Accept_Deny::deny;
        }

        
        //Need to find direction:
        finder = currRule.find("direction='in'");
        if(finder != string::npos)
        {
            direction = Direction::in;
        }
        else
        {
         direction = Direction::out;
        }
        
        //Need to find priority:
        string priorityDeleter = "priority='";
        deleter(priorityDeleter,currRule,priority);
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
        if(direction == Direction::in)
        {
        string srcIpDeleter = "srcipaddr='";
            if(deleter(srcIpDeleter,currRule,ip))
            {
                iptobin(ip);
            }
        }
        
        //Need to search for dstipaddress
        else if(direction == Direction::out)
        {
            //cout << "Found an out rule." << endl;
            string dstIpDeleter = "dstipaddr='";
            if(deleter(dstIpDeleter,currRule,ip))
            {
                iptobin(ip);
            }
        }
        
        //Need to find source port end:
        string srcPortDeleter = "srcportstart='";
        if(deleter(srcPortDeleter, currRule, srcportstart))
        {
            int temp = atoi(srcportstart.c_str());
            srcportstart = _decToBin.returnStr(temp, BIT_16);
        }
        
        //Need to find source port end
        srcPortDeleter = "srcportend='";
        if(deleter(srcPortDeleter, currRule, srcportend))
        {
            int temp = atoi(srcportend.c_str());
            srcportend = _decToBin.returnStr(temp, BIT_16);            
        }
        
        //Need to find dstportstart
        string dstPortDeleter = "dstportstart='";
        
        if(deleter(dstPortDeleter, currRule, destportstart))
        {
            int temp = atoi(destportstart.c_str());
            destportstart = _decToBin.returnStr(temp, BIT_16);
        }
        
        //Need to find dstportend
        dstPortDeleter = "dstportend='";
        if(deleter(dstPortDeleter, currRule, destportend))
        {
            int temp = atoi(destportend.c_str());
            destportend = _decToBin.returnStr(temp, BIT_16);
        }
        
        //Now need to check range: 4 ranges: srcip,dstip,srcport,dstport-> worry about it later
        
        //Determine whether rule belongs at inaccept, inreject, outaccept and outreject
        
        string wholeBinRule = "";
        int intProt = (int)protocol;
        wholeBinRule += (_decToBin.returnStr(intProt, BIT_8)) + srcportstart + destportstart + ip;
        GroupedRule binRule(accept_deny, intPriority, direction, wholeBinRule);
        if(direction == Direction::in)
        {
            inRules.push_back(binRule);
        }
        else
        {
           // cout << "Pushing back outrule." << endl;
           // cout <<"intPriority: " << intPriority << endl;
            outRules.push_back(binRule);
        }
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
        ipAsBin += _decToBin.returnStr(tmpDecIp, BIT_8);
        ip.erase(0, finder + delimiter.size());
    }
    ip = ipAsBin;
}

void XMLParserIn::sortBinGroupedRule()
{
    sortByPriority(inRules);
    sortByPriority(outRules);
}

void XMLParserIn::sortByPriority(vector<GroupedRule>& rules)//Need to changed to grouped rule
{
    //implement insertion sort by reference
    GroupedRule temp;
    int j;
    int limit = rules.size();
    for(int i =0; i<limit; i++)
    {
        j=i;
        while(j>0 && rules[j].returnPriority() < rules[j-1].returnPriority())
        {
            temp = rules[j];
            rules[j]=rules[j-1];
            rules[j-1]=temp;
            j--;
        }
    }
}

int BinGroupedRule::returnPriority()
{
    return priority;
}

BinGroupedRule::BinGroupedRule(){
    
}

void XMLParserIn::printRulesConsole()
{
    //cout << "input rules" << endl;
    for(auto i: inRules)
    {
        cout << i.returnPriority() << endl;
    }
  //  cout << "output rules" << endl;
    for (auto i : outRules)
    {
        cout << i.returnPriority() << endl;
    }
}

vector<GroupedRule> XMLParserIn::returnInRules()
{
    return inRules;
}
