#include "GroupedRule.h"


GroupedRule::GroupedRule()
{
    
}
GroupedRule::GroupedRule(Direction _direction, string _binRule)
{
    binRule.push_back(_binRule);
    direction = _direction;
    
    string srcPortTemp = _binRule.substr(8,16);
    checkForTwoRange(srcPortEnd, srcPortStart, srcPortTemp);
    
    string dstPortTemp = _binRule.substr(24, 16);
    checkForTwoRange(destPortEnd, destPortStart, dstPortTemp);
    
    string protocolTemp = _binRule.substr(0, 8);
    checkForTwoRange(protocolUpper, protocolLower, protocolTemp);
    
    if((returnProtocolRange() + 2) == (int)Protocol::all)
    {
        protocol = Protocol::all;
        setProtocolRange((int)protocol);
    }
    
    string ip1Temp = _binRule.substr(40, 8);
    checkForTwoRange(ip1Upper, ip1Lower, ip1Temp);
    
    string ip2Temp = _binRule.substr(48, 8);
    checkForTwoRange(ip2Upper, ip2Lower, ip2Temp);
    
    string ip3Temp = _binRule.substr(56, 8);
    checkForTwoRange(ip3Upper, ip3Lower, ip3Temp);
    
    string ip4Temp = _binRule.substr(64, 8);
    checkForTwoRange(ip3Upper, ip4Lower, ip4Temp);
    
    //extractRule(_binRule);
    priority = DEFAULT_PRIORITY;
    
}

GroupedRule::GroupedRule(Accept_Deny accept_deny, int _priority, Direction _direction, string wholeBinRule)
{
    action = accept_deny;
    priority = _priority;
    direction = _direction;
    binRule.push_back(wholeBinRule);
}

GroupedRule::GroupedRule(Protocol _protocol,int _srcPortStart,int _srcPortEnd,int _destPortStart,int _destPortEnd,int _ip1,int _ip2,
int _ip3, int _ip4,int _priority, Direction _direction,Accept_Deny _action)
{
    protocol = _protocol;
    srcPortStart = _srcPortStart;
    srcPortEnd = _srcPortEnd;
    destPortStart = _destPortStart;
    destPortEnd = _destPortEnd;
    ip1 = _ip1;
    ip2 = _ip2;
    ip3 = _ip3;
    ip4 = _ip4;
    priority = _priority;
    action = _action;
    direction = _direction;
    binRule = returnRangedBinRule();
    
    ip1Lower = ip1;
    ip1Upper = ip1;
    
    ip2Lower = ip2;
    ip2Upper = ip2;
    
    ip3Lower = ip3;
    ip3Upper = ip3;
    
    ip4Lower = ip4;
    ip4Upper = ip4;
    
    protocolLower = (int)protocol;
    protocolUpper = (int)protocol;
}
const string GroupedRule::returnProt()
{
    switch(protocol)
    {
        case Protocol::tcp:
        {
            //cout<<"Whats wrong with the code i dono tommy its tip top";
            return "tcp";
            break;
        }
        case Protocol::udp:
        {
            return "udp";
            break;
        }
        case Protocol::icmp:
        {
            return "icmp";
            break;
        }
        default:
        {
            cout<<"error the switch is not working in grouped rule";
        return "How those sausages, 5 minutes turkish";
        
        }
    }
}

const int GroupedRule::returnSrcPortStart()
{
    
    return srcPortStart;
   /* string tmp = to_string(srcPortStart);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;*/
}

const int GroupedRule::returnDestPortStart()
{
    
    return destPortStart;
 /*  string tmp = to_string(destPortStart);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;*/
}

const int GroupedRule::returnSrcPortEnd()
{
    
    return srcPortEnd;
   /* string tmp = to_string(srcPortEnd);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;*/
}

const int GroupedRule::returnDestPortEnd()
{
    
    return destPortEnd;
   /*string tmp = to_string(destPortEnd);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;*/
}

