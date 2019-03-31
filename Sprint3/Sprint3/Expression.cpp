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
				}else if(ExpressionBinary *expr = dynamic_cast<ExpressionBinary*>(right)){
						// a + i op ?
						if(ExpressionVar * expr_v_left = dynamic_cast<ExpressionVar*>(expr->left)){
								o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
								int reg_off_right = symbolTable->find(expr_v_left->name)->second;
								o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
								if(ExpressionBinary * expr_expr_right = dynamic_cast<ExpressionBinary*>(expr->right)){
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr_expr_right->left)){
												o << "addl %edx, %eax" << endl;
										}else{
												o << "addl %eax, %edx" << endl;
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr->right)){
										o << "addl %edx, %eax" << endl;
								}else{
										o << "addl %eax, %edx" << endl;
								}
						// a + 3 op ?
						}else if(ExpressionConst * expr_c_left = dynamic_cast<ExpressionConst*>(expr->left)){
								if(ExpressionBinary * expr_expr_right = dynamic_cast<ExpressionBinary*>(expr->right)){ 
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr_expr_right->left)){
												o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
												o << "addl $" << expr_c_left->value << ", %eax" << endl;
										}else{
												o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
												o << "addl $" << expr_c_left->value << ", %edx" << endl;
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr->right)){
												o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
												o << "addl $" << expr_c_left->value << ", %eax" << endl;
								}else{
										o << "movl -" << reg_off_left << "(%rbp), %edx" << endl;
										o << "addl $" << expr_c_left->value << ", %edx" << endl;
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
				}else if(ExpressionBinary *expr = dynamic_cast<ExpressionBinary*>(right)){
						// 3 + i op ?
						if(ExpressionVar * expr_v_right = dynamic_cast<ExpressionVar*>(expr->left)){
								int reg_off_right = symbolTable->find(expr_v_right->name)->second;
								if(ExpressionBinary * expr_expr_right = dynamic_cast<ExpressionBinary*>(expr->right)){
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr_expr_right->left)){
												o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
												o << "addl $" << c_left->value << ", %eax" << endl;
										}else{
												o << "movl -" << reg_off_right << "(%rbp), %edx" << endl;
												o << "addl $" << c_left->value << ", %edx" << endl;
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr->right)){
										o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
										o << "addl $" << c_left->value << ", %eax" << endl;
								}else{
										o << "movl -" << reg_off_right << "(%rbp), %edx" << endl;
										o << "addl $" << c_left->value << ", %edx" << endl;
								}
						// 3 + 4 op ?
						}else if(ExpressionConst * expr_c_left = dynamic_cast<ExpressionConst*>(expr->left)){ 
								int add = c_left->value + expr_c_left->value;
								if(ExpressionBinary * expr_expr_right = dynamic_cast<ExpressionBinary*>(expr->right)){
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr_expr_right->left)){
												o << "movl $" << add << ", %eax" << endl;
										}else{
												o << "movl $" << add << ", %edx" << endl;
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr->right)){
										o << "movl $" << add << ", %eax" << endl;
								}else{
										o << "movl $" << add << ", %edx" << endl;
								}
						}
				}
		// expr + ?
		}else if(ExpressionBinary *expr = dynamic_cast<ExpressionBinary*>(left)){
				// expr + a
				if(ExpressionVar * v_right = dynamic_cast<ExpressionVar*>(right)){
						expr->right = new ExpressionPlus(expr->right, v_right);
						expr->buildASM(o, symbolTable);
						int reg_off_right = symbolTable->find(v_right->name)->second;
						o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
						o << "addl %edx, %eax" << endl;
				// expr + 3
				}else if(ExpressionConst * c_right = dynamic_cast<ExpressionConst*>(right)){
						expr->right = new ExpressionPlus(expr->right, c_right);
						expr->buildASM(o, symbolTable);
						o << "addl $" << c_right->value << ", %eax" << endl;
				// expr + expr1
				}else if(ExpressionBinary *expr1 = dynamic_cast<ExpressionBinary*>(right)){
						expr->right = new ExpressionPlus(expr->right, expr1);
						expr->buildASM(o, symbolTable);
						// expr + a + expr2
						if(ExpressionVar * expr1_v_left = dynamic_cast<ExpressionVar*>(expr1->left)){
								int reg_off_right = symbolTable->find(expr1_v_left->name)->second;
								o << "movl -" << reg_off_right << "(%rbp), %eax" << endl;
								if(ExpressionBinary * expr2 = dynamic_cast<ExpressionBinary*>(expr1->right)){
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr2->left)){
												o << "addl %edx, %eax" << endl;
										}else{
												o << "addl %eax, %edx" << endl;
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr1->right)){
										o << "addl %edx, %eax" << endl;
								}else{
										o << "addl %eax, %edx" << endl;
								}
						// expr + 3 + expr2
						}else if(ExpressionConst * expr1_c_left = dynamic_cast<ExpressionConst*>(expr1->left)){
								if(ExpressionBinary * expr2 = dynamic_cast<ExpressionBinary*>(expr1->right)){
										if(ExpressionConst * c = dynamic_cast<ExpressionConst*>(expr2->left)){
												o << "addl $" << expr1_c_left->value << ", %eax" << endl;
										}else{
												o << "movl $" << expr1_c_left->value << ", %edx" << endl;
												o << "addl %eax, %edx" << endl; 
										}
								}else if(ExpressionConst * c_expr2 = dynamic_cast<ExpressionConst*>(expr1->right)){
										o << "addl $" << expr1_c_left->value << ", %eax" << endl;
								}else{
										o << "movl $" << expr1_c_left->value << ", %edx" << endl;
										o << "addl %eax, %edx" << endl; 
								}
						}		
				}
		}
}

