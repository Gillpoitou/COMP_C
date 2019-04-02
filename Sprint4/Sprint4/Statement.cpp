#include "Statement.h"
#include "Expression.h"
#include "IR.h"

string Statement::toString()
{
      return "Statement = { right : " + right->toString() + ", left : " + left->toString() + "\n";
}

string StatementReturn::toString()
{
      return "Return = { value : " + value->toString() + " }\n";
}

string Statement::build_IR(){
    string temp = right->build_IR(ir_cfg);
    string leftName = left->build_IR(ir_cfg);
    vector<string> params;
    params.push_back(temp);
    params.push_back(leftName);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::ret,INT,params); // PAS BON ATTENTION
}

string StatementReturn::build_IR(CFG* ir_cfg){
    string var_name_ret = value->build_IR(ir_cfg);
   vector<string> params;
   params.push_back(var_name_ret);
    ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::ret,INT,params);
    return "";
}
