#include <string>
using namespace std;


class SymbAtt
{
    public:
        SymbAtt(string aName, string aType, string aRType) : name(aName) { }

        string name;
        string type;        //probably need to use the object Type
        string rtype;

}