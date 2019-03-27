#include <vector>
#include <string>

#include "Declaration.h"
#include "Statement.h"
using namespace std;

class Function
{
    public:
      Function(vector<Declaration *> *declarations, vector<Statement *> *stats) : declarations(declarations), statements(stats) {}
      string toString()
      {
            string result = "Function = { \n";
            for (vector<Declaration *>::iterator it = declarations->begin(); it != declarations->end(); ++it)
            {
                  result += ((Declaration *)*it)->toString() + "\n";
            }
	    for (vector<Statement *>::iterator it2 = statements->begin(); it2 != statements->end(); ++it2)
            {
                  result += ((Statement *)*it2)->toString() + "\n";
            }

            return result += "}\n";
      }
      void buildASM(&ostream o){

      }

      vector<Declaration *> *declarations;
      vector<Statement *> *statements;
};
