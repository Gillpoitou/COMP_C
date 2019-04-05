#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <sstream>
#include <vector>
#include "Type.h"

using namespace std;
class CFG;

class Expression
{
    public:
      Type type;
      Expression() {}
      Expression(Type type) : type(type) {}
      virtual string toString()
      {
            return "";
      };
      virtual string build_IR(CFG *)
      {
            return "";
      }
};

class ExpressionConst : public Expression
{
    public:
      ExpressionConst(Type type, int value) : Expression(type), value(value) {}

      virtual string toString()
      {
            ostringstream ss;
            ss << value;
            return "ExpressionConst = { value : " + ss.str() + " } \n";
      }
      string build_IR(CFG *);
      int value;
};

class ExpressionVar : public Expression
{
    public:
      ExpressionVar(string name) : name(name) {}
      ExpressionVar(Type type, string name) : Expression(type), name(name) {}

      virtual string toString()
      {
            return "ExpressionVar = { name : " + name + "}\n";
      }
      string build_IR(CFG *);
      string name;
};

class ExpressionPar : public Expression
{
    public:
      Expression *value;
      ExpressionPar(Type type, Expression *value) : Expression(type), value(value) {}
      virtual string toString()
      {
            return "ExpressionPar = { value : " + value->toString() + "}\n";
      }
      string build_IR(CFG *);
};

class ExpressionCall : public Expression
{
    public:

      ExpressionCall(Type type, string calledFuncName, vector<Expression*> *func_params) : Expression(type), calledFuncName(calledFuncName), func_params(func_params) {}
      string calledFuncName;
      vector<Expression*> *func_params;
      virtual string toString()
      {
            string result  = "ExpressionCall = { calledFuncName : " + calledFuncName + ", \n params : ";
            for (vector<Expression *>::iterator it = func_params->begin(); it != func_params->end(); ++it)
            {
                  result += ((Expression *)*it)->toString() + "\n";
            }
            return result;
      }
      string build_IR(CFG *);
};

class ExpressionBinary : public Expression
{
    public:
      Expression *right;
      Expression *left;

      ExpressionBinary(Type type, Expression *left, Expression *right) : Expression(type), right(right), left(left) {}
      virtual string toString() = 0;
      string build_IR(CFG *);
};

class ExpressionPlus : public ExpressionBinary
{
    public:
      ExpressionPlus(Type type, Expression *left, Expression *right) : ExpressionBinary(type, left, right) {}
      virtual string toString()
      {
            return "ExpressionPlus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG *);
};

class ExpressionMinus : public ExpressionBinary
{
    public:
      ExpressionMinus(Type type, Expression *left, Expression *right) : ExpressionBinary(type, left, right) {}
      virtual string toString()
      {
            return "ExpressionMinus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG *);
};

class ExpressionMult : public ExpressionBinary
{
    public:
      ExpressionMult(Type type, Expression *left, Expression *right) : ExpressionBinary(type, left, right) {}
      virtual string toString()
      {
            return "ExpressionMult = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG *);
};

#endif
