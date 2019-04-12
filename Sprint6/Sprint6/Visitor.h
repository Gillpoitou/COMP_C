#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "antlr4-runtime.h"
#include "Grammar4BaseVisitor.h"
#include "Function.h"
#include "Prog.h"
#include "Type.h"
#include "SymbolTable.h"
#include "Block.h"

using namespace std;
class Visitor : public Grammar4BaseVisitor
{
    public:
      Visitor(bool staticAnalyse, bool optimization) : staticAnalyse(staticAnalyse), optimization(optimization){};
      SymbolTable *symbolTable;
      bool staticAnalyse;
      bool optimization;

      // -------------------- It represents the program => It's the first visitor
      virtual antlrcpp::Any visitProg(Grammar4Parser::ProgContext *ctx) override
      {
            //cout << "2.1" << endl;

            //Creating the symbolTable
            if (staticAnalyse)
            {
                  this->symbolTable = new SymbolTable();
            }

            Function *f;

            // -------------------- Functions
            map<string, Function *> *funcList = new map<string, Function *>();
            for (int i = 0; i < ctx->funcdef().size(); i++)
            {
                  f = (Function *)visit(ctx->funcdef(i));
                  funcList->insert(pair<string, Function *>(f->name, f));
            }

            //cout << "2.2" << endl;

            // -------------------- Main Function
            Function *mainf = (Function *)visit(ctx->main());
            //cout << "2.3" << endl;
            funcList->insert(pair<string, Function *>(mainf->name, mainf));

            return (Prog *)new Prog(funcList);
      }

      // -------------------- Function Main definition => type is INT and 0 params possible
      virtual antlrcpp::Any visitMain(Grammar4Parser::MainContext *ctx) override
      {
            //cout << "2.2.1" << endl;

            // -------------------- Type = INT
            Type rtype = INT;

            // -------------------- Name = "main"
            string name = "main";

            if (staticAnalyse && !symbolTable->addFunction(name, rtype))
            {
                  cerr << "Function " << name << " has already been defined" << endl;
                  exit(1);
            }

            // -------------------- Params => No params
            vector<ExpressionVar *> *params = new vector<ExpressionVar *>(0);

            // -------------------- Declarations
            vector<Declaration *> *subList;
            vector<Declaration *> *declList = new vector<Declaration *>(0);
            for (int i = 0; i < ctx->declaration().size(); i++)
            {
                  subList = (vector<Declaration *> *)visit(ctx->declaration(i));
                  for (Declaration *decl : *subList)
                  {
                        declList->push_back(decl);
                  }
            }

            //cout << "2.2.2" << endl;

            // -------------------- Statements
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            //cout << "2.2.3" << endl;

            // -------------------- Statement Return => it exisits
            StatementReturn *rstat = (StatementReturn *)visit(ctx->rstat());
            /*if (staticAnalyse && rstat->value->type != rtype)
            {
                  cerr << "Return type of " << name << " function does not match with return statement" << endl;
                  exit(1);
            }*/

            if (staticAnalyse)
            {
                  symbolTable->functionEnd();
            }

            return (Function *)new Function(rtype, name, params, declList, statList, rstat);
      }

      // -------------------- Function Definition
      virtual antlrcpp::Any visitFuncdef(Grammar4Parser::FuncdefContext *ctx) override
      {
            //cout << "2.1.1" << endl;

            // -------------------- Type
            Type rtype = (Type)visit(ctx->rtype());

            // -------------------- Name
            string name = ctx->ID()->getText().c_str();

            if (staticAnalyse && !symbolTable->addFunction(name, rtype))
            {
                  cerr << "Function " << name << " has already been defined" << endl;
                  exit(1);
            }

            // -------------------- Params
            vector<ExpressionVar *> *paramsList = new vector<ExpressionVar *>(0);
            if (ctx->dparams())
            {
                  paramsList = visit(ctx->dparams());
            }

            //cout << "2.1.2" << endl;

            // -------------------- Declarations
            vector<Declaration *> *declSubList;
            vector<Declaration *> *declList = new vector<Declaration *>(0);
            for (int i = 0; i < ctx->declaration().size(); i++)
            {
                  declSubList = (vector<Declaration *> *)visit(ctx->declaration(i));
                  for (Declaration *decl : *declSubList)
                  {
                        declList->push_back(decl);
                  }
            }
            //cout << "2.1.3" << endl;

            /// -------------------- Statements
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            //cout << "2.1.4" << endl;

            // -------------------- Statement Return
            StatementReturn *rstat = nullptr;
            if (ctx->rstat())
            {
                  rstat = (StatementReturn *)visit(ctx->rstat());
                  if (staticAnalyse && rstat->value->type != rtype)
                  {
                        cerr << "Return type of " << name << " function does not match with return statement" << endl;
                        exit(1);
                  }
            }

            //cout << "2.1.5" << endl;

            Function *function = new Function(rtype, name, paramsList, declList, statList, rstat);

            if (staticAnalyse)
            {
                  symbolTable->functionEnd();
            }

            return (Function *)function;
      }

