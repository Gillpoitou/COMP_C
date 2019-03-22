#pragma once
#include <string.h>
#include <map>
#include "antlr4-runtime.h"
#include "Grammar2BaseVisitor.h"
#include "Expression.h"
#include "Declaration.h"

using namespace std;
class Visitor : public Grammar2BaseVisitor
{
    public:
      virtual antlrcpp::Any visitMain(Grammar2Parser::MainContext *ctx) override
      {
            Declaration * decl;
            for(int i = 0; i<ctx->declaration().size(); i++){
                  decl = (Declaration*) visitChildren(ctx->declaration(i));
                  this->declarations.insert(pair<string, Declaration*>(decl->left->name, decl));
            }

            //TODO: modifier renvoyer le bon type
            return (this->declarations);
      }

      virtual antlrcpp::Any visitDecl(Grammar2Parser::DeclContext *ctx) override
      {
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());

            return (Declaration *)new Declaration(var);
      }

      virtual antlrcpp::Any visitInitVar(Grammar2Parser::InitVarContext *ctx) override
      {
            ExpressionVar *right = declarations[ctx->ID(1)->getText().c_str()]->left;
            ExpressionVar *left = new ExpressionVar(ctx->ID(0)->getText().c_str(), right);

            return (Declaration *)new Declaration(left, right);
            ;
      }

      virtual antlrcpp::Any visitInitCst(Grammar2Parser::InitCstContext *ctx) override
      {
            ExpressionConst *val = new ExpressionConst(stoi(ctx->INT()->getText()));
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str(), val);

            return (Declaration *)new Declaration(var, val);
      }

    protected:
      map<string, Declaration *> declarations;
}