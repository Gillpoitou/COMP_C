
// Generated from Sprint1/Sprint1.g4 by ANTLR 4.7.2


#include "Sprint1Visitor.h"

#include "Sprint1Parser.h"


using namespace antlrcpp;
using namespace antlr4;

Sprint1Parser::Sprint1Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

Sprint1Parser::~Sprint1Parser() {
  delete _interpreter;
}

std::string Sprint1Parser::getGrammarFileName() const {
  return "Sprint1.g4";
}

const std::vector<std::string>& Sprint1Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& Sprint1Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

Sprint1Parser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sprint1Parser::MainContext* Sprint1Parser::ProgContext::main() {
  return getRuleContext<Sprint1Parser::MainContext>(0);
}


size_t Sprint1Parser::ProgContext::getRuleIndex() const {
  return Sprint1Parser::RuleProg;
}


antlrcpp::Any Sprint1Parser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sprint1Visitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

Sprint1Parser::ProgContext* Sprint1Parser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, Sprint1Parser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(8);
    main();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MainContext ------------------------------------------------------------------

Sprint1Parser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sprint1Parser::TnameContext* Sprint1Parser::MainContext::tname() {
  return getRuleContext<Sprint1Parser::TnameContext>(0);
}

Sprint1Parser::BodyContext* Sprint1Parser::MainContext::body() {
  return getRuleContext<Sprint1Parser::BodyContext>(0);
}


size_t Sprint1Parser::MainContext::getRuleIndex() const {
  return Sprint1Parser::RuleMain;
}


antlrcpp::Any Sprint1Parser::MainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sprint1Visitor*>(visitor))
    return parserVisitor->visitMain(this);
  else
    return visitor->visitChildren(this);
}

Sprint1Parser::MainContext* Sprint1Parser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 2, Sprint1Parser::RuleMain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    tname();
    setState(11);
    match(Sprint1Parser::T__0);
    setState(12);
    match(Sprint1Parser::T__1);
    setState(13);
    match(Sprint1Parser::T__2);
    setState(14);
    match(Sprint1Parser::T__3);
    setState(15);
    body();
    setState(16);
    match(Sprint1Parser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TnameContext ------------------------------------------------------------------

Sprint1Parser::TnameContext::TnameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t Sprint1Parser::TnameContext::getRuleIndex() const {
  return Sprint1Parser::RuleTname;
}


antlrcpp::Any Sprint1Parser::TnameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sprint1Visitor*>(visitor))
    return parserVisitor->visitTname(this);
  else
    return visitor->visitChildren(this);
}

Sprint1Parser::TnameContext* Sprint1Parser::tname() {
  TnameContext *_localctx = _tracker.createInstance<TnameContext>(_ctx, getState());
  enterRule(_localctx, 4, Sprint1Parser::RuleTname);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(Sprint1Parser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

Sprint1Parser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sprint1Parser::BodyContext::INT() {
  return getToken(Sprint1Parser::INT, 0);
}


size_t Sprint1Parser::BodyContext::getRuleIndex() const {
  return Sprint1Parser::RuleBody;
}


antlrcpp::Any Sprint1Parser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sprint1Visitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

Sprint1Parser::BodyContext* Sprint1Parser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 6, Sprint1Parser::RuleBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(Sprint1Parser::T__6);
    setState(21);
    match(Sprint1Parser::INT);
    setState(22);
    match(Sprint1Parser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> Sprint1Parser::_decisionToDFA;
atn::PredictionContextCache Sprint1Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN Sprint1Parser::_atn;
std::vector<uint16_t> Sprint1Parser::_serializedATN;

std::vector<std::string> Sprint1Parser::_ruleNames = {
  "prog", "main", "tname", "body"
};

std::vector<std::string> Sprint1Parser::_literalNames = {
  "", "'main'", "'('", "')'", "'{'", "'}'", "'int'", "'return'", "';'"
};

std::vector<std::string> Sprint1Parser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INT", "WS"
};

dfa::Vocabulary Sprint1Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> Sprint1Parser::_tokenNames;

Sprint1Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xc, 0x1b, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x2, 0x2, 0x6, 
    0x2, 0x4, 0x6, 0x8, 0x2, 0x2, 0x2, 0x16, 0x2, 0xa, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0xc, 0x3, 0x2, 0x2, 0x2, 0x6, 0x14, 0x3, 0x2, 0x2, 0x2, 0x8, 0x16, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0xb, 0x5, 0x4, 0x3, 0x2, 0xb, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0xd, 0x5, 0x6, 0x4, 0x2, 0xd, 0xe, 0x7, 0x3, 0x2, 0x2, 
    0xe, 0xf, 0x7, 0x4, 0x2, 0x2, 0xf, 0x10, 0x7, 0x5, 0x2, 0x2, 0x10, 0x11, 
    0x7, 0x6, 0x2, 0x2, 0x11, 0x12, 0x5, 0x8, 0x5, 0x2, 0x12, 0x13, 0x7, 
    0x7, 0x2, 0x2, 0x13, 0x5, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x7, 0x8, 
    0x2, 0x2, 0x15, 0x7, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x7, 0x9, 0x2, 
    0x2, 0x17, 0x18, 0x7, 0xb, 0x2, 0x2, 0x18, 0x19, 0x7, 0xa, 0x2, 0x2, 
    0x19, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

Sprint1Parser::Initializer Sprint1Parser::_init;
