#include <vector>
#include <string>

#include "Funcdef.h"
using namespace std;

class Prog
{
    public:
      Prog(vector<Funcdef *> *aFuncdefs, MainFunction *aMainfunc) : funcdefs(aFuncdefs), mainfunc(aMainfunc) {}
      string toString()
      {
            string result = "Prog = { \n";
            for (vector<Funcdef *>::iterator it = funcdefs->begin(); it != funcdefs->end(); ++it)
            {
                  result += ((Funcdefs *)*it)->toString() + "\n";
            }

            return result += mainfunc->toString() + "}\n";
      }

      vector<Funcdef *> *funcdefs;
      MainFunction *mainfunc;
};