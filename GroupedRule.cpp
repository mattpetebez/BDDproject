#include "GroupedRule.h"


GroupedRule::GroupedRule()
{
    
}
GroupedRule::GroupedRule(Direction _direction, string _binRule)
{
    binRule = _binRule;
    direction = _direction;
    extractRule();
}

GroupedRule::GroupedRule(Accept_Deny accept_deny, int _priority, Direction _direction, string wholeBinRule)
{
    action = accept_deny;
    priority = _priority;
    direction = _direction;
    binRule = wholeBinRule;
}
string GroupedRule::returnProt()
{
    switch(prot)
    {
        case ((int)Protocol::tcp):
        {
            //cout<<"Whats wrong with the code i dono tommy its tip top";
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
        {
            cout<<"error";
        return "How those sausages, 5 minutes turkish";
        
        }
    }
}

string GroupedRule::returnSrcPort()
{
    string tmp = to_string(srcPort);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;
}

string GroupedRule::returnDestPort()
{
   string tmp = to_string(destPort);
    int temp = converter.returnInt(tmp);
    string sport= "'"+to_string(temp)+"'";
    return sport;
}

string GroupedRule::returnIp1()
{
     string tmp = to_string(ip1);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

string GroupedRule::returnIp2()
{
     string tmp = to_string(ip2);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

string GroupedRule::returnIp3()
{
     string tmp = to_string(ip3);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

string GroupedRule::returnIp4()
{
    string tmp = to_string(ip4);
    int temp = converter.returnInt(tmp);
    string sport= to_string(temp);
    return sport;
}

string GroupedRule::returnWholeIP()
{
    //cout<<"'"+returnIp1()+"."+returnIp2()+"."+returnIp3()+"."+returnIp4()+"'"<<endl;
    return "'"+returnIp1()+"."+returnIp2()+"."+returnIp3()+"."+returnIp4()+"'";
}

GroupedRule::~GroupedRule()
{
}

Direction GroupedRule::returnDirection()
{
    return direction;
}

const string GroupedRule::returnBinRule()
{
    return binRule;
}

void GroupedRule::extractRule()
{
        binDecConverter converter;
        string _prot = binRule.substr(0,8);
        if(_prot == "22222222")
        {
            _prot = "00000000";
        }
        prot = atoi(_prot.c_str());
        string _srcPort = binRule.substr(8,16);
        if(_srcPort == "2222222222222222")
        {
            _srcPort = "0000000000000000"; //then later in rule creater we check were its zero and make it blank. nwfilter will remove it automatically.
            //coming now
        }
        srcPort = atoi(_srcPort.c_str());
        string _destPort = binRule.substr(24, 16);
        destPort = atoi(_destPort.c_str());
        string _ip1 = binRule.substr(40, 8);
        ip1 = atoi(_ip1.c_str());
        string _ip2 = binRule.substr(48, 8);
        ip2 = atoi(_ip2.c_str());
        string _ip3 = binRule.substr(56, 8);
        ip3 = atoi(_ip3.c_str());
        string _ip4 = binRule.substr(64, 8);
        ip4 = atoi(_ip4.c_str());
       // cout<<ip4<<endl;
}
const int GroupedRule::returnPriority()
{
    return priority;
}
