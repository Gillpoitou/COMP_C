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

    /*string leftName = this->left->buildIR(ir_cfg);
      int reg_off_left = symbolTable->find(leftName)->second;
      string rightName = this->right->buildASM(o, symbolTable, lastOffset);
      int reg_off_right = symbolTable->find(rightName)->second;

      o << "movl -" << reg_off_left << "(%rbp), %eax" << endl;
      o << "imull -" << reg_off_right << "(%rbp), %eax" << endl;

      *lastOffset = *lastOffset + 4;
      string name = "mult" + to_string(*lastOffset);
      pair<string, int> var(name, *lastOffset);
      symbolTable->insert(var);

      o << "movl %eax, -" << *lastOffset << "(%rbp)" << endl;

      return name;*/
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
