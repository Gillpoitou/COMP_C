#include <vector>
#include <string>

#include "Declaration.h"
#include "Statement.h"
using namespace std;

class Funcdef
{
      //TODO change everything 
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

      vector<Declaration *> *declarations;
      vector<Statement *> *statements;
      StatementReturn *rstat;
};