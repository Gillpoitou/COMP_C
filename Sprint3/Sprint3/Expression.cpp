#include "Expression.h"
#include <iostream>
using namespace std;

void ExpressionPlus::buildASM(ostream &o, map<string,int>* symbolTable){
		// a + ?
		if(ExpressionVar * v_left = dynamic_cast<ExpressionVar*>(left)){
				int reg_off_left = symbolTable->find(v_left->name)->second;
				// a + b 
				if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){
						o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
						int reg_off_right = symbolTable->find(v_right->name)->second;
						o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
						o << "addl %edx, %eax" << endl;
				// a + 3 
				}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
						o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
						o << "addl $" << c_right->value << ", %eax" <<endl;
				// a + expr
				}else if(ExpressionBinary *p_right = dynamic_cast<ExpressionBinary*>(right)){
						// a + i op ?
						if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(p_right->left)){
								o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
								int reg_off_right = symbolTable->find(v_right->name)->second;
								o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){
										if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "addl %edx, %eax" << endl;
										}else{
												o << "addl %eax, %edx" << endl;
										}
								}else{
										o << "addl %eax, %edx" << endl;
								}
						// a + 3 op ?
						}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->left)){
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){ 
										if(ExpressionConst * p_right_c_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
												o << "addl $" << c_right->value << ", %eax" << endl;
										}else{
												o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
												o << "addl $" << c_right->value << ", %edx" << endl;
										}
								}else{
										o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
										o << "addl $" << c_right->value << ", %edx" << endl;
								}
						}
				}
		// 3 + ?
		}else if(ExpressionConst * c_left = dynamic_cast<ExpressionConst*>(left)){
				// 3 + a
				if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){
						int reg_off_right = symbolTable->find(v_right->name)->second;
						o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
						o << "addl $" << c_left->value << ", %eax" <<endl;
				// 3 + 4
				}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
						int add = c_left->value + c_right->value;
						o << "movl $" << add << ", %eax" << endl;
				// 3 + expr
				}else if(ExpressionBinary *p_right = dynamic_cast<ExpressionBinary*>(right)){
						// 3 + i op ?
						if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(p_right->left)){
								int reg_off_right = symbolTable->find(v_right->name)->second;
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){
										if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
												o << "addl $" << c_left->value << ", %eax" << endl;
										}else{
												o << "movl -" << reg_off_right << "(%rbp), %edx" << endl;
												o << "addl $" << c_left->value << ", %edx" << endl;
										}
								}else{
										o << "movl -" << reg_off_right << "(%rbp), %edx" << endl;
										o << "addl $" << c_left->value << ", %edx" << endl;
								}
						// 3 + 4 op ?
						}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->left)){ 
								int add = c_left->value + c_right->value;
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){
										if(ExpressionConst * e_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "movl $" << add << ", %eax" << endl;
										}else{
												o << "movl $" << add << ", %edx" << endl;
										}
								}else{
										o << "movl $" << add << ", %edx" << endl;
								}
						}
				}
		// expr + ?
		}else if(ExpressionBinary *p_left = dynamic_cast<ExpressionBinary*>(left)){
				// expr + a
				if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){
						cout << "expr + a" <<endl;
						p_left->right = new ExpressionPlus(p_left->right, v_right);
						p_left->buildASM(o, symbolTable);
						int reg_off_right = symbolTable->find(v_right->name)->second;
						o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
						o << "addl %edx, %eax" << endl;
				// expr + 3
				}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
						p_left->right = new ExpressionPlus(p_left->right, c_right);
						p_left->buildASM(o, symbolTable);
						o << "addl $" << c_right->value << ", %eax" << endl;
				// expr + expr 
				}else if(ExpressionBinary *p_right = dynamic_cast<ExpressionBinary*>(right)){
						cout << "expr + expr" <<endl;
						p_left->right = new ExpressionPlus(p_left->right, p_right);
						p_left->buildASM(o, symbolTable);
						// expr + a + expr
						if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(p_right->left)){
								int reg_off_right = symbolTable->find(v_right->name)->second;
								o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){
										if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "addl %edx, %eax" << endl;
										}else{
												o << "addl %eax, %edx" << endl;
										}
								}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->right)){
										o << "addl %edx, %eax" << endl;
								}else{
										o << "addl %eax, %edx" << endl;
								}
						// expr + 3 + expr
						}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(p_right->left)){
								if(ExpressionBinary * p_right_right = dynamic_cast<ExpressionBinary*>(p_right->right)){
										if(ExpressionConst * e_right = dynamic_cast<ExpressionConst*>(p_right_right->left)){
												o << "addl $" << c_right->value << ", %eax" << endl;
										}else{
												o << "movl $" << c_right->value << ", %edx" << endl;
												o << "addl %eax, %edx" << endl; 
										}
								}else if(ExpressionConst * e_right = dynamic_cast<ExpressionConst*>(p_right->right)){
										o << "addl $" << c_right->value << ", %eax" << endl;
								}else{
										o << "movl $" << c_right->value << ", %edx" << endl;
										o << "addl %eax, %edx" << endl; 
								}
						}		
				}
		}
}

