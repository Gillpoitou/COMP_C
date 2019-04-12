#pragma once
#include <string.h>
#include <map>
#include <vector>
#include <iostream>

#include "antlr4-runtime.h"
#include "Grammar2BaseVisitor.h"
#include "Function.h"

using namespace std;
class Visitor : public Grammar2BaseVisitor
{
    public:
      virtual antlrcpp::Any visitProg(Grammar2Parser::ProgContext *ctx) override
      {
            return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitMain(Grammar2Parser::MainContext *ctx) override
      {

            Declaration *decl;

            vector<Declaration *> *declList = new vector<Declaration *>(0);

            for (int i = 0; i < ctx->declaration().size(); i++)
            {
                  decl = (Declaration *)visit(ctx->declaration(i));
                  this->declarations.insert(pair<string, Declaration *>(decl->left->name, decl));
                  declList->push_back(decl);
            }
	    vector<Statement *> *stats = new vector<Statement *>(0);
	    if(ctx->rstat()){
		StatementReturn *ret = (StatementReturn *)visit(ctx->rstat());
	    	stats->push_back(ret);
	    }else{
            	stats = nullptr;
	    }
            return (Function *)new Function(declList, stats);
      }

      virtual antlrcpp::Any visitDecl(Grammar2Parser::DeclContext *ctx) override
      {

            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());

            return (Declaration *)new Declaration(var);
      }

      virtual antlrcpp::Any visitInitVar(Grammar2Parser::InitVarContext *ctx) override
      {
            ExpressionVar *right;
            if (declarations[ctx->ID(1)->getText().c_str()])
            {
                  right = declarations[ctx->ID(1)->getText().c_str()]->left;
            }
            else
            {
                  cout << "PAS NORMAL" << endl;
            }
            ExpressionVar *left = new ExpressionVar(ctx->ID(0)->getText().c_str(), right);

            Declaration *declaration = new Declaration(left, right);

            return (Declaration *)declaration;
      }

      virtual antlrcpp::Any visitInitCst(Grammar2Parser::InitCstContext *ctx) override
      {

            ExpressionConst *val = new ExpressionConst(stoi(ctx->INT()->getText()));
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str(), val);

            Declaration *declaration = new Declaration(var, val);

            return (Declaration *)declaration;
      }

      virtual antlrcpp::Any visitRetInt(Grammar2Parser::RetIntContext *ctx) override
      {
	    ExpressionConst *val = new ExpressionConst(stoi(ctx->INT()->getText()));
	    return (StatementReturn *)new StatementReturn(val);
      }

      virtual antlrcpp::Any visitRetVar(Grammar2Parser::RetVarContext *ctx) override
      {
	    ExpressionVar *val = declarations[ctx->ID()->getText().c_str()]->left;
	    return (StatementReturn *) new StatementReturn(val);
      }

    protected:
      map<string, Declaration *> declarations;
};
