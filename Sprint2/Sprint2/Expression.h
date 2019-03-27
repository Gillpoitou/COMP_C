#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Expression
{
    public:
      virtual string toString(){
            return "";
      };

      virtual void buildASM(ostream &o){
            
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

      virtual void buildASM(ostream &o);

      int value;
};

class ExpressionVar : public Expression
{
    public:
      ExpressionVar(string name) : name(name), value(nullptr) {}
      ExpressionVar(string name, ExpressionVar *val) : name(name)
      {
            this->value = new ExpressionConst(val->getValue()->value);
      }
      ExpressionVar(string name, ExpressionConst *value) : name(name), value(value) {}
      ExpressionConst * getValue()
      {
            return value;
      }

      virtual string toString()
      {
            if (value != nullptr)
            {
                  return "ExpressionVar = { name : " + name + " , value : " + value->toString() + " }\n";
            }
            else
            {
                  return "ExpressionVar = { name : " + name + " , value : null } \n";
            }
      }

      virtual void buildASM(ostream &o);

      string name;
      ExpressionConst *value;
};