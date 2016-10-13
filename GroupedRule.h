#ifndef GROUPEDRULE_H
#define GROUPEDRULE_H
#include <iostream>
#include <string>
#include <vector>

#include "binDecConverter.h"

#define DEFAULT_PRIORITY 500
#define MASKED_VALUE -1

enum class Accept_Deny
{
    accept,
    deny
};

enum class Direction
{
    in,
    out
};
enum class Protocol
{
    tcp=1,
    udp,
    icmp,
    all
};
enum class Field
{
  ip1Upper = 1,
  ip1Lower,
  ip2Upper,
  ip2Lower,
  ip3Upper,
  ip3Lower,
  ip4Upper,
  ip4Lower,
  protocolUpper,
  protocolLower,
  dstportstart,
  dstportend,
  srcportstart,
  srcportend,
  
  ip1Range,
  ip2Range,
  ip3Range,
  ip4Range,
  protocolRange
};

using namespace std;

class GroupedRule
{
public:
    GroupedRule();//Not sure if needed
    ~GroupedRule();
    
    GroupedRule(Protocol _protocol, int _srcPortStart,int _srcPortEnd,int _destPortStart,int _destPortEnd,
    int _ip1,int _ip2,int _ip3, int _ip4,int _priority, Direction _direction, Accept_Deny accept_deny); //Used for parser in
    
    GroupedRule(Direction _direction, string _binRule);//Needed for parser out
    
    GroupedRule(Accept_Deny accept_deny, int _priority, Direction _direction, string wholeBinRule);//Not sure of needed;
    
    const Direction returnDirection();
    const int returnPriority();
    const string returnProt();

    vector<GroupedRule> returnRangedGroup();
    
    bool isAllMasked(string& _binRule);
    
    bool isRanged();
    bool isPortRanged();
    

    const string returnWholeIP();

    const vector<string> returnBinRule();

    const vector<string> returnRangedBinRule();
    
    void debugReturnEnglishRule();
    
    void GenericSet(Field _field, int _value);
    int GenericReturn(Field _field);
private:
    void createBinRule();
    void extractRule(string& rule);
    void checkForTwoRange(int&, int&, string&);
    
    const string returnIp1();
    const string returnIp2();
    const string returnIp3();
    const string returnIp4();
    
    int srcPortStart;
    int srcPortEnd;
    
    int destPortStart;
    int destPortEnd;
    
    int protocolLower;
    int protocolUpper;
    
    int ip1Lower;
    int ip2Lower;
    int ip3Lower;
    int ip4Lower;
    
    int ip1Upper;
    int ip2Upper;
    int ip3Upper;
    int ip4Upper;
    
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    
    int priority;
    int _prot;
    
    Protocol protocol;
    Accept_Deny action;
    vector<string> binRule;
    Direction direction;
    
    binDecConverter converter;
};

#endif // GROUPEDRULE_H
