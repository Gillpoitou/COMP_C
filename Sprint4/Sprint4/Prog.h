#include <vector>
#include <string>

#include "Function.h"
using namespace std;

class Prog
{
    public:
      Prog();
      string toString()
      {
            string result = "Prog = { \n";
            for (map<string,Function *>::iterator it = functions.begin(); it != functions.end(); ++it)
            {
                  result += ((Function *) it->second)->toString() + "\n";
            }

           return result;
      }

      map<string, Function *> functions;
  
};