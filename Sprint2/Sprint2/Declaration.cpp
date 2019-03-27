#include "Declaration.h"

void Declaration::buildASM(ostream &o, map<string,int>* symbolTable, int* lastOffset){
    *lastOffset = *lastOffset + 4;
    pair<string,int> var(left->name,*lastOffset);
    symbolTable->insert(var);

    if(right != nullptr){
        int reg_off = symbolTable->find(left->name)->second;

       if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
   
           o << "movl $" << c_right->value << ", -" << reg_off << "(%rbp)" << endl;

       }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){

           int reg_off_right = symbolTable->find(v_right->name)->second;
           o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
           o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
       }
    }
}