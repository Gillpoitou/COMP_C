#include <string.h>
using namespace std;

class Expression
{
      //     public:
      //       virtual Expression(Expression &expr);
};

class ExpressionVar : public Expression
{
    public:
      ExpressionVar(string name) : name(name), value(nullptr) {}
      ExpressionVar(string name, ExpressionVar *val) : name(name)
      {
            this->value = new ExpressionConst(val->getValue().value);
      }
      ExpressionVar(string name, ExpressionConst *value) : name(name), value(value) {}
      ExpressionConst * getValue()
      {
            return value;
      }

      string name;
      ExpressionConst *value;      
};

class ExpressionConst : public Expression
{
    public:
      ExpressionConst(int value) : value(value) {}
      int value;

    protected:
};
