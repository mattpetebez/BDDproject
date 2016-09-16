//BDD Class Defintion
using namespace std;

#include <memory>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iterator>

struct node{
public:
    node(int _lvl);
    ~node();
    void setlow(shared_ptr<node> _low);
    void sethigh(shared_ptr<node> _high);
    const int getRank();
    shared_ptr<node> getLow();
    shared_ptr<node> getHigh();
private:
    int lvl;
    shared_ptr<node> low, high;
};

#ifndef BDD_H
#define BDD_H

class BDD
{
public: 
    BDD(const string& _rule, const bool _ACCEPT);
    BDD(const string& _rule, const bool _ACCEPT, shared_ptr<node>&& ownerAccept, shared_ptr<node>&& ownerDeny);
    bool makeBDD();
    bool checkPacket(string& rule);
    
private:
    shared_ptr<node> makeBranch(string::iterator& iter, int Lvl);
    //void terminateNodes();
    shared_ptr<node> head;
    shared_ptr<node> accept;
    shared_ptr<node> reject;
    shared_ptr<node> genTerm;
    shared_ptr<node> term;
    string rule;
    bool ACCEPT;    
}
;

#endif 
