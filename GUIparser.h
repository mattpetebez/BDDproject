#ifndef GUIPARSER_H
#define GUIPARSER_H

#include <iostream>
#include <vector>

#include "binDecConverter.h"

class GUIparser
{
public:
    GUIparser();
    ~GUIparser();
private:
    string ip;
    string prot;
    string srcportstart;
    string srcportend;
    string direction;
    string action;
    string destportstart;
    string destportend;
    
    binDecConverter _converter;

};

#endif // GUIPARSER_H
