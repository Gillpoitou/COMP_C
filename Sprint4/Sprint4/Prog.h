#pragma once

#include <vector>
#include <string>

#include "Function.h"
using namespace std;

class Prog
{
    public:
      Prog(map<string,Function *> *functions) :  functions(functions){}
      string toString()
      {
            string result = "Prog = { \n";
            for (map<string,Function *>::iterator it = functions->begin(); it != functions->end(); ++it)
            {
                  result += ((Function *) it->second)->toString() + "\n";
            }

           return result;
      }
      void build_ASM(ostream& o);

      map<string, Function *> *functions;
  
};