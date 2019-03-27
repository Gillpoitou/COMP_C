#include "string"
#include <iostream>
#include <map>
using namespace std;

class Expression;

class Statement {
      public:
      virtual string toString(){
            return "";
      };

      virtual void buildASM(ostream &o, map<string,int>* symbolTable){
            
      };
};

class StatementReturn : public Statement{
      public:
	    StatementReturn(Expression *expr): value(expr) {}
	    string toString();
      virtual void buildASM(ostream &o, const map<string,int>* symbolTable);
            Expression *value;
};
