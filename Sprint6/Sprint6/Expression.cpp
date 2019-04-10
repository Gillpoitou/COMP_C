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
	vector<string> params;
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_eq, INT, params);
    return "";
}

string ExpressionCompDif::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	vector<string> params;
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_neq, INT, params);
    return "";
}

string ExpressionCompSup::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	vector<string> params;
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_lt, INT, params);
    return "";
}

string ExpressionCompInf::build_IR(CFG* ir_cfg){
    string leftName = this->left->build_IR(ir_cfg);
    string rightName = this->right->build_IR(ir_cfg);
	vector<string> params;
    params.push_back(leftName);
    params.push_back(rightName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::cmp_gt, INT, params);
    return "";
}

string ExpressionUnaryNo::build_IR(CFG* ir_cfg){
    string valueName = this->value->build_IR(ir_cfg);
    vector<string>params;
    params.push_back(valueName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::no, INT, params);
    return "";
}

string ExpressionLogAnd::build_IR(CFG* ir_cfg){
      
      left->build_IR(ir_cfg);
      BasicBlock* rightConditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(rightConditionBB);
      rightConditionBB->exit_true = ir_cfg->current_bb->exit_true;
      rightConditionBB->exit_false = ir_cfg->current_bb->exit_false;
      ir_cfg->current_bb->exit_true = rightConditionBB;
      ir_cfg->current_bb = rightConditionBB;   
      right->build_IR(ir_cfg); 
      return "";
}

string ExpressionLogOr::build_IR(CFG* ir_cfg){

	  left->build_IR(ir_cfg);
      BasicBlock* rightConditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(rightConditionBB);
      rightConditionBB->exit_true = ir_cfg->current_bb->exit_true;
      rightConditionBB->exit_false = ir_cfg->current_bb->exit_false;
      ir_cfg->current_bb->exit_false = rightConditionBB;
      ir_cfg->current_bb = rightConditionBB;   
      right->build_IR(ir_cfg); 
      return "";
}

string ExpressionLogXor::build_IR(CFG* ir_cfg){
      return "";
}