const string GroupedRule::returnIp1()
{
     string tmp = to_string(ip1);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

const string GroupedRule::returnIp2()
{
     string tmp = to_string(ip2);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

const string GroupedRule::returnIp3()
{
     string tmp = to_string(ip3);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

const string GroupedRule::returnIp4()
{
    string tmp = to_string(ip4);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

const string GroupedRule::returnWholeIP()
{
    return "'"+returnIp1()+"."+returnIp2()+"."+returnIp3()+"."+returnIp4()+"'";
}

GroupedRule::~GroupedRule()
{
}

const Direction GroupedRule::returnDirection()
{
    return direction;
}

const vector<string> GroupedRule::returnBinRule()
{
    return binRule;
}

void GroupedRule::extractRule(string& _binRule)
{
        binDecConverter converter;

        string _prot = _binRule.substr(0,8);
        if(_prot == "22222222")
        {
            _prot = "00000000";
        }
        
        int prot = converter.returnInt(_prot);
    
        protocol = (Protocol)prot;
    
        string _ip1 = _binRule.substr(40, 8);
        ip1 = atoi(_ip1.c_str());
        string _ip2 = _binRule.substr(48, 8);
        ip2 = atoi(_ip2.c_str());
        string _ip3 = _binRule.substr(56, 8);
        ip3 = atoi(_ip3.c_str());
        string _ip4 = _binRule.substr(64, 8);
        ip4 = atoi(_ip4.c_str());
}
const int GroupedRule::returnPriority()
{
    return priority;
}

bool GroupedRule::isRanged()
{
    if(srcPortEnd - srcPortStart != 0 || destPortEnd - destPortStart != 0)
    {
        return true;
    }
    else return false;
    
}

const vector<string> GroupedRule::returnRangedBinRule()
{
    vector<string> rangedBinRule;
    
/*    int srcportrange = srcPortEnd - srcPortStart;
    int dstportrange = destPortEnd - destPortStart;
    
    if(srcportrange == 0)
    {
        srcportrange += 1;
    }
    if(dstportrange == 0)
    {
        dstportrange += 1;
    }*/
    
    string binRule = "";
    int tempProt = (int)protocol;
    binRule += converter.returnStr(tempProt, 8);
    
    string ip = converter.returnStr(ip1, 8) + converter.returnStr(ip2, 8) + converter.returnStr(ip3, 8) + converter.returnStr(ip4, 8);
    
    for(int i = srcPortStart; i <= srcPortEnd; i++)
    {
        string currRule = "";
        int tempSrcPort = i;
        currRule += binRule;
        
        currRule += converter.returnStr(tempSrcPort, 16);
        for(int j = destPortStart; j <= destPortEnd; j++)
        {
            string innerCurrRule = currRule;
            int tempDstPort = j;
            innerCurrRule += converter.returnStr(tempDstPort, 16);
            innerCurrRule += ip;
            rangedBinRule.push_back(innerCurrRule);
        }
        
    }
    return rangedBinRule;
    
}

void GroupedRule::checkForTwoRange(int& upperBound, int& lowerBound, string& binaryRule)
{
    string binUpper = "";
    string binLower = "";
    
    string::iterator binIter = binaryRule.begin();
    
    while(binIter != binaryRule.end())
    {
        if((*binIter) == '1')
        {
            binUpper += '1';
            binLower += '1';
        }
        else if ((*binIter) == '0')
        {
            binUpper +='0';
            binLower +='0';
        }
        else if ((*binIter) == '2')
        {
            binUpper += '1';
            binLower += '0';
        }
        ++binIter;
    }
    upperBound = converter.returnInt(binUpper);
    lowerBound = converter.returnInt(binLower);
}

void GroupedRule::setSrcPortStart(int _srcportstart)
{
    srcPortStart = _srcportstart;
}

void GroupedRule::setSrcPortEnd(int _srcportend)
{
    srcPortEnd = _srcportend;
}

void GroupedRule::setDstPortStart(int _destportstart)
{
    destPortStart = _destportstart;
}

void GroupedRule::setDstPortEnd(int _destportend)
{
    destPortEnd = _destportend;
}
void GroupedRule::debugReturnEnglishRule()
{
    cout << "Protocol: " << (int)protocol << " srcportrange: " << srcPortStart << "-" << srcPortEnd << " dstportrange: "
 << destPortStart << "-" << destPortEnd << " IP: " << returnWholeIP() << endl; 
}

bool GroupedRule::isRanged()
{
    if(ip1Upper != ip1Lower || ip2Upper != ip2Lower || ip3Upper != ip3Lower || ip4Upper != ip4Lower || protocolUpper != protocolLower)
    {
        return true;
    }
    else return false;
}

vector<GroupedRule> GroupedRule::returnRangedGroup()
{
    vector<GroupedRule> returnRules;
    
    //Need to do range for protocol
    for(int i = protocolLower; i <= protocolUpper; i++)
    {
        GroupedRule newGrpRule = this;
        newGrpRule.setRangeProt(i);
        returnRules.push_back(newGrpRule);
    }
    
    //Now need to range ip1 FROM return rules:
    
    for(auto i: returnRules)
    {
        if(ip1Upper)
    }
}