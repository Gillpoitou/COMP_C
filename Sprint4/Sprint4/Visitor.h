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
      // map<string, SymbAtt *> *symbTable; //the symbol table

      virtual antlrcpp::Any visitProg(Grammar4Parser::ProgContext *ctx) override
      {
            //creating the symbol table
            // symbTable = new map<string, SymbAtt *>();
            //cout << "2.1" << endl;
            Function *f;

            map<string, Function *> *funcList = new map<string, Function *>();
            for (int i = 0; i < ctx->funcdef().size(); i++)
            {
                  f = (Function *)visit(ctx->funcdef(i));
                  funcList->insert(pair<string, Function *>(f->name, f));
                  // symbTable->insert(pair<string, SymbAtt *>(f->name, new SymbAtt(f->name, UNDEFINED, f->rtype)));
            }

            //cout << "2.2" << endl;

            Function *mainf = (Function *)visit(ctx->main());

            //cout << "2.3" << endl;
            funcList->insert(pair<string, Function *>(mainf->name, mainf));
            return (Prog *)new Prog(funcList);
      }

      virtual antlrcpp::Any visitMain(Grammar4Parser::MainContext *ctx) override
      {
            //cout << "2.2.1" << endl;
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
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            //cout << "2.2.3" << endl;
            StatementReturn *rstat = (StatementReturn *)visit(ctx->rstat());
            Type rtype = INT;
            vector<ExpressionVar *> *params = new vector<ExpressionVar *>(0);
            return (Function *)new Function(rtype, "main", params, declList, statList, rstat);
      }

      virtual antlrcpp::Any visitFuncdef(Grammar4Parser::FuncdefContext *ctx) override
      {
            //cout << "2.1.1" << endl;

            Type rtype = (Type)visit(ctx->rtype());

            string name = ctx->ID()->getText().c_str();

            //Params
            vector<ExpressionVar *> *paramsList = new vector<ExpressionVar *>(0);
            if (ctx->dparams())
            {
                  paramsList = visit(ctx->dparams());
            }
            //cout << "2.1.2" << endl;

            //Declarations
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

            //Statements
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            //cout << "2.1.4" << endl;

            //Rstat
            StatementReturn *rstat = nullptr;
            if (ctx->rstat())
            {
                  rstat = (StatementReturn *)visit(ctx->rstat());
            }

            //cout << "2.1.5" << endl;

            Function *function = new Function(rtype, name, paramsList, declList, statList, rstat);

            return (Function *)function;
      }

      virtual antlrcpp::Any visitFncall(Grammar4Parser::FncallContext *ctx) override
      {

            //TODO: Modify to get the type of the function with symbolTable
            Type type = INT;
            string name = ctx->ID()->getText().c_str();

            vector<Expression *> *params = new vector<Expression *>(0);
            if (ctx->cparams())
            {
                  params = (vector<Expression *> *)visit(ctx->cparams());
            }

            return (ExpressionCall *)new ExpressionCall(type, name, params);

            //check  params match formal params of the func
            //check  give a the return type to the expr
            //check the function exists

            // ExpressionCall *call;
            // vector<Expression *> *params;

            // params = (vector<Expression *>)visit(ctx->dparams());

            // if (params == null){
            //       params = new vector<Expression *>(0);
            // }

            //TODO get the rtype of the func in atype
            //call = new ExpressionCall(atype, ctx->ID()->getText().c_str(), params);

            //return call;
      }

      virtual antlrcpp::Any visitDparams(Grammar4Parser::DparamsContext *ctx) override
      {
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
            ExpressionVar *expr = (ExpressionVar *)visit(ctx->dparam());
            //cout << "2.1.1.3" << endl;
            paramsList->insert(paramsList->begin(), expr);
            return (vector<ExpressionVar *> *)paramsList;
      }

      virtual antlrcpp::Any visitDparam(Grammar4Parser::DparamContext *ctx) override
      {
            Type type = (Type)visit(ctx->type());
            string name = ctx->ID()->getText().c_str();
            return (ExpressionVar *)new ExpressionVar(type, name);
      }

      virtual antlrcpp::Any visitCparams(Grammar4Parser::CparamsContext *ctx) override
      {
            vector<Expression *> *paramsList;
            if (ctx->cparams())
            {
                  paramsList = (vector<Expression *> *)visit(ctx->cparams());
            }
            else
            {
                  paramsList = new vector<Expression *>(0);
            }
            Expression *expr = (Expression *)visit(ctx->expr());
            paramsList->insert(paramsList->begin(), expr);
            return (vector<Expression *> *)paramsList;
      }

      virtual antlrcpp::Any visitDeclaration(Grammar4Parser::DeclarationContext *ctx) override
      {
            //cout << "2.2.1.1" << endl;
            Type type = (Type)visit(ctx->type());
            //cout << "2.2.1.2" << endl;

            vector<Declaration *> *decls = (vector<Declaration *> *)visit(ctx->variables());
            //cout << "2.2.1.3" << endl;

            for (Declaration *d : *decls)
            {
                  d->left->type = type;
            }
            //cout << "2.2.1.4" << endl;

            return (vector<Declaration *> *)decls;
      }

      virtual antlrcpp::Any visitVariables(Grammar4Parser::VariablesContext *ctx) override
      {
            //cout << "2.2.1.2.1" << endl;
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
            Declaration *d = (Declaration *)visit(ctx->variable());
            //cout << "2.2.1.2.3" << endl;
            decls->insert(decls->begin(), d);
            //cout << "2.2.1.2.4" << endl;
            return (vector<Declaration *> *)decls;
      }

      virtual antlrcpp::Any visitDecl(Grammar4Parser::DeclContext *ctx) override
      {
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());
            return (Declaration *)new Declaration(var);
      }

      virtual antlrcpp::Any visitInit(Grammar4Parser::InitContext *ctx) override
      {
            //cout << "2.2.1.2.2.1" << endl;
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());
            //cout << "2.2.1.2.2.2" << endl;
            Expression *right = visit(ctx->expr());
            //cout << "2.2.1.2.2.3" << endl;

            Declaration *declaration = new Declaration(left, right);
            //cout << "2.2.1.2.2.4" << endl;

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

            return (Statement *)new StatementAssignement(left, right);
      }

      virtual antlrcpp::Any visitCallnr(Grammar4Parser::CallnrContext *ctx) override
      {
            //cout << "2.2.2.1" << endl;
            ExpressionCall *expr = (ExpressionCall *)visit(ctx->fncall());
            //cout << "2.2.2.2" << endl;
            StatementFunction *statement = new StatementFunction(expr);
            //cout << "2.2.2.3" << endl;
            return (Statement *)statement;
      }

      virtual antlrcpp::Any visitPar(Grammar4Parser::ParContext *ctx) override
      {
            Expression *expression = (Expression *)visit(ctx->expr());
            return (Expression *)new ExpressionPar(INT, expression);
      }

      virtual antlrcpp::Any visitPlusminus(Grammar4Parser::PlusminusContext *ctx) override
      {
            Expression *left = (Expression *)visit(ctx->expr(0));
            Expression *right = (Expression *)visit(ctx->expr(1));

            if (ctx->PLUSMINUS()->getText().compare("+") == 0)
            {
                  return (Expression *)new ExpressionPlus(INT, left, right);
            }
            else
            {
                  return (Expression *)new ExpressionMinus(INT, left, right);
            }
      }

      virtual antlrcpp::Any visitMult(Grammar4Parser::MultContext *ctx) override
      {
            Expression *left = (Expression *)visit(ctx->expr(0));
            Expression *right = (Expression *)visit(ctx->expr(1));

            return (Expression *)new ExpressionMult(INT, left, right);
      }

      virtual antlrcpp::Any visitConst(Grammar4Parser::ConstContext *ctx) override
      {
            ExpressionConst *val = new ExpressionConst(INT, (int)stoi(ctx->INT()->getText()));
            return (Expression *)val;
      }

      virtual antlrcpp::Any visitCallr(Grammar4Parser::CallrContext *ctx) override
      {
            //cout << "2.2.1.2.2.2.1" << endl;
            Expression * expr = (ExpressionCall *)visit(ctx->fncall());
            //cout << "2.2.1.2.2.2.2" << endl;
            return (Expression *)expr;
      }

      virtual antlrcpp::Any visitVar(Grammar4Parser::VarContext *ctx) override
      {
            return (Expression *)new ExpressionVar(ctx->ID()->getText().c_str());
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

/*

      TODO:

      Une pile de table de symbole => chaque étage est une table correspondant à un contexte (une fonction dans notre cas)
      Lorsqu'on rentre dans la définition d'une fonction => on empile un table de symboles. Quand la définition est terminée, on dépile

      Pour chaque 
            Déclaration de variable
            => Vérifier que ça n'existe pas déjà dans la table des symboles du contexte

            Utilisation de variable
            Initialisation de variable
            Appel de fonction
            => Vérifier qu'elle existe dans la table des symboles
            
*/