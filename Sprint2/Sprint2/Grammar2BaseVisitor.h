
// Generated from Sprint2/Grammar2.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar2Visitor.h"


/**
 * This class provides an empty implementation of Grammar2Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Grammar2BaseVisitor : public Grammar2Visitor {
public:

  virtual antlrcpp::Any visitProg(Grammar2Parser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMain(Grammar2Parser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTname(Grammar2Parser::TnameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBody(Grammar2Parser::BodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRetInt(Grammar2Parser::RetIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRetVar(Grammar2Parser::RetVarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStats(Grammar2Parser::StatsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStat(Grammar2Parser::StatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(Grammar2Parser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }


};

