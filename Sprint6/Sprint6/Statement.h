#pragma once

#include "string"
#include "Expression.h"
using namespace std;

class Expression;
class Block;
class BasicBlock;

class Statement
{
    public:
      virtual string build_IR(CFG *);
      virtual string toString();
};

class StatementAssignement : public Statement
{
    public:
      StatementAssignement(ExpressionVar *left, Expression *right) : left(left), right(right) {}
      ExpressionVar *left;
      Expression *right;
      virtual string build_IR(CFG *);
      virtual string toString();
};

class StatementFunction : public Statement
{
    public:
      StatementFunction(ExpressionCall *functionCalled) : functionCalled(functionCalled) {}
      ExpressionCall *functionCalled;
      virtual string build_IR(CFG *);
      virtual string toString();
};

class StatementIfElse : public Statement
{
    public:
      StatementIfElse(Block* block): condition(nullptr), block(block), elserule(nullptr) {}
      StatementIfElse(Expression * condition, Block* block, StatementIfElse * elserule) : condition(condition), block(block), elserule(elserule) {}
      Expression * condition;
      Block* block;
      StatementIfElse * elserule;

      virtual string build_IR(CFG *);
      virtual string toString();
};

class StatementWhile : public Statement
{
    public:
      StatementWhile(Block* block): condition(nullptr), block(block) {}
      StatementWhile(Expression * condition, Block* block) : condition(condition), block(block) {}
      Expression * condition;
      Block* block;

      virtual string build_IR(CFG *);
      virtual string toString();
};

class StatementReturn
{
    public:
      StatementReturn(Expression *expr) : value(expr) {}
      string toString();
      string build_IR(CFG *);
      Expression *value;
};
