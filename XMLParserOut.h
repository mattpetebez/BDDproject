#ifndef XMLPARSEROUT_H
#define XMLPARSEROUT_H

#include "BDDBuilder.h"
#include "RuleReturner.h"
#include <iostream>
class XMLParserOut
{
public:
    XMLParserOut();
    void setRules();
    void orderByIPDesc();
    ~XMLParserOut();

};

#endif // XMLPARSEROUT_H
