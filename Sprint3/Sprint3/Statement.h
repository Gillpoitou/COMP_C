#pragma once
#include "string"
#include "Expression.h"
#include <map>
using namespace std;

class Expression;

class Statement
{
    public:
      Statement(ExpressionVar *left, Expression *right) : left(left), right(right) {}
      ExpressionVar *left;
      Expression *right;
      string toString();
};

class StatementReturn
{
    public:
      StatementReturn(Expression *expr) : value(expr) {}
      virtual void buildASM(ostream &o, map<string,int>* symbolTable);
      string toString();
      Expression *value;
};
