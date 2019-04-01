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

string ExpressionDiv::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionMinus::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionMult::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionPar::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionPlus::build_IR(CFG* ir_cfg){
    return "";
}

string ExpressionVar::build_IR(CFG* ir_cfg){
    return name;
}
