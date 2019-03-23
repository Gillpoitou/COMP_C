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
            //cout << "2.1" << endl;
            return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitMain(Grammar2Parser::MainContext *ctx) override
      {
            //cout << "2.2" << endl;

            Declaration *decl;

            vector<Declaration *> *declList = new vector<Declaration *>(0);

            for (int i = 0; i < ctx->declaration().size(); i++)
            {
                  //cout << "2.2.1" << endl;
                  decl = (Declaration *)visit(ctx->declaration(i));
                  //cout << "2.2.2" << endl;
                  this->declarations.insert(pair<string, Declaration *>(decl->left->name, decl));
                  declList->push_back(decl);
            }
            return (Function *)new Function(declList);
            // return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitDecl(Grammar2Parser::DeclContext *ctx) override
      {
            //cout << "2.3" << endl;

            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());

            return (Declaration *)new Declaration(var);
            // return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitInitVar(Grammar2Parser::InitVarContext *ctx) override
      {

            //cout << "2.4" << endl;

            // cout << "initVar" << endl;
            ExpressionVar *right;

            // cout << ctx->ID(1)->getText() << endl;
            // cout << declarations.size() << endl;
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

            // cout << declaration->toString() << endl;

            return (Declaration *)declaration;
            // return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitInitCst(Grammar2Parser::InitCstContext *ctx) override
      {
            //cout << "2.5" << endl;

            ExpressionConst *val = new ExpressionConst(stoi(ctx->INT()->getText()));
            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str(), val);

            Declaration *declaration = new Declaration(var, val);

            // cout << declaration->toString() << endl;

            return (Declaration *)declaration;
            // return visitChildren(ctx);
      }

    protected:
      map<string, Declaration *> declarations;
};
