#pragma once

#include <vector>
#include "Declaration.h"
#include "string"
#include "Statement.h"

using namespace std;

class Block
{
    public:
      Block(vector<Statement *> *statements, StatementReturn *rstat) : statements(statements), rstat(rstat) {}
      string toString()
      {
            string result = "Block = { \n";
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

      vector<Statement *> *statements;
      StatementReturn *rstat;
};