      // -------------------- Function Call
      virtual antlrcpp::Any visitFncall(Grammar4Parser::FncallContext *ctx) override
      {
            // -------------------- Name  of the called function
            string name = ctx->ID()->getText().c_str();

            // -------------------- Type of the called function
            Type type = INT; //TODO: modif
            if (staticAnalyse)
            {
                  Symbol *functionSymbol = symbolTable->getSymbol(name);
                  if (!functionSymbol)
                  {
                        cerr << "Function " << name << " does not exists" << endl;
                        exit(1);
                  }

                  type = functionSymbol->type;
            }

            // -------------------- Params values sent to the called function
            vector<Expression *> *params = new vector<Expression *>(0);
            if (ctx->cparams())
            {
                  params = (vector<Expression *> *)visit(ctx->cparams());
            }

            return (ExpressionCall *)new ExpressionCall(type, name, params);
      }

      virtual antlrcpp::Any visitBlock(Grammar4Parser::BlockContext *ctx) override
      {
            // -------------------- Statements
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            // -------------------- Statement Return
            StatementReturn *rstat = nullptr;
            if (ctx->rstat())
            {
                  rstat = (StatementReturn *)visit(ctx->rstat());
            }

            return (Block *)new Block(statList, rstat);
      }

      // -------------------- Params in case of function definition
      virtual antlrcpp::Any visitDparams(Grammar4Parser::DparamsContext *ctx) override
      {
            // -------------------- Other params
            //cout << "2.1.1.1" << endl;
            vector<ExpressionVar *> *paramsList;
            if (ctx->dparams())
            {
                  paramsList = (vector<ExpressionVar *> *)visit(ctx->dparams());
            }
            else
            {
                  paramsList = new vector<ExpressionVar *>(0);
            }

            //cout << "2.1.1.2" << endl;

            // -------------------- New param
            ExpressionVar *expr = (ExpressionVar *)visit(ctx->dparam());

            //cout << "2.1.1.3" << endl;

            paramsList->insert(paramsList->begin(), expr);
            return (vector<ExpressionVar *> *)paramsList;
      }

      // -------------------- Param in case of function definition
      virtual antlrcpp::Any visitDparam(Grammar4Parser::DparamContext *ctx) override
      {
            // -------------------- Type
            Type type = (Type)visit(ctx->type());

            // -------------------- Name
            string name = ctx->ID()->getText().c_str();

            if (staticAnalyse && !symbolTable->addVar(name, type))
            {
                  cerr << "Variable " << name << " has already been declared" << endl;
                  exit(1);
            }

            return (ExpressionVar *)new ExpressionVar(type, name);
      }

      // -------------------- Params in case of function call
      virtual antlrcpp::Any visitCparams(Grammar4Parser::CparamsContext *ctx) override
      {
            // -------------------- Other params
            vector<Expression *> *paramsList;
            if (ctx->cparams())
            {
                  paramsList = (vector<Expression *> *)visit(ctx->cparams());
            }
            else
            {
                  paramsList = new vector<Expression *>(0);
            }

            // -------------------- New param
            Expression *expr = (Expression *)visit(ctx->expr());

            paramsList->insert(paramsList->begin(), expr);
            return (vector<Expression *> *)paramsList;
      }

