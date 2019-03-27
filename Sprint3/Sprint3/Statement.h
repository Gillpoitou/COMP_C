#include "string"
#include "Expression.h"
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
      string toString();
      Expression *value;
};
