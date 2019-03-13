
// Generated from Sprint1/Sprint1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "Sprint1Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Sprint1Parser.
 */
class  Sprint1Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Sprint1Parser.
   */
    virtual antlrcpp::Any visitProg(Sprint1Parser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitMain(Sprint1Parser::MainContext *context) = 0;

    virtual antlrcpp::Any visitTname(Sprint1Parser::TnameContext *context) = 0;

    virtual antlrcpp::Any visitBody(Sprint1Parser::BodyContext *context) = 0;


};

