#include "Expression.h"

using namespace std;

class Declaration
{
      public:
            Declaration(ExpressionVar * left) : left(left), right(nullptr) {}
            Declaration(ExpressionVar * left, Expression * right) : left(left), right(right){}
            ExpressionVar * left;
            Expression * right;
};