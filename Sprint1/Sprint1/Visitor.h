#pragma once
#include "antlr4-runtime.h"
#include "Grammar1BaseVisitor.h"
using namespace std;
class Visitor : public Grammar1BaseVisitor
{
    public:
      virtual antlrcpp::Any visitProg(Grammar1Parser::ProgContext *ctx) override
      {
            return (int)visit(ctx->main());
      }

      virtual antlrcpp::Any visitMain(Grammar1Parser::MainContext *ctx) override
      {
            return (int)visit(ctx->body());
      }

      virtual antlrcpp::Any visitBody(Grammar1Parser::BodyContext *ctx) override
      {
            return (int)atoi(ctx->INT()->getText().c_str());
      }
};