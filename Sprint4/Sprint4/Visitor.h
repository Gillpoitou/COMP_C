#pragma once
#include <string.h>
#include <map>
#include <vector>
#include <iostream>

#include "antlr4-runtime.h"
#include "Grammar4BaseVisitor.h"
#include "Function.h"
#include "Prog.h"
#include "Type.h"
#include "SymbAtt.h"

using namespace std;
class Visitor : public Grammar4BaseVisitor
{
    public:

      map<string, SymbAtt*> *symbTable;    //the symbol table

      virtual antlrcpp::Any visitProg(Grammar4Parser::ProgContext *ctx) override
      {
            //creating the symbol table
            symbTable = new map<string, SymbAtt*>();

            Function *f;

            map<string, Function *> *funcList = new map<string, Function *>();
            for (int i = 0; i < ctx->funcdef().size(); i++)
            {
                  f = (Function *)visit(ctx->funcdef(i));

                  funcList->insert(pair<string, Function *>(f->name, f));
            }
            Function *mainf = (Function *)visit(ctx->main());
            funcList->insert(pair<string, Function *>(mainf->name, mainf));
            return (Prog *)new Prog(funcList);
      }

      virtual antlrcpp::Any visitFuncdef(Grammar4Parser::FuncdefContext *ctx) override
      {
            return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitFncall(Grammar4Parser::FncallContext *ctx) override 
      {
            //check  params match formal params of the func
            //check  give a the return type to the expr
            //check the function exists

            ExpressionCall *call;
            vector<Expression *> *params;

            params = (vector<Expression *>)visit(ctx->dparams());
            
            if (params == null){
                  params = new vector<Expression *>(0);
            }

            //TODO get the rtype of the func in atype
            //call = new ExpressionCall(atype, ctx->ID()->getText().c_str(), params);

            //return call;
      }

      virtual antlrcpp::Any visitMain(Grammar4Parser::MainContext *ctx) override
      {
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
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            StatementReturn *rstat = (StatementReturn *)visit(ctx->rstat());
            Type rtype = INT;
            vector<ExpressionVar *> *params;
            return (Function *)new Function(rtype, "main", params, declList, statList, rstat);
      }

      virtual antlrcpp::Any visitDeclaration(Grammar4Parser::DeclarationContext *ctx) override
      {
            vector<Declaration *> *decls = new vector<Declaration *>(0);
            Type type = (Type)visit(ctx->type());

            vector<Declaration *> *decls = (vector<Declaration *> *)visit(ctx->variables());

            for(Declaration * d : *decls){
                  d->left->type = type;
            }

            return (vector<Declaration *> * )decls;
      }

      virtual antlrcpp::Any visitVariables(Grammar4Parser::VariablesContext *ctx) override
      {
            vector<Declaration *> *decls = (vector<Declaration *> *)visit(ctx->variables());
            Declaration *d = (Declaration *)visit(ctx->variable());
            decls->insert(decls->begin(), d);
            return (vector<Declaration *> *)decls;
      }

      virtual antlrcpp::Any visitDecl(Grammar4Parser::DeclContext *ctx) override
      {
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());
            return (Declaration *)new Declaration(var);
      }

      virtual antlrcpp::Any visitInit(Grammar4Parser::InitContext *ctx) override
      {
            Expression *right = visit(ctx->expr());
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());

            Declaration *declaration = new Declaration(left, right);
            return (Declaration *)declaration;
      }

      virtual antlrcpp::Any visitRstat(Grammar4Parser::RstatContext *ctx) override
      {
            Expression *val = (Expression *)visit(ctx->expr());
            return (StatementReturn *)new StatementReturn(val);
      }

      virtual antlrcpp::Any visitAsgn(Grammar4Parser::AsgnContext *ctx) override
      {
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());
            Expression *right = (Expression *)visit(ctx->expr());

            return (Statement *)new Statement(left, right);
      }

      virtual antlrcpp::Any visitMult(Grammar4Parser::MultContext *ctx) override
      {
            Expression *left = (Expression *)visit(ctx->expr(0));
            Expression *right = (Expression *)visit(ctx->expr(1));

            return (Expression *)new ExpressionMult(left, right);
      }

      virtual antlrcpp::Any visitPlusminus(Grammar4Parser::PlusminusContext *ctx) override
      {
            Expression *left = (Expression *)visit(ctx->expr(0));
            Expression *right = (Expression *)visit(ctx->expr(1));

            if (ctx->PLUSMINUS()->getText().compare("+") == 0)
            {
                  return (Expression *)new ExpressionPlus(left, right);
            }
            else
            {
                  return (Expression *)new ExpressionMinus(left, right);
            }
      }

      virtual antlrcpp::Any visitConst(Grammar4Parser::ConstContext *ctx) override
      {
            cout << "2.1.2.1" << endl;
            ExpressionConst *val = new ExpressionConst((int)stoi(ctx->INT()->getText()));
            cout << "2.1.2.2" << endl;
            return (Expression *)val;
      }

      virtual antlrcpp::Any visitVar(Grammar4Parser::VarContext *ctx) override
      {
            return (Expression *)new ExpressionVar(ctx->ID()->getText().c_str());
      }

      virtual antlrcpp::Any visitPar(Grammar4Parser::ParContext *ctx) override
      {
            Expression *expression = (Expression *)visit(ctx->expr());
            return (Expression *)new ExpressionPar(expression);
      }

      virtual antlrcpp::Any visitTypeINT(Grammar4Parser::TypeINTContext *ctx) override
      {
            return (Type)INT;
      }
};
