#ifndef GROUPEDRULE_H
#define GROUPEDRULE_H
#include <iostream>
#include <string>
#include <vector>

#include "binDecConverter.h"

#define DEFAULT_PRIORITY 500
#define MASKED_VALUE -1

enum class Action
{
    accept=1,
    deny
};

enum class Direction
{
    in=1,
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
  ip1Upper = 1, //1
  ip1Lower, //2
  ip2Upper, //3
  ip2Lower, //4
  ip3Upper, //5
  ip3Lower, //6
  ip4Upper, //7
  ip4Lower, //8
  protocolUpper, //9
  protocolLower, //10
  dstportstart, //11
  dstportend, //12
  srcportstart, //13
  srcportend, //14
  
  ip1Range, //15
  ip2Range, //16
  ip3Range, //17
  ip4Range, //18
  protocolRange //19

};

using namespace std;

class GroupedRule
{
public:
    GroupedRule();//Not sure if needed
    ~GroupedRule();
    
    GroupedRule(Protocol _protocol, int _srcPortStart,int _srcPortEnd,int _destPortStart,int _destPortEnd,
    int _ip1,int _ip2,int _ip3, int _ip4,int _priority, Direction _direction, Action accept_deny); //Used for parser in
    
    GroupedRule(Direction _direction, string _binRule);//Needed for rule returner;
    
    GroupedRule(Action accept_deny, int _priority, Direction _direction, string wholeBinRule);//Not sure if needed;
    int returnAction();
    const Direction returnDirection();
    const int returnPriority();
    const string returnProt();

    vector<GroupedRule> returnRangedGroup();
    
    bool isAllMasked(string& _binRule);
    
    bool isRanged();
    bool isPortRanged();
    
    GroupedRule deepcopy();//Is needed?
    const string returnWholeIP();

    const vector<string> returnBinRule();

    const vector<string> returnRangedBinRule();
    
    void debugReturnEnglishRule();
    void setDirection(Direction);
    void GenericSet(Field _field, int _value);
    int GenericReturn(Field _field);
private:
    void createBinRule();
    void extractRule(string& rule);
    void checkForTwoRange(int&, int&, string&);
    
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
    
    int priority;
    int _prot;
    
    Protocol protocol;
    Action action;
    vector<string> binRule;
    Direction direction;
    
    binDecConverter converter;
};

#endif // GROUPEDRULE_H
