#include "Declaration.h"
#include "IR.h"

string Declaration::build_IR(CFG * ir_cfg){

    ir_cfg->add_to_symbol_table(left->name, INT);

    if(right != nullptr){

        string var_name_right = right->build_IR(ir_cfg);
        string var_name_left = left->build_IR(ir_cfg);
        vector<string> params;
        params.push_back(var_name_left);
        params.push_back(var_name_right);
        ir_cfg->current_bb->add_IRInstr(IRInstr::Operation::wmem,INT,params);
        return var_name_right;
    }
    return "";
}
