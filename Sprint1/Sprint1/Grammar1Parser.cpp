
// Generated from Sprint1/Grammar1.g4 by ANTLR 4.7.2


#include "Grammar1Visitor.h"

#include "Grammar1Parser.h"


using namespace antlrcpp;
using namespace antlr4;

Grammar1Parser::Grammar1Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

Grammar1Parser::~Grammar1Parser() {
  delete _interpreter;
}

std::string Grammar1Parser::getGrammarFileName() const {
  return "Grammar1.g4";
}

const std::vector<std::string>& Grammar1Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& Grammar1Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

Grammar1Parser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar1Parser::MainContext* Grammar1Parser::ProgContext::main() {
  return getRuleContext<Grammar1Parser::MainContext>(0);
}


size_t Grammar1Parser::ProgContext::getRuleIndex() const {
  return Grammar1Parser::RuleProg;
}


antlrcpp::Any Grammar1Parser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar1Visitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

Grammar1Parser::ProgContext* Grammar1Parser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, Grammar1Parser::RuleProg);

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

Grammar1Parser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar1Parser::TnameContext* Grammar1Parser::MainContext::tname() {
  return getRuleContext<Grammar1Parser::TnameContext>(0);
}

Grammar1Parser::BodyContext* Grammar1Parser::MainContext::body() {
  return getRuleContext<Grammar1Parser::BodyContext>(0);
}


size_t Grammar1Parser::MainContext::getRuleIndex() const {
  return Grammar1Parser::RuleMain;
}


antlrcpp::Any Grammar1Parser::MainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar1Visitor*>(visitor))
    return parserVisitor->visitMain(this);
  else
    return visitor->visitChildren(this);
}

Grammar1Parser::MainContext* Grammar1Parser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 2, Grammar1Parser::RuleMain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    tname();
    setState(11);
    match(Grammar1Parser::T__0);
    setState(12);
    match(Grammar1Parser::T__1);
    setState(13);
    match(Grammar1Parser::T__2);
    setState(14);
    match(Grammar1Parser::T__3);
    setState(15);
    body();
    setState(16);
    match(Grammar1Parser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TnameContext ------------------------------------------------------------------

Grammar1Parser::TnameContext::TnameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t Grammar1Parser::TnameContext::getRuleIndex() const {
  return Grammar1Parser::RuleTname;
}


antlrcpp::Any Grammar1Parser::TnameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar1Visitor*>(visitor))
    return parserVisitor->visitTname(this);
  else
    return visitor->visitChildren(this);
}

Grammar1Parser::TnameContext* Grammar1Parser::tname() {
  TnameContext *_localctx = _tracker.createInstance<TnameContext>(_ctx, getState());
  enterRule(_localctx, 4, Grammar1Parser::RuleTname);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(Grammar1Parser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

Grammar1Parser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar1Parser::BodyContext::INT() {
  return getToken(Grammar1Parser::INT, 0);
}


size_t Grammar1Parser::BodyContext::getRuleIndex() const {
  return Grammar1Parser::RuleBody;
}


antlrcpp::Any Grammar1Parser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar1Visitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

Grammar1Parser::BodyContext* Grammar1Parser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 6, Grammar1Parser::RuleBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(Grammar1Parser::T__6);
    setState(21);
    match(Grammar1Parser::INT);
    setState(22);
    match(Grammar1Parser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> Grammar1Parser::_decisionToDFA;
atn::PredictionContextCache Grammar1Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN Grammar1Parser::_atn;
std::vector<uint16_t> Grammar1Parser::_serializedATN;

std::vector<std::string> Grammar1Parser::_ruleNames = {
  "prog", "main", "tname", "body"
};

std::vector<std::string> Grammar1Parser::_literalNames = {
  "", "'main'", "'('", "')'", "'{'", "'}'", "'int'", "'return'", "';'"
};

std::vector<std::string> Grammar1Parser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INT", "WS"
};

dfa::Vocabulary Grammar1Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> Grammar1Parser::_tokenNames;

Grammar1Parser::Initializer::Initializer() {
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

Grammar1Parser::Initializer Grammar1Parser::_init;
