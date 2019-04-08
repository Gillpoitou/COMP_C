#include "Function.h"

void Function::build_IR(CFG *ir_cfg)
{
      //cout << this->toString() << endl;

      //cout << "2.1" << endl;
      BasicBlock *first_bb = new BasicBlock(ir_cfg, this->name);
      //cout << "2.2" << endl;

      ir_cfg->add_bb(first_bb);
      ir_cfg->current_bb = first_bb;
      //cout << "2.3" << endl;

      for (ExpressionVar *exp : *params)
      {
            //cout << "2.3 bis" << endl;
            ir_cfg->add_to_symbol_table(exp->name, exp->type);
      }

      //cout << "2.4" << endl;

      for (Declaration *decl : *declarations)
      {
            decl->build_IR(ir_cfg);
      }
      //cout << "2.5" << endl;

      for (Statement *statm : *statements)
      {
			//cout << "2.5 bis" << endl;
            statm->build_IR(ir_cfg);
      }
      //cout << "2.6" << endl;

      if (rstat)
      {
            rstat->build_IR(ir_cfg);
      }
}
