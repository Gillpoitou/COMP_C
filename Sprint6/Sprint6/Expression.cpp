#include "Expression.h"
#include "IR.h"

string ExpressionBinary::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionConst::build_IR(CFG* ir_cfg){
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string> params;
    params.push_back(var);
    params.push_back(to_string(this->value));
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, INT, params);
    return var;
}

string ExpressionUnaryMinus::build_IR(CFG* ir_cfg){
    string valueName = this->value->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string>params;
    params.push_back(var);
    params.push_back(valueName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::neg, INT, params);
    return var;
}

string ExpressionMinus::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::sub, INT, params);
    return var;
}

string ExpressionMult::build_IR(CFG* ir_cfg){

    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::mul, INT, params);

    return var;
}

string ExpressionPar::build_IR(CFG* ir_cfg){
    return this->value->build_IR(ir_cfg);
}

string ExpressionPlus::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::add, INT, params);
    return var;
}

string ExpressionVar::build_IR(CFG* ir_cfg){
    return name;
}

string ExpressionCall::build_IR(CFG* ir_cfg){

    string var = ir_cfg->create_new_tempvar(INT);
    vector<string> params;
    params.push_back(calledFuncName);
    params.push_back(var);

    for(Expression* expr : *func_params){
       string par_var = expr->build_IR(ir_cfg);
       params.push_back(par_var);
    }
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::call, INT, params);
    return var;
}

string ExpressionCompEq::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
	vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_eq, INT, params);
    return var;
}

string ExpressionCompDif::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	string var = ir_cfg->create_new_tempvar(INT);
	vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_neq, INT, params);
    return var;
}

string ExpressionCompSup::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	string var = ir_cfg->create_new_tempvar(INT);
	vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_lt, INT, params);
    return var;
}

string ExpressionCompInf::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	string var = ir_cfg->create_new_tempvar(INT);
	vector<string> params;
    params.push_back(var);
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_gt, INT, params);
    return var;
}

string ExpressionUnaryNo::build_IR(CFG* ir_cfg){
    string valueName = this->value->build_IR(ir_cfg);
    string var = ir_cfg->create_new_tempvar(INT);
    vector<string>params;
    params.push_back(var);
    params.push_back(valueName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::no, INT, params);
    return var;
}

string ExpressionLogAnd::build_IR(CFG* ir_cfg){

			string leftBoolExpr = this->left->build_IR(ir_cfg);
			string rightBoolExpr = this->right->build_IR(ir_cfg);
			string var = ir_cfg->create_new_tempvar(INT);

			BasicBlock* afterConditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(afterConditionBB);
      afterConditionBB->exit_true = ir_cfg->current_bb->exit_true;
      afterConditionBB->exit_false = ir_cfg->current_bb->exit_false;

			BasicBlock* trueBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(trueBB);
      trueBB->exit_true = afterConditionBB;
      trueBB->exit_false = nullptr;

			BasicBlock* falseBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(falseBB);
      falseBB->exit_true = afterConditionBB;
      falseBB->exit_false = nullptr;

			BasicBlock* secConditionBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
			ir_cfg->add_bb(secConditionBB);
			secConditionBB->exit_true = trueBB;
      secConditionBB->exit_false = falseBB;	

			ir_cfg->current_bb->exit_true = secConditionBB;
			ir_cfg->current_bb->exit_false = falseBB;

			vector<string>params1;
			params1.push_back(leftBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params1);

			ir_cfg->current_bb = secConditionBB;
			vector<string>params2;
			params2.push_back(rightBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params2);

			vector<string>params3;
			params3.push_back(var);
			ir_cfg->current_bb = trueBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_1, INT, params3);
			ir_cfg->current_bb = falseBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_0, INT, params3);

			ir_cfg->current_bb = afterConditionBB;
			return var;
}

string ExpressionLogOr::build_IR(CFG* ir_cfg){

	    string leftBoolExpr = this->left->build_IR(ir_cfg);
			string rightBoolExpr = this->right->build_IR(ir_cfg);
			string var = ir_cfg->create_new_tempvar(INT);

			BasicBlock* afterConditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(afterConditionBB);
      afterConditionBB->exit_true = ir_cfg->current_bb->exit_true;
      afterConditionBB->exit_false = ir_cfg->current_bb->exit_false;

			BasicBlock* trueBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(trueBB);
      trueBB->exit_true = afterConditionBB;
      trueBB->exit_false = nullptr;

			BasicBlock* falseBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(falseBB);
      falseBB->exit_true = afterConditionBB;
      falseBB->exit_false = nullptr;

			BasicBlock* secConditionBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
			ir_cfg->add_bb(secConditionBB);
			secConditionBB->exit_true = trueBB;
      secConditionBB->exit_false = falseBB;	

			ir_cfg->current_bb->exit_true = trueBB;
			ir_cfg->current_bb->exit_false = secConditionBB;

			vector<string>params1;
			params1.push_back(leftBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params1);

			ir_cfg->current_bb = secConditionBB;
			vector<string>params2;
			params2.push_back(rightBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params2);

			vector<string>params3;
			params3.push_back(var);
			ir_cfg->current_bb = trueBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_1, INT, params3);
			ir_cfg->current_bb = falseBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_0, INT, params3);

			ir_cfg->current_bb = afterConditionBB;
			return var;
}

string ExpressionLogXor::build_IR(CFG* ir_cfg){
			string leftBoolExpr = this->left->build_IR(ir_cfg);
			string rightBoolExpr = this->right->build_IR(ir_cfg);
			string var = ir_cfg->create_new_tempvar(INT);

			BasicBlock* afterConditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(afterConditionBB);
      afterConditionBB->exit_true = ir_cfg->current_bb->exit_true;
      afterConditionBB->exit_false = ir_cfg->current_bb->exit_false;

			BasicBlock* trueBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(trueBB);
      trueBB->exit_true = afterConditionBB;
      trueBB->exit_false = nullptr;

			BasicBlock* falseBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(falseBB);
      falseBB->exit_true = afterConditionBB;
      falseBB->exit_false = nullptr;

			BasicBlock* afterTrueBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
			ir_cfg->add_bb(afterTrueBB);
			afterTrueBB->exit_true = falseBB;
      afterTrueBB->exit_false = trueBB;	

			BasicBlock* afterFalseBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
			ir_cfg->add_bb(afterFalseBB);
			afterFalseBB->exit_true = trueBB;
      afterFalseBB->exit_false = falseBB;

			ir_cfg->current_bb->exit_true = afterTrueBB;
			ir_cfg->current_bb->exit_false = afterFalseBB;

			vector<string>params1;
			params1.push_back(leftBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params1);

			ir_cfg->current_bb = afterTrueBB;
			vector<string>params2;
			params2.push_back(rightBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params2);

			ir_cfg->current_bb = afterFalseBB;
			vector<string>params2bis;
			params2bis.push_back(rightBoolExpr);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params2bis);

			vector<string>params3;
			params3.push_back(var);
			ir_cfg->current_bb = trueBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_1, INT, params3);
			ir_cfg->current_bb = falseBB;
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::bool_0, INT, params3);

			ir_cfg->current_bb = afterConditionBB;
      return var;
}
