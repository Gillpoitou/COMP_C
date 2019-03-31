#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <string>
#include <sstream>
using namespace std;

class Expression
{
    public:
			virtual void buildASM(ostream &o, map<string,int>* symbolTable){}
      virtual string toString()
      {
            return "";
      };
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
};

class ExpressionBinary : public Expression
{
		public:
			Expression *right;
      Expression *left;
			
      ExpressionBinary(Expression *left, Expression *right) : right(right), left(left) {}
      virtual string toString() 
			{ 
					return "";
			};
			virtual void buildASM(ostream &o, map<string,int>* symbolTable){}
};

class ExpressionPlus : public ExpressionBinary
{
    public:
      ExpressionPlus(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionPlus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
			virtual void buildASM(ostream &o, map<string,int>* symbolTable);
};

class ExpressionMinus : public ExpressionBinary
{
    public:
      ExpressionMinus(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionMinus = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
};

class ExpressionMult : public ExpressionBinary
{
    public:
      ExpressionMult(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionMult = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
};

class ExpressionDiv : public ExpressionBinary
{
    public:
      ExpressionDiv(Expression *left, Expression *right): ExpressionBinary(left, right){}
      virtual string toString()
      {
            return "ExpressionDiv = { right : " + right->toString() + ", left : " + left->toString() + "\n";
      }
};

#endif
