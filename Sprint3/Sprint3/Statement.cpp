#include "Statement.h"
#include "Expression.h"

string Statement::toString()
{
      return "Statement = { right : " + right->toString() + ", left : " + left->toString() + "\n";
}

string StatementReturn::toString()
{
      return "Return = { value : " + value->toString() + " }\n";
}

void StatementReturn::buildASM(ostream &o, map<string,int>* symbolTable){

	if(value != nullptr){

       if(ExpressionConst * c_value = dynamic_cast<ExpressionConst*>(value)){
   
           o << "movl $" << c_value->value << ", %eax" << endl;

       }else if(ExpressionVar * v_value = dynamic_cast<ExpressionVar*>(value)){

           int reg_off_value = symbolTable->find(v_value->name)->second;
           o << "movl -" << reg_off_value << "(%rbp), %eax" << endl;
       }
    }
}