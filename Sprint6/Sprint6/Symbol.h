#pragma once

#include <string>
#include "Type.h"

using namespace std;

class Symbol
{
    public:
      string name;
      Type type;
      Symbol(string name, Type type) : name(name), type(type) {}
};