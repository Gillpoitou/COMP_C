#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <sstream>
using namespace std;
class CFG;

class Expression
{
    public:
      virtual string toString()
      {
            return "";
      };
      virtual string build_IR(CFG*){
            return "";
      }
};

class ExpressionConst : public Expression
{
    public:
      ExpressionConst(int value) : value(value) {}

      virtual string toString()
      {
            ostringstream ss;
            ss << value;
            return "ExpressionConst = { value : " + ss.str() + " } \n";
      }
      string build_IR(CFG*);
      int value;
};

class ExpressionVar : public Expression
{
    public:
      ExpressionVar(string name) : name(name) {}

      virtual string toString()
      {
            return "ExpressionVar = { name : " + name + "}\n";
      }
      string build_IR(CFG*);
      string name;
};

class ExpressionPar : public Expression
{
    public:
      Expression *value;
      ExpressionPar(Expression *value) : value(value) {}
      virtual string toString()
      {
            return "ExpressionPar = { value : " + value->toString() + "}\n";
      }
      string build_IR(CFG*);
};

class ExpressionBinary : public Expression
{
    public:
      Expression *right;
      Expression *left;

      ExpressionBinary(Expression *left, Expression *right) : right(right), left(left) {}
      virtual string toString() = 0;
      string build_IR(CFG*);
};

class ExpressionPlus : public ExpressionBinary
{
    public:
      ExpressionPlus(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionPlus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG*);
};

class ExpressionMinus : public ExpressionBinary
{
    public:
      ExpressionMinus(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionMinus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG*);
};

class ExpressionMult : public ExpressionBinary
{
    public:
      ExpressionMult(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionMult = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG*);
};

class ExpressionDiv : public ExpressionBinary
{
    public:
      ExpressionDiv(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionDiv = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
      string build_IR(CFG*);
};

#endif