
// Generated from Sprint1/Grammar1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar1Visitor.h"


/**
 * This class provides an empty implementation of Grammar1Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Grammar1BaseVisitor : public Grammar1Visitor {
public:

  virtual antlrcpp::Any visitProg(Grammar1Parser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMain(Grammar1Parser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTname(Grammar1Parser::TnameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBody(Grammar1Parser::BodyContext *ctx) override {
    return visitChildren(ctx);
  }


};

