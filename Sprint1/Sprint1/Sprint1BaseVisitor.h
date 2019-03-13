
// Generated from Sprint1/Sprint1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Sprint1Visitor.h"


/**
 * This class provides an empty implementation of Sprint1Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Sprint1BaseVisitor : public Sprint1Visitor {
public:

  virtual antlrcpp::Any visitProg(Sprint1Parser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMain(Sprint1Parser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTname(Sprint1Parser::TnameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBody(Sprint1Parser::BodyContext *ctx) override {
    return visitChildren(ctx);
  }


};

