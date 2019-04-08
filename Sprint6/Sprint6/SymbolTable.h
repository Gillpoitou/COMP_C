#pragma once
#include <stack>
#include <map>

#include "Symbol.h"
#include "Type.h"

using namespace std;

typedef map<string, Symbol *> Stable;

class SymbolTable
{
    public:
      stack<Stable * > * symbolTables;
      Stable * currentTable;

      SymbolTable();
      bool addVar(string name, Type type);
      bool addFunction(string name, Type type);
      void functionEnd();
      Symbol* getSymbol(string name);

      void print();
};