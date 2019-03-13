#pragma once
#include "antlr4-runtime.h"
#include "Sprint1BaseVisitor.h"
using namespace std;
class Visitor : public Sprint1BaseVisitor
{
    public:
      virtual antlrcpp::Any visitProg(Sprint1Parser::ProgContext *ctx) override
      {
            return (int)visit(ctx->main());
      }

      virtual antlrcpp::Any visitMain(Sprint1Parser::MainContext *ctx) override
      {
            return (int)visit(ctx->body());
      }

      virtual antlrcpp::Any visitBody(Sprint1Parser::BodyContext *ctx) override
      {
            return (int)atoi(ctx->INT()->getText().c_str());
      }
};