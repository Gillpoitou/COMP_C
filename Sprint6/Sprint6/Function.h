#pragma once

#include <vector>
#include <string>

#include "Expression.h"
#include "IR.h"
#include "Bloc.h"
using namespace std;

class Function
{
    public:
      Function(Type rtype, string name, vector<ExpressionVar *> *params, Bloc* bloc) : rtype(rtype), name(name), params(params), bloc(bloc) {}
      string toString()
      {
            string result = "Function = { \n";
            // result += "type : " + rtype + ", \n";
            result += "name : " + name + ", \n";
            // for (vector<ExpressionVar *>::iterator it = params->begin(); it != params->end(); ++it)
            // {
            //       result += ((ExpressionVar *)*it)->toString() + "\n";
            // }
            result += "bloc : " + bloc->toString() + "}\n";

            return result;
      }

      void build_IR(CFG *);
      Type rtype;
      string name;
      vector<ExpressionVar *> *params;
      Bloc *bloc;
};
