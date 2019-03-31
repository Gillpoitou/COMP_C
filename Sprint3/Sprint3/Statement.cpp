#include "Statement.h"
#include "Expression.h"
#include <iostream>

using namespace std;

string Statement::toString()
{
      return "Statement = { right : " + right->toString() + ", left : " + left->toString() + "\n";
}

string StatementReturn::toString()
{
      return "Return = { value : " + value->toString() + " }\n";
}

void Statement::buildASM(ostream &o, map<string,int>* symbolTable){
    if(right != nullptr){
        int reg_off = symbolTable->find(left->name)->second;

        if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
   
           o << "movl $" << c_right->value << ", -" << reg_off << "(%rbp)" << endl;

        }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){

           int reg_off_right = symbolTable->find(v_right->name)->second;
           o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
           o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
       
        }else if(Expression *p_right = dynamic_cast<Expression*>(right)){
			right->buildASM(o, symbolTable);
			o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
		}
    }
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
