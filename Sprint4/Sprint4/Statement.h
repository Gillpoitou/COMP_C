#include "string"
#include "Expression.h"
using namespace std;

class Expression;
class BasicBlock;

class Statement
{
    public:
      Statement(ExpressionVar *left, Expression *right) : left(left), right(right) {}
      string build_IR(CFG*);
      ExpressionVar *left;
      Expression *right;
      string toString();
};

class StatementReturn
{
    public:
      StatementReturn(Expression *expr) : value(expr) {}
      string toString();
      string build_IR(CFG*);
      Expression *value;
};
