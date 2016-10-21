#include "XMLParserIn.h"

XMLParserIn::XMLParserIn(string& _filename)
{
    filename = _filename;
}

XMLParserIn::~XMLParserIn()
{
}

void XMLParserIn::buildInOutRules(vector<GroupedRule>& _inRules, vector<GroupedRule>& _outRules)
{
    buildStringRules();
    buildBinRules();
    sortByPriority(inRules);
    sortByPriority(outRules);
    
    _inRules = inRules;
    _outRules = outRules;
}

void XMLParserIn::buildStringRules()
{
    string line = "";
    string ruleDelimiter = "<rule";
    string allRules = "";
    ifstream infile;

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

    allRules.erase(0, pos + ruleDelimiter.size());
    StringRules.push_back(token);
    }
    token = allRules.substr(0, pos);
    StringRules.push_back(token);

    allRules.erase(0, pos + ruleDelimiter.size());
}



void XMLParserIn::buildBinRules()
{
    Action action;
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
            action = Action::accept;
        }
        finder = currRule.find("drop");
        if(finder != string::npos)
        {
            action = Action::deny;
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
            string dstIpDeleter = "dstipaddr='";
            if(deleter(dstIpDeleter,currRule,ip))
            {
                iptobin(ip);
            }
        }
        int srcportstartint=0;
        int srcportendint=0;
        //Need to find source port start:
        string srcPortDeleter = "srcportstart='";
        if(deleter(srcPortDeleter, currRule, srcportstart))
        {
            int temp = atoi(srcportstart.c_str());
            srcportstartint = temp;
            srcportstart = _decToBin.returnStr(temp, BIT_16);
        }
        
        //Need to find source port end
        srcPortDeleter = "srcportend='";
        if(deleter(srcPortDeleter, currRule, srcportend))
        {
            int temp = atoi(srcportend.c_str());
            srcportendint = temp;
            srcportend = _decToBin.returnStr(temp, BIT_16);            
        }
        
        //Need to find dstportstart
        string dstPortDeleter = "dstportstart='";
        int destportstartint=0;
        
        if(deleter(dstPortDeleter, currRule, destportstart))
        {
            int temp = atoi(destportstart.c_str());
            destportstartint=temp;
            destportstart = _decToBin.returnStr(temp, BIT_16);
        }
        int destportendint=0;
        //Need to find dstportend
        dstPortDeleter = "dstportend='";
        if(deleter(dstPortDeleter, currRule, destportend))
        {
            int temp = atoi(destportend.c_str());
            destportendint =temp;
            destportend = _decToBin.returnStr(temp, BIT_16);
        }
        
        string wholeBinRule = "";
	
        GroupedRule binRule(protocol, srcportstartint,srcportendint,destportstartint,destportendint,ips[0],ips[1],ips[2],ips[3],intPriority,direction,action);
       
	   if(direction == Direction::in)
        {
			if(intPriority!=0)
            inRules.push_back(binRule);
			
			//binRule.debugReturnEnglishRule();
        }
        else
        {
			if(intPriority!=0)
            outRules.push_back(binRule);
			
			//binRule.debugReturnEnglishRule();
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
    int count =0;
    while(finder != string::npos)
    {
        finder = ip.find(delimiter);
        int tmpDecIp =atoi(ip.substr(0, finder).c_str());
        ipAsBin += _decToBin.returnStr(tmpDecIp, BIT_8);
        ip.erase(0, finder + delimiter.size());
        count++;
    }
    ip = ipAsBin;
    string temp = ip.substr(0,8);
    ips[0]= _decToBin.returnInt(temp);
    temp = ip.substr(8,8);
    ips[1]= _decToBin.returnInt(temp);
    temp = ip.substr(16,8);
    ips[2]= _decToBin.returnInt(temp);
    temp = ip.substr(24,8);
    ips[3]= _decToBin.returnInt(temp);
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



void XMLParserIn::printRulesConsole()
{
    for(auto i: inRules)
    {
        cout << i.returnPriority() << endl;
    }
    for (auto i : outRules)
    {
        cout << i.returnPriority() << endl;
    }
}
//Lekker