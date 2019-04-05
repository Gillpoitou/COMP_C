#pragma once

#include <string>
#include "Type.h"

using namespace std;


class SymbAtt
{
    public:
        SymbAtt(string name, Type type, Type rtype) : name(name), type(type), rtype(rtype) { }

        string name;
        Type type;
        Type rtype;

};