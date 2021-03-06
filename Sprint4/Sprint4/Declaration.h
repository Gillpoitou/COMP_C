#include "Expression.h"
#include <string>

using namespace std;
class CFG;

class Declaration
{
      public:
            Declaration(ExpressionVar * left) : left(left), right(nullptr) {}
            Declaration(ExpressionVar * left, Expression * right) : left(left), right(right){}

            string toString(){
                  if(this->right){
                        return "Declaration = { left : " + left->toString() + " , right : " + right->toString() + " }\n";
                  } else {
                        return "Declaration = { left : " + left->toString() + " , right : null } \n";
                  }
            }

            string build_IR(CFG *);
            ExpressionVar * left;
            Expression * right;
};
