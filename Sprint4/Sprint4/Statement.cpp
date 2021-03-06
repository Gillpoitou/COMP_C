#include "Statement.h"
#include "Expression.h"
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
