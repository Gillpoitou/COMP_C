#include "Expression.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;

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

            void buildASM(ostream &o, map<string,int>* symbolTable, int* lastOffset);


            ExpressionVar * left;
            Expression * right;
};
