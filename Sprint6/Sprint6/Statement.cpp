#include "Statement.h"
#include "Expression.h"
#include "Block.h"
#include "IR.h"

string Statement::toString()
{
      return "";
}
string StatementAssignement::toString()
{
      return "StatementAssignement = { right : " + right->toString() + ", left : " + left->toString() + "\n";
}

string StatementFunction::toString()
{
      return "StatementFunction = { function : " + functionCalled->toString() + "\n";
}

string StatementIfElse::toString()
{

      string result = "StatementIfElse = { ";

      
      if(condition != nullptr){
            result += "cond : " + condition->toString() + ", \n";
      }
      
      result += block->toString() + ", \n";

      if(elserule != nullptr){
            result += "elserule : " + elserule->toString() + ", \n";
      }

      result += "} \n";

      return result;
}

string StatementWhile::toString()
{

      string result = "StatementWhile = { ";

      
      if(condition != nullptr){
            result += "cond : " + condition->toString() + ", \n";
      }
      
      result += block->toString() + ", \n";

      result += "} \n";

      return result;
}

string StatementReturn::toString()
{
      return "Return = { value : " + value->toString() + " }\n";
}

string Statement::build_IR(CFG *ir_cfg)
{
      return "";
}

string StatementAssignement::build_IR(CFG *ir_cfg)
{
      string temp = right->build_IR(ir_cfg);
      string leftName = left->build_IR(ir_cfg);
      vector<string> params;
      params.push_back(leftName);
      params.push_back(temp);
      ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::wmem, INT, params);

      return leftName;
}

string StatementFunction::build_IR(CFG *ir_cfg)
{
      string var = ir_cfg->create_new_tempvar(INT);
      vector<string> params;
      params.push_back(functionCalled->calledFuncName);
      params.push_back(var);

      for (Expression *expr : *(functionCalled->func_params))
      {
            string par_var = expr->build_IR(ir_cfg);
            params.push_back(par_var);
      }
      ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::call, INT, params);
      return var;
}

string StatementReturn::build_IR(CFG *ir_cfg)
{
      string var_name_ret = value->build_IR(ir_cfg);
      vector<string> params;
      params.push_back(var_name_ret);
      ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::ret, INT, params);
      return "";
}

string StatementIfElse::build_IR(CFG *ir_cfg){

			BasicBlock* afterIfBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
      ir_cfg->add_bb(afterIfBB);
	  	afterIfBB->exit_true =  ir_cfg->current_bb->exit_true;
      afterIfBB->exit_false =  ir_cfg->current_bb->exit_false;

	  	BasicBlock* thenBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
      ir_cfg->add_bb(thenBB);
      thenBB->exit_true = afterIfBB;
      thenBB->exit_false = nullptr;

	  	ir_cfg->current_bb->exit_true = thenBB;
	  	ir_cfg->current_bb->exit_false = afterIfBB;

      BasicBlock* elseBB = nullptr;
      if(elserule != nullptr){
          	elseBB = new BasicBlock(ir_cfg, ir_cfg->new_BB_name());
          	ir_cfg->add_bb(elseBB);
						elseBB->exit_true = afterIfBB;
      			elseBB->exit_false = nullptr;
						ir_cfg->current_bb->exit_false = elseBB;
      }
      if(condition != nullptr){
  					string conditionVar = condition->build_IR(ir_cfg);
						vector<string> params;
      			params.push_back(conditionVar);
						ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params);
	  	}
      ir_cfg->current_bb = thenBB;
      block->build_IR(ir_cfg);

      if(elseBB != nullptr) {
            ir_cfg->current_bb = elseBB;
            elserule->build_IR(ir_cfg);
      }
      ir_cfg->current_bb = afterIfBB;

      return "";
}

string StatementWhile::build_IR(CFG *ir_cfg)
{
			BasicBlock* afterWhileBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(afterWhileBB);
			afterWhileBB->exit_false = ir_cfg->current_bb->exit_true;

      BasicBlock* conditionBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(conditionBB);

      ir_cfg->current_bb->exit_true = conditionBB;
      ir_cfg->current_bb = conditionBB;

      string conditionVar = condition->build_IR(ir_cfg);
			vector<string> params;
			params.push_back(conditionVar);
			ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::eq_if, INT, params);

      BasicBlock* loopBB = new BasicBlock(ir_cfg,ir_cfg->new_BB_name());
      ir_cfg->add_bb(loopBB);
      conditionBB->exit_true = loopBB;
      conditionBB->exit_false = afterWhileBB;
      loopBB->exit_true = conditionBB;

      ir_cfg->current_bb = loopBB;
      block->build_IR(ir_cfg);

      ir_cfg->current_bb = afterWhileBB;

      return "";
}
