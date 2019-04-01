#pragma once
#include <string.h>
#include <map>
#include <vector>
#include <iostream>

#include "antlr4-runtime.h"
#include "Grammar3BaseVisitor.h"
#include "Function.h"

using namespace std;
class Visitor : public Grammar3BaseVisitor
{
    public:
      virtual antlrcpp::Any visitProg(Grammar3Parser::ProgContext *ctx) override
      {
            return visitChildren(ctx);
      }

      virtual antlrcpp::Any visitMain(Grammar3Parser::MainContext *ctx) override
      {
            Declaration *decl;

            vector<Declaration *> *declList = new vector<Declaration *>(0);
            for (int i = 0; i < ctx->declaration().size(); i++)
            {
                  decl = (Declaration *)visit(ctx->declaration(i));
                  declList->push_back(decl);
            }
            Statement *stat;
            vector<Statement *> *statList = new vector<Statement *>(0);
            for (int i = 0; i < ctx->stat().size(); i++)
            {
                  stat = (Statement *)visit(ctx->stat(i));
                  statList->push_back(stat);
            }

            StatementReturn *rstat = (StatementReturn *)visit(ctx->rstat());

            return (Function *)new Function(declList, statList, rstat);
      }

      virtual antlrcpp::Any visitDecl(Grammar3Parser::DeclContext *ctx) override
      {

            ExpressionVar *var = new ExpressionVar(ctx->ID()->getText().c_str());

            return (Declaration *)new Declaration(var);
      }

      virtual antlrcpp::Any visitInit(Grammar3Parser::InitContext *ctx) override
      {

            Expression *right = visit(ctx->expr());
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());

            Declaration *declaration = new Declaration(left, right);
            return (Declaration *)declaration;
      }

      virtual antlrcpp::Any visitRstat(Grammar3Parser::RstatContext *ctx) override
      {
            Expression *val = (Expression *)visit(ctx->expr());
            return (StatementReturn *)new StatementReturn(val);
      }

      virtual antlrcpp::Any visitStat(Grammar3Parser::StatContext *ctx) override
      {
            ExpressionVar *left = new ExpressionVar(ctx->ID()->getText().c_str());
            Expression *right = (Expression *)visit(ctx->expr());

            return (Statement *)new Statement(left, right);
      }

      virtual antlrcpp::Any visitMultdiv(Grammar3Parser::MultdivContext *ctx) override
      {
            Expression *left = (Expression *)visit(ctx->expr(0));
            Expression *right = (Expression *)visit(ctx->expr(1));

            return (Expression *)new ExpressionMult(left, right);
      }

      virtual antlrcpp::Any visitPlusminus(Grammar3Parser::PlusminusContext *ctx) override
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

      virtual antlrcpp::Any visitConst(Grammar3Parser::ConstContext *ctx) override
      {
            ExpressionConst *val = new ExpressionConst((int)stoi(ctx->INT()->getText()));
            return (Expression *)val;
      }

      virtual antlrcpp::Any visitVar(Grammar3Parser::VarContext *ctx) override
      {
            return (Expression *)new ExpressionVar(ctx->ID()->getText().c_str());
      }

      virtual antlrcpp::Any visitPar(Grammar3Parser::ParContext *ctx) override
      {
            Expression *expression = (Expression *)visit(ctx->expr());
            return (Expression *)new ExpressionPar(expression);
      }
};
