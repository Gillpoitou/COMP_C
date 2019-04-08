#pragma once

#include <vector>
#include "Declaration.h"
#include "Statement.h"

class Bloc
{
    public:
      Bloc(vector<Declaration *> *declarations, vector<Statement *> *statements, StatementReturn *rstat) : declarations(declarations), statements(statements), rstat(rstat) {}
      string toString()
      {
            string result = "Bloc = { \n";
            for (vector<Declaration *>::iterator it = declarations->begin(); it != declarations->end(); ++it)
            {
                  result += ((Declaration *)*it)->toString() + "\n";
            }
            for (vector<Statement *>::iterator it2 = statements->begin(); it2 != statements->end(); ++it2)
            {
                  result += ((Statement *)*it2)->toString() + "\n";
            }
            if (rstat)
            {
                  return result += "rstat : " + rstat->toString() + "}\n";
            }
            else
            {
                  return result += "}\n";
            }
      }
      string build_IR(CFG *);

      vector<Declaration *> *declarations;
      vector<Statement *> *statements;
      StatementReturn *rstat;
};