#include <vector>
#include <string>

#include "Declaration.h"
using namespace std;

class Function
{
    public:
      Function(vector<Declaration *> *declarations) : declarations(declarations) {}
      string toString()
      {
            string result = "Function = { \n";
            for (vector<Declaration *>::iterator it = declarations->begin(); it != declarations->end(); ++it)
            {
                  result += ((Declaration *)*it)->toString() + "\n";
            }

            return result += "}\n";
      }

      vector<Declaration *> *declarations;
};