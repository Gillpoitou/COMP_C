#include <vector>
#include <string>

#include "Declaration.h"
#include "Statement.h"
#include "IR.h"
using namespace std;

class MainFunction
{
    public:
      MainFunction(vector<Declaration *> *declarations, vector<Statement *> *stats, StatementReturn *rstat) : declarations(declarations), statements(stats), rstat(rstat) {}
      string toString()
      {
            string result = "MainFunction = { \n";
            for (vector<Declaration *>::iterator it = declarations->begin(); it != declarations->end(); ++it)
            {
                  result += ((Declaration *)*it)->toString() + "\n";
            }
            for (vector<Statement *>::iterator it2 = statements->begin(); it2 != statements->end(); ++it2)
            {
                  result += ((Statement *)*it2)->toString() + "\n";
            }

            return result += "rstat : " + rstat->toString() + "}\n";
      }

      void build_IR(CFG*);
      vector<Declaration *> *declarations;
      vector<Statement *> *statements;
      StatementReturn *rstat;
      string name = "main";
};

