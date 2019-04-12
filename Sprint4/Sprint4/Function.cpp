#include "Function.h"

void Function::build_IR(CFG *ir_cfg)
{
  
      BasicBlock *first_bb = new BasicBlock(ir_cfg, this->name);

      ir_cfg->add_bb(first_bb);
      ir_cfg->current_bb = first_bb;

      for (ExpressionVar *exp : *params)
      {
            ir_cfg->add_to_symbol_table(exp->name, exp->type);
      }

      for (Declaration *decl : *declarations)
      {
            decl->build_IR(ir_cfg);
      }

      for (Statement *statm : *statements)
      {
            statm->build_IR(ir_cfg);
      }

      if (rstat)
      {
            rstat->build_IR(ir_cfg);
      }
}
