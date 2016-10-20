#include "GroupedRule.h"


GroupedRule::GroupedRule()
{
    
}
GroupedRule::GroupedRule(Direction _direction, string _binRule)
{
    direction = _direction;
    string protocolTemp = _binRule.substr(0, 8);
    if(isAllMasked(protocolTemp))
    {
       GenericSet(Field::protocolRange, (int)Protocol::all);
       protocol = (Protocol)protocolUpper;
    }
    else
    {
        checkForTwoRange(protocolUpper, protocolLower, protocolTemp);
        protocol = (Protocol)protocolUpper;
    }
    string srcPortTemp = _binRule.substr(8,16);
    if(isAllMasked(srcPortTemp))
    {
       GenericSet(Field::srcportstart, MASKED_VALUE);
       GenericSet(Field::srcportend, MASKED_VALUE);
    }
    else
    {
        checkForTwoRange(srcPortEnd, srcPortStart, srcPortTemp);
    }
    
    string dstPortTemp = _binRule.substr(24, 16);
    
    if(isAllMasked(dstPortTemp))
    {
       GenericSet(Field::dstportstart, MASKED_VALUE);
       GenericSet(Field::dstportend, MASKED_VALUE);
    }
    else
    {
        checkForTwoRange(destPortEnd, destPortStart, dstPortTemp);
    }
    
    
    string ip1Temp = _binRule.substr(40, 8);
    if(isAllMasked(ip1Temp))
    {
       GenericSet(Field::ip1Range, MASKED_VALUE);
    }
    else
    {
        checkForTwoRange(ip1Upper, ip1Lower, ip1Temp);
    }
    
    
    string ip2Temp = _binRule.substr(48, 8);
    if(isAllMasked(ip2Temp))
    {
       GenericSet(Field::ip2Range, MASKED_VALUE);
    }
   else
    {
        checkForTwoRange(ip2Upper, ip2Lower, ip2Temp);
    }
   
    
    string ip3Temp = _binRule.substr(56, 8);
    if(isAllMasked(ip3Temp))
    {
       GenericSet(Field::ip3Range, MASKED_VALUE);
    }
    else
    {
        checkForTwoRange(ip3Upper, ip3Lower, ip3Temp);
    }
    
    
    string ip4Temp = _binRule.substr(64, 8);
    if(isAllMasked(ip4Temp))
    {
       GenericSet(Field::ip4Range, MASKED_VALUE);
    }
    else
    {
        checkForTwoRange(ip4Upper, ip4Lower, ip4Temp);
    }

    priority = DEFAULT_PRIORITY;
}

GroupedRule::GroupedRule(Action _action, int _priority, Direction _direction, string wholeBinRule)
{
    action = _action;
    priority = _priority;
    direction = _direction;
    binRule.push_back(wholeBinRule);
}

int GroupedRule::returnAction()
{
    return (int)action;
}

GroupedRule::GroupedRule(Protocol _protocol,int _srcPortStart,int _srcPortEnd,int _destPortStart,int _destPortEnd,int _ip1,int _ip2,
int _ip3, int _ip4,int _priority, Direction _direction,Action _action)
{
    protocol = _protocol;
    srcPortStart = _srcPortStart;
    srcPortEnd = _srcPortEnd;
    destPortStart = _destPortStart;
    destPortEnd = _destPortEnd;

    priority = _priority;
    action = _action;
    direction = _direction;
    
    ip1Lower = _ip1;
    ip1Upper = _ip1;
    
    ip2Lower = _ip2;
    ip2Upper = _ip2;
    
    ip3Lower = _ip3;
    ip3Upper = _ip3;
    
    ip4Lower = _ip4;
    ip4Upper = _ip4;
    
    protocolLower = (int)protocol;
    protocolUpper = (int)protocol;
    
    binRule = returnRangedBinRule();
}
const string GroupedRule::returnProt()
{
    switch(protocol)
    {
        case Protocol::tcp:
        {
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
            cout << "Error the switch is not working in grouped rule" << endl;
            return "How those sausages, 5 minutes turkish";
        }
    }
}

bool GroupedRule::isAllMasked(string& _binRule)
{
    bool allMasked = true;
    for(auto i: _binRule)
    {
        if(i != '2')
        {
            allMasked = false;
        }
    }
    return allMasked;
}

