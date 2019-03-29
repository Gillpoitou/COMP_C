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
       
       }else if(ExpressionPlus *p_right = dynamic_cast<ExpressionPlus*>(right)){

             if(ExpressionVar * v_left = dynamic_cast<ExpressionVar*>(p_right->left)){
                int reg_off_left = symbolTable->find(v_left->name)->second;
                if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(p_right->right)){
                        o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
                        int reg_off_right = symbolTable->find(v_right->name)->second;
                        o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
                        o << "addl %edx, %eax" << endl;
                }else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->right)){
                    o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
                    o << "addl $" << c_right->value << ", %eax" <<endl;
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(p_right->right)){
                if(ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(p_right->left)){
                    int reg_off_right = symbolTable->find(v_right->name)->second;
                    o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
                    o << "addl $" << c_left->value << ", %eax" <<endl;
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else{
                ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(p_right->left);
                ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->right);
                int add = c_left->value + c_right->value;
                o << "movl $" << add << ", -" << reg_off << "(%rbp)" << endl;
                 
            }

        }else if(ExpressionMinus *m_right = dynamic_cast<ExpressionMinus*>(right)){
            if(ExpressionVar * v_left = dynamic_cast<ExpressionVar*>(m_right->left)){
                int reg_off_left = symbolTable->find(v_left->name)->second;
                if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                        o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
                        int reg_off_right = symbolTable->find(v_right->name)->second;
                        o << "subl -" << reg_off_right << "(%rbp), %eax" << endl;
                }else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right)){
                    o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
                    o << "subl $" << c_right->value << ", %eax" <<endl;
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                if(ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left)){
                    int reg_off_right = symbolTable->find(v_right->name)->second;
                    o << "movl $" << c_left->value << ", %eax" <<endl;
                    o << "subl -" << reg_off_right << "(%rbp), %eax" << endl;                
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else{
                ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left);
                ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right);
                int minus = c_left->value - c_right->value;
                o << "movl $" << minus << ", -" << reg_off << "(%rbp)" << endl;    
            }
        }else if(ExpressionMult *m_right = dynamic_cast<ExpressionMult*>(right)){
            if(ExpressionVar * v_left = dynamic_cast<ExpressionVar*>(m_right->left)){
                int reg_off_left = symbolTable->find(v_left->name)->second;
                if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                        o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
                        int reg_off_right = symbolTable->find(v_right->name)->second;
                        o << "imull -" << reg_off_right << "(%rbp), %eax" << endl;
                }else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right)){
                    //TODO;
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            
            
            }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                if(ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left)){
                    //TODO              
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else{
                ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left);
                ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right);
                int mult = c_left->value * c_right->value;
                o << "movl $" << mult << ", -" << reg_off << "(%rbp)" << endl;    
            }
        }else if(ExpressionMult *m_right = dynamic_cast<ExpressionMult*>(right)){
            if(ExpressionVar * v_left = dynamic_cast<ExpressionVar*>(m_right->left)){
                int reg_off_left = symbolTable->find(v_left->name)->second;
                if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                        o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
                        int reg_off_right = symbolTable->find(v_right->name)->second;
                        o << "cltd" << endl;
                        o << "idivl -" << reg_off_right << "(%rbp)" << endl;
                }else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right)){
                    //TODO;
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            
            
            }else if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(m_right->right)){
                if(ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left)){
                    //TODO              
                }
                o << "movl %eax, -" << reg_off << "(%rbp)" << endl;
            }else{
                ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(m_right->left);
                ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(m_right->right);
                int div = c_left->value / c_right->value;
                o << "movl $" << div << ", -" << reg_off << "(%rbp)" << endl;    
            }
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