
// Generated from Sprint2/Grammar2.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar2Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Grammar2Parser.
 */
class  Grammar2Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Grammar2Parser.
   */
    virtual antlrcpp::Any visitProg(Grammar2Parser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitMain(Grammar2Parser::MainContext *context) = 0;

    virtual antlrcpp::Any visitTname(Grammar2Parser::TnameContext *context) = 0;

    virtual antlrcpp::Any visitBody(Grammar2Parser::BodyContext *context) = 0;

    virtual antlrcpp::Any visitRetInt(Grammar2Parser::RetIntContext *context) = 0;

    virtual antlrcpp::Any visitRetVar(Grammar2Parser::RetVarContext *context) = 0;

    virtual antlrcpp::Any visitStats(Grammar2Parser::StatsContext *context) = 0;

    virtual antlrcpp::Any visitStat(Grammar2Parser::StatContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(Grammar2Parser::DeclarationContext *context) = 0;


};