      // -------------------- Declarations of variables
      virtual antlrcpp::Any visitDeclaration(Grammar4Parser::DeclarationContext *ctx) override
      {
            //cout << "2.2.1.1" << endl;

            // -------------------- Type
            Type type = (Type)visit(ctx->type());
            //cout << "2.2.1.2" << endl;

            // -------------------- All declarations
            vector<Declaration *> *decls = (vector<Declaration *> *)visit(ctx->variables());
            //cout << "2.2.1.3" << endl;

            // -------------------- Give type to all declarations
            for (Declaration *d : *decls)
            {
                  d->left->type = type;
                  if (staticAnalyse && !symbolTable->addVar(d->left->name, d->left->type))
                  {
                        cerr << "Variable " << d->left->name << " has already been declared" << endl;
                        exit(1);
                  }
            }
            //cout << "2.2.1.4" << endl;

            return (vector<Declaration *> *)decls;
      }

      // -------------------- List of variables in a declaration
      virtual antlrcpp::Any visitVariables(Grammar4Parser::VariablesContext *ctx) override
      {
            //cout << "2.2.1.2.1" << endl;

            // -------------------- Other variables
            vector<Declaration *> *decls;
            if (ctx->variables())
            {
                  decls = (vector<Declaration *> *)visit(ctx->variables());
            }
            else
            {
                  decls = new vector<Declaration *>(0);
            }
            //cout << "2.2.1.2.2" << endl;

            // -------------------- New variable
            Declaration *d = (Declaration *)visit(ctx->variable());
            //cout << "2.2.1.2.3" << endl;

            decls->insert(decls->begin(), d);
            //cout << "2.2.1.2.4" << endl;

            return (vector<Declaration *> *)decls;
      }

      // -------------------- Variable declaration without initialisation
      virtual antlrcpp::Any visitDecl(Grammar4Parser::DeclContext *ctx) override
      {
            // -------------------- Creating new variable
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());

