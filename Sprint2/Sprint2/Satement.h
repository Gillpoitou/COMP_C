using namespace std;

class Expression;

class Statement {
      public:
      virtual string toString(){
            return "";
      };
};

class StatementReturn : public Statement{
      public:
	    StatementReturn(Expression *expr): value(expr) {}
	    string toString(){
            	return "Return = { value : " + value->toString() + " }\n";
            }
            Expression *value;
};