const string GroupedRule::returnWholeIP()
{
    return "'"+to_string(ip1Lower)+"."+to_string(ip2Lower)+"."+to_string(ip3Lower)+"."+to_string(ip4Lower)+"'";
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

const int GroupedRule::returnPriority()
{
    return priority;
}

bool GroupedRule::isPortRanged()
{
    if (srcPortEnd - srcPortStart != 0 || destPortEnd - destPortStart != 0)
    {
        return true;
    }
    else return false;
}

bool GroupedRule::isRanged()
{
    if(GenericReturn(Field::ip1Range) > 0 || GenericReturn(Field::ip2Range) > 0 || GenericReturn(Field::ip3Range) > 0
    || GenericReturn(Field::ip4Range) > 0 || GenericReturn(Field::protocolRange) > 0)
    {
        return true;
    }
    else return false;
    
}

const vector<string> GroupedRule::returnRangedBinRule()
{
    vector<string> rangedBinRule;
    
    string binRule = "";
    int tempProt = (int)protocol;
    binRule += converter.returnStr(tempProt, 8);
    
    string ip = converter.returnStr(ip1Lower, 8) + converter.returnStr(ip2Lower, 8) + converter.returnStr(ip3Lower, 8) + converter.returnStr(ip4Lower, 8);
    
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
    if(binaryRule.find('2') != string::npos)
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
    else
    {
        upperBound = converter.returnInt(binaryRule);
        lowerBound = upperBound;
    }
    
}

void GroupedRule::debugReturnEnglishRule()
{
    cout << "Protocol: " << (int)protocol << " srcportrange: " << srcPortStart << "-" << srcPortEnd << " dstportrange: "
 << destPortStart << "-" << destPortEnd << " IP: " << returnWholeIP() << endl; 
}
GroupedRule GroupedRule::deepcopy()
{
    
    GroupedRule temp;
    temp.direction = direction;
    
    temp.ip1Lower = ip1Lower;
    temp.ip2Lower = ip2Lower;
    temp.ip3Lower = ip3Lower;
    temp.ip4Lower = ip4Lower;
    
    temp.ip1Upper = ip1Upper;
    temp.ip2Upper = ip2Upper;
    temp.ip3Upper = ip3Upper;
    temp.ip4Upper = ip4Upper;

    temp.protocolUpper = protocolUpper;
    temp.protocolLower = protocolLower;
    
    temp.srcPortStart = srcPortStart;
    temp.srcPortEnd = srcPortEnd;
    temp.destPortStart = destPortStart;
    temp.destPortEnd = destPortEnd;
    
    temp.protocol = protocol;
    temp.priority = priority;
    temp.action = action;
    temp.binRule = binRule;
    temp._prot = _prot;
    return temp;
}

void GroupedRule::setDirection(Direction _direction)
{
    direction =_direction;
}

void GroupedRule::GenericSet(Field _field, int _value)
{
    switch(_field)
    {
        case Field::ip1Lower:
        {
            ip1Lower = _value;
            break;
        }
        case Field::ip1Upper:
        {
            ip1Upper = _value;
            break;
        }
        case Field::ip2Lower:
        {
            ip2Lower = _value;
            break;
        }
        case Field::ip2Upper:
        {
            ip2Upper = _value;
            break;
        }
        case Field::ip3Lower:
        {
            ip3Lower = _value;
            break;
        }
        case Field::ip3Upper:
        {
            ip3Upper = _value;
            break;
        }
        case Field::ip4Lower:
        {
            ip4Lower = _value;
            break;
        }
        case Field::ip4Upper:
        {
            ip4Upper = _value;
            break;
        }
        case Field::protocolLower:
        {
            protocolLower = _value;
            break;
        }
        case Field::protocolUpper:
        {
            protocolUpper = _value;
            break;
        }        
        case Field::ip1Range:
        {
            ip1Lower = _value;
            ip1Upper = _value;
            break;
        }        
        case Field::ip2Range:
        {
            ip2Lower = _value;
            ip2Upper = _value;
            break;
        }        
        case Field::ip3Range:
        {
            ip3Lower = _value;
            ip3Upper = _value;
            break;
        }        
        case Field::ip4Range:
        {
            ip4Lower = _value;
            ip4Upper = _value;
            break;
        }        
        case Field::protocolRange:
        {
            protocolLower = _value;
            protocolUpper = _value;
            protocol = (Protocol)_value;
            break;
        }
        case Field::dstportstart:
        {
            destPortStart = _value;
            break;
        }
        case Field::dstportend:
        {
             destPortEnd = _value;
             break;
        }
        case Field::srcportstart:
        {
             srcPortStart = _value;
             break;
        }
        case Field::srcportend:
        {
             srcPortEnd = _value;
             break;
        }
        default:
        {
            cout << "I don't know Tommy. It's TIP-TOP." << endl;
        }
    }
}

int GroupedRule::GenericReturn(Field _field)
{
    switch(_field)
    {
        case Field::ip1Lower:
        {
            return ip1Lower;
            break;
        }
        case Field::ip1Upper:
        {
            return ip1Upper;
            break;
        }
        case Field::ip2Lower:
        {
            return ip2Lower;
            break;
        }
        case Field::ip2Upper:
        {
            return ip2Upper;
            break;
        }
        case Field::ip3Lower:
        {
            return ip3Lower;
            break;
        }
        case Field::ip3Upper:
        {
            return ip3Upper;
            break;
        }
        case Field::ip4Lower:
        {
            return ip4Lower;
            break;
        }
        case Field::ip4Upper:
        {
            return ip4Upper;
            break;
        }
        case Field::protocolLower:
        {
            return protocolLower;
            break;
        }
        case Field::protocolUpper:
        {
            return protocolUpper;
            break;
        }
        
        case Field::ip1Range:
        {
            return ip1Upper - ip1Lower;
            break;
        }        
        case Field::ip2Range:
        {
            return ip2Upper - ip2Lower;
            break;
        }        
        case Field::ip3Range:
        {
            return ip3Upper - ip3Lower;
            break;
        }        
        case Field::ip4Range:
        {
            return ip4Upper - ip4Lower;
            break;
        }        
        case Field::protocolRange:
        {
            return protocolUpper - protocolLower;
            break;
        }
        case Field::dstportstart:
        {
            return destPortStart;
            break;
        }
        case Field::dstportend:
        {
            return destPortEnd;
            break;
        }
        case Field::srcportstart:
        {
            return srcPortStart;
            break;
        }
        case Field::srcportend:
        {
            return srcPortEnd;
            break;
        }
        default:
        {
            cout << "Tommy, the tit, is praying; and if he isn't, he fucken should be." << endl;
            return -1;
        }
    }
}