            return (Declaration *)new Declaration(var);
      }

      // -------------------- Variable declaration with initialisation
      virtual antlrcpp::Any visitInit(Grammar4Parser::InitContext *ctx) override
      {
            //cout << "2.2.1.2.2.1" << endl;

            // -------------------- New variable
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());
            //cout << "2.2.1.2.2.2" << endl;

            // -------------------- Value assigned to new variable
            Expression *right = visit(ctx->expr());
            //cout << "2.2.1.2.2.3" << endl;

            Declaration *declaration = new Declaration(left, right);
            //cout << "2.2.1.2.2.4" << endl;

            return (Declaration *)declaration;
      }

      // -------------------- Statement return
      virtual antlrcpp::Any visitRstat(Grammar4Parser::RstatContext *ctx) override
      {
            // -------------------- The expression returned
            Expression *val = (Expression *)visit(ctx->expr());
            return (StatementReturn *)new StatementReturn(val);
      }

      // -------------------- Statement to assign value to an existing variable
      virtual antlrcpp::Any visitAsgn(Grammar4Parser::AsgnContext *ctx) override
      {
            // -------------------- The existing variable
            string name = ctx->ID()->getText().c_str();
            if (staticAnalyse)
            {
                  Symbol *var = symbolTable->getSymbol(name);
                  if (!var)
                  {
                        cerr << "Variable " << name << " does not exists" << endl;
                        exit(1);
                  }
            }

            ExpressionVar *left = new ExpressionVar(name);

            // -------------------- The value
            Expression *right = (Expression *)visit(ctx->expr());

            return (Statement *)new StatementAssignement(left, right);
      }

      // -------------------- Statement to call a function without catching the returned value
      virtual antlrcpp::Any visitCallnr(Grammar4Parser::CallnrContext *ctx) override
      {
            //cout << "2.2.2.1" << endl;

            // -------------------- Function called
            ExpressionCall *expr = (ExpressionCall *)visit(ctx->fncall());
            //cout << "2.2.2.2" << endl;

            StatementFunction *statement = new StatementFunction(expr);
            //cout << "2.2.2.3" << endl;
            return (Statement *)statement;
      }

      virtual antlrcpp::Any visitStatifelse(Grammar4Parser::StatifelseContext *ctx) override
      {
            Statement *statement = (StatementIfElse *)visit(ctx->ifelse());
            return (Statement *)statement;
      }

      virtual antlrcpp::Any visitStatwhile(Grammar4Parser::StatwhileContext *ctx) override
      {
            Statement *statement = (StatementWhile *)visit(ctx->whilerule());
            return (Statement *)statement;
      }

      virtual antlrcpp::Any visitWhilerule(Grammar4Parser::WhileruleContext *ctx) override
      {
            Expression *cond = (Expression *)visit(ctx->expr());

            Block *block = (Block *)visit(ctx->block());

            return (StatementWhile *)new StatementWhile(cond, block);
      }

      virtual antlrcpp::Any visitIfelse(Grammar4Parser::IfelseContext *ctx) override
      {
            Expression *cond = (Expression *)visit(ctx->expr());

            Block *block = (Block *)visit(ctx->block());

            StatementIfElse *elserule = nullptr;

            if (ctx->elserule())
            {
                  elserule = (StatementIfElse *)visit(ctx->elserule());
            }
            return (StatementIfElse *)new StatementIfElse(cond, block, elserule);
      }

      virtual antlrcpp::Any visitElseonly(Grammar4Parser::ElseonlyContext *ctx) override
      {
            Block *block = (Block *)visit(ctx->block());

            return (StatementIfElse *)new StatementIfElse(block);
      }

      virtual antlrcpp::Any visitElseif(Grammar4Parser::ElseifContext *ctx) override
      {
            return (StatementIfElse *)visit(ctx->ifelse());
      }

      // -------------------- Expression Par
      virtual antlrcpp::Any visitPar(Grammar4Parser::ParContext *ctx) override
      {
            // -------------------- The expression contained in par
            Expression *expression = (Expression *)visit(ctx->expr());

            if (optimization)
            {
                  ExpressionConst *exprCst = dynamic_cast<ExpressionConst *>(expression);

                  if (exprCst != nullptr)
                  {
                        return (Expression *)exprCst;
                  }
            }

            return (Expression *)new ExpressionPar(INT, expression);
      }

      // -------------------- Expression Plus or Minus
      virtual antlrcpp::Any visitPlusminus(Grammar4Parser::PlusminusContext *ctx) override
      {
            // -------------------- Left operand
            Expression *left = (Expression *)visit(ctx->expr(0));

            // -------------------- Right operand
            Expression *right = (Expression *)visit(ctx->expr(1));

            // -------------------- building the expression Plus or Minus
            if (ctx->PLUSMINUS()->getText().compare("+") == 0)
            {
                  if (optimization)
                  {
                        ExpressionConst *exprCstLeft = dynamic_cast<ExpressionConst *>(left);
                        ExpressionConst *exprCstRight = dynamic_cast<ExpressionConst *>(right);

                        if (exprCstLeft != nullptr && exprCstRight)
                        {
                              return (Expression *) new ExpressionConst(INT, exprCstLeft->value + exprCstRight->value);
                        }
                  }
                  return (Expression *)new ExpressionPlus(INT, left, right);
            }
            else
            {
                  if (optimization)
                  {
                        ExpressionConst *exprCstLeft = dynamic_cast<ExpressionConst *>(left);
                        ExpressionConst *exprCstRight = dynamic_cast<ExpressionConst *>(right);

                        if (exprCstLeft != nullptr && exprCstRight)
                        {
                              return (Expression *) new ExpressionConst(INT, exprCstLeft->value - exprCstRight->value);
                        }
                  }
                  return (Expression *)new ExpressionMinus(INT, left, right);
            }
      }

      // -------------------- Expression mult
      virtual antlrcpp::Any visitMult(Grammar4Parser::MultContext *ctx) override
      {
            // -------------------- Left operand
            Expression *left = (Expression *)visit(ctx->expr(0));

            // -------------------- Right operand
            Expression *right = (Expression *)visit(ctx->expr(1));

            if (optimization)
                  {
                        ExpressionConst *exprCstLeft = dynamic_cast<ExpressionConst *>(left);
                        ExpressionConst *exprCstRight = dynamic_cast<ExpressionConst *>(right);

                        if (exprCstLeft != nullptr && exprCstRight)
                        {
                              return (Expression *) new ExpressionConst(INT, exprCstLeft->value * exprCstRight->value);
                        }
                  }

            return (Expression *)new ExpressionMult(INT, left, right);
      }

      // -------------------- Const value (expression too)
      virtual antlrcpp::Any visitConst(Grammar4Parser::ConstContext *ctx) override
      {
            // -------------------- Casting the value
            ExpressionConst *val = new ExpressionConst(INT, (int)stoi(ctx->INT()->getText()));
            return (Expression *)val;
      }

      // -------------------- Function call with value catching (as an expression)
      virtual antlrcpp::Any visitCallr(Grammar4Parser::CallrContext *ctx) override
      {
            //cout << "2.2.1.2.2.2.1" << endl;

            // -------------------- The called function
            Expression *expr = (ExpressionCall *)visit(ctx->fncall());
            //cout << "2.2.1.2.2.2.2" << endl;

            return (Expression *)expr;
      }

      virtual antlrcpp::Any visitUnopexpr(Grammar4Parser::UnopexprContext *ctx) override
      {
            Expression *value = (Expression *)visit(ctx->expr());

            if (ctx->UNOP()->getText().compare("!") == 0)
            {
                  return (Expression *)new ExpressionUnaryNo(INT, value);
            }
            else
            {
                  return (Expression *)new ExpressionUnaryMinus(INT, value);
            }
      }

      // -------------------- Var value (Expression too)
      virtual antlrcpp::Any visitVar(Grammar4Parser::VarContext *ctx) override
      {
            string name = ctx->ID()->getText().c_str();
            //cout << "2.1.4.1" << endl;
            if (staticAnalyse)
            {
                  Symbol *var = symbolTable->getSymbol(name);
                  //cout << "2.1.4.2" << endl;
                  if (var == nullptr)
                  {
                        cerr << "Variable " << name << " does not exists" << endl;
                        exit(1);
                  }
            }

            //cout << "2.1.4.3" << endl;
            return (Expression *)new ExpressionVar(name);
      }

      virtual antlrcpp::Any visitCompexpr(Grammar4Parser::CompexprContext *ctx) override
      {
            // -------------------- Left operand
            Expression *left = (Expression *)visit(ctx->expr(0));

            // -------------------- Right operand
            Expression *right = (Expression *)visit(ctx->expr(1));

            if (ctx->COMPOP()->getText().compare("==") == 0)
            {
                  return (Expression *)new ExpressionCompEq(INT, left, right);
            }
            else if (ctx->COMPOP()->getText().compare("!=") == 0)
            {
                  return (Expression *)new ExpressionCompDif(INT, left, right);
            }
            else if (ctx->COMPOP()->getText().compare("<") == 0)
            {
                  return (Expression *)new ExpressionCompInf(INT, left, right);
            }
            else
            {
                  return (Expression *)new ExpressionCompSup(INT, left, right);
            }
      }

      virtual antlrcpp::Any visitLogexpr(Grammar4Parser::LogexprContext *ctx) override
      {
            // -------------------- Left operand
            Expression *left = (Expression *)visit(ctx->expr(0));

            // -------------------- Right operand
            Expression *right = (Expression *)visit(ctx->expr(1));

            if (ctx->LOGOP()->getText().compare("&&") == 0)
            {
                  return (Expression *)new ExpressionLogAnd(INT, left, right);
            }
            else if (ctx->LOGOP()->getText().compare("||") == 0)
            {
                  return (Expression *)new ExpressionLogOr(INT, left, right);
            }
            else
            {
                  return (Expression *)new ExpressionLogXor(INT, left, right);
            }
      }

      virtual antlrcpp::Any visitRtypeTYPE(Grammar4Parser::RtypeTYPEContext *ctx) override
      {
            return (Type)visit(ctx->type());
      }

      virtual antlrcpp::Any visitRtypeVOID(Grammar4Parser::RtypeVOIDContext *ctx) override
      {
            return (Type)VOID;
      }

      virtual antlrcpp::Any visitTypeINT(Grammar4Parser::TypeINTContext *ctx) override
      {
            return (Type)INT;
      }
};