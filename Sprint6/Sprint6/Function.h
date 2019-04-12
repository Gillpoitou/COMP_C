#pragma once

#include <vector>
#include <string>

#include "Declaration.h"
#include "Statement.h"
#include "Expression.h"
#include "IR.h"
using namespace std;

class Function
{
    public:
      Function(Type rtype, string name, vector<ExpressionVar *> *params, vector<Declaration *> *declarations, vector<Statement *> *stats, StatementReturn *rstat) : rtype(rtype), name(name), params(params), declarations(declarations), statements(stats), rstat(rstat) {}
      string toString()
      {
            string result = "Function = { \n";
            result += "name : " + name + ", \n";
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

      void build_IR(CFG *);
      Type rtype;
      string name;
      vector<ExpressionVar *> *params;
      vector<Declaration *> *declarations;
      vector<Statement *> *statements;
      StatementReturn *rstat;
};
