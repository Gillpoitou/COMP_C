
// Generated from Sprint1/Grammar1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar1Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Grammar1Parser.
 */
class  Grammar1Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Grammar1Parser.
   */
    virtual antlrcpp::Any visitProg(Grammar1Parser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitMain(Grammar1Parser::MainContext *context) = 0;

    virtual antlrcpp::Any visitTname(Grammar1Parser::TnameContext *context) = 0;

    virtual antlrcpp::Any visitBody(Grammar1Parser::BodyContext *context) = 0;


};

