#include "string"
#include "Expression.h"
#include "Bloc.h"
using namespace std;

class Expression;
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
      StatementIfElse(Expression * condition, Bloc* bloc, StatementIfElse * elserule) : condition(condition), bloc(bloc), elserule(elserule) {}
      Expression * condition;
      Bloc* bloc;
      StatementIfElse * elserule;

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
