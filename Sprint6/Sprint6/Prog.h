#pragma once

#include <vector>
#include <string>

#include "Function.h"
using namespace std;

class Prog
{
    public:
      map<string, Function *> *functions;

      Prog(map<string, Function *> *functions) : functions(functions) {}
      
      void build_ASM(ostream &o);

      string toString()
      {
            string result = "Prog = { \n";
            for (map<string, Function *>::iterator it = functions->begin(); it != functions->end(); ++it)
            {
                  result += ((Function *)it->second)->toString() + "\n";
            }

            return result;
      }  
};