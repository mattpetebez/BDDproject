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
    void setlow(node& _low);
    void sethigh(node& _high);
private:
    int lvl;
    shared_ptr<node> low, high;
};

node::node(int _lvl)
{
    lvl = _lvl;
}

void node::setlow(node& _low)
{
    low = make_shared<node>(_low);
}

void node::sethigh(node& _high)
{
    high = make_shared<node>(_high);
}

#ifndef BDD_H
#define BDD_H

class BDD
{
public: 
    BDD(string&);
    bool makeBDD(string& rule);
    
private:
    shared_ptr<node> makeBranch(string::iterator& iter, int Lvl); 
    shared_ptr<node> head;
    shared_ptr<node> deny;
    shared_ptr<node> accept;
    string rule;
    
};

BDD::BDD(string& _rule)
{
    rule = _rule;
}

bool BDD::makeBDD(string& rule)
{
    if(rule.size() != 8)
    {
        return false;
    }
    else
    {
        vector<shared_ptr<node>> nodes;
        
        for (auto i: rule)
        {
            shared_ptr<node> currNode = make_shared<node>(node(i));
            
            if( rule.at(i) == '0')
            {
                //INSERT CODE HERE
            }
            else if( rule.at(i) == '1')
            {
                //INSERT CODE HERE BALLS AND DICK
            }
        }
        return true;
    }
} //penis is my favourite

shared_ptr<node> BDD::makeBranch(string::iterator& iter, int Lvl)
{
    shared_ptr<node> curr = make_shared<node>(node(Lvl));
    if(iter != rule.end()-1)
    {
        //std::iter2 == iter;
        //iter2++;
        if(*iter == '0')
        {
            curr->setlow(*makeBranch(++iter, Lvl+1));
            //curr->sethigh(false);
        }
        if (*iter == '1')
        {
            curr->sethigh(*makeBranch(++iter, Lvl+1));
            //curr->setlow(false);
        }
    }
    else
    {
        if (*iter == '0')
        {
         //   curr->
        }
    }
    return curr;
    
}
#endif 