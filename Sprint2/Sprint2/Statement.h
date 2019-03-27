#include "string"
#include <iostream>
using namespace std;

class Expression;

class Statement {
      public:
      virtual string toString(){
            return "";
      };

      virtual void buildASM(ostream &o){
            
      };
};

class StatementReturn : public Statement{
      public:
	    StatementReturn(Expression *expr): value(expr) {}
	    string toString();
            Expression *value;
};
