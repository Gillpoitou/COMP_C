
// Generated from Sprint2/Grammar2.g4 by ANTLR 4.7.2


#include "Grammar2Visitor.h"

#include "Grammar2Parser.h"


using namespace antlrcpp;
using namespace antlr4;

Grammar2Parser::Grammar2Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

Grammar2Parser::~Grammar2Parser() {
  delete _interpreter;
}

std::string Grammar2Parser::getGrammarFileName() const {
  return "Grammar2.g4";
}

const std::vector<std::string>& Grammar2Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& Grammar2Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

Grammar2Parser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::MainContext* Grammar2Parser::ProgContext::main() {
  return getRuleContext<Grammar2Parser::MainContext>(0);
}


size_t Grammar2Parser::ProgContext::getRuleIndex() const {
  return Grammar2Parser::RuleProg;
}


antlrcpp::Any Grammar2Parser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::ProgContext* Grammar2Parser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, Grammar2Parser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
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

Grammar2Parser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::TnameContext* Grammar2Parser::MainContext::tname() {
  return getRuleContext<Grammar2Parser::TnameContext>(0);
}

Grammar2Parser::BodyContext* Grammar2Parser::MainContext::body() {
  return getRuleContext<Grammar2Parser::BodyContext>(0);
}


size_t Grammar2Parser::MainContext::getRuleIndex() const {
  return Grammar2Parser::RuleMain;
}


antlrcpp::Any Grammar2Parser::MainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitMain(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::MainContext* Grammar2Parser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 2, Grammar2Parser::RuleMain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    tname();
    setState(19);
    match(Grammar2Parser::T__0);
    setState(20);
    match(Grammar2Parser::T__1);
    setState(21);
    match(Grammar2Parser::T__2);
    setState(22);
    match(Grammar2Parser::T__3);
    setState(23);
    body();
    setState(24);
    match(Grammar2Parser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TnameContext ------------------------------------------------------------------

Grammar2Parser::TnameContext::TnameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t Grammar2Parser::TnameContext::getRuleIndex() const {
  return Grammar2Parser::RuleTname;
}


antlrcpp::Any Grammar2Parser::TnameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitTname(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::TnameContext* Grammar2Parser::tname() {
  TnameContext *_localctx = _tracker.createInstance<TnameContext>(_ctx, getState());
  enterRule(_localctx, 4, Grammar2Parser::RuleTname);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(26);
    match(Grammar2Parser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

Grammar2Parser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::StatsContext* Grammar2Parser::BodyContext::stats() {
  return getRuleContext<Grammar2Parser::StatsContext>(0);
}

Grammar2Parser::RstatContext* Grammar2Parser::BodyContext::rstat() {
  return getRuleContext<Grammar2Parser::RstatContext>(0);
}


size_t Grammar2Parser::BodyContext::getRuleIndex() const {
  return Grammar2Parser::RuleBody;
}


antlrcpp::Any Grammar2Parser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::BodyContext* Grammar2Parser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 6, Grammar2Parser::RuleBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    stats();
    setState(29);
    rstat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RstatContext ------------------------------------------------------------------

Grammar2Parser::RstatContext::RstatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t Grammar2Parser::RstatContext::getRuleIndex() const {
  return Grammar2Parser::RuleRstat;
}

void Grammar2Parser::RstatContext::copyFrom(RstatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RetIntContext ------------------------------------------------------------------

tree::TerminalNode* Grammar2Parser::RetIntContext::INT() {
  return getToken(Grammar2Parser::INT, 0);
}

Grammar2Parser::RetIntContext::RetIntContext(RstatContext *ctx) { copyFrom(ctx); }


antlrcpp::Any Grammar2Parser::RetIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitRetInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RetVarContext ------------------------------------------------------------------

tree::TerminalNode* Grammar2Parser::RetVarContext::ID() {
  return getToken(Grammar2Parser::ID, 0);
}

Grammar2Parser::RetVarContext::RetVarContext(RstatContext *ctx) { copyFrom(ctx); }


antlrcpp::Any Grammar2Parser::RetVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitRetVar(this);
  else
    return visitor->visitChildren(this);
}
Grammar2Parser::RstatContext* Grammar2Parser::rstat() {
  RstatContext *_localctx = _tracker.createInstance<RstatContext>(_ctx, getState());
  enterRule(_localctx, 8, Grammar2Parser::RuleRstat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(37);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<RstatContext *>(_tracker.createInstance<Grammar2Parser::RetIntContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(31);
      match(Grammar2Parser::T__5);
      setState(32);
      match(Grammar2Parser::INT);
      setState(33);
      match(Grammar2Parser::T__6);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<RstatContext *>(_tracker.createInstance<Grammar2Parser::RetVarContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(34);
      match(Grammar2Parser::T__5);
      setState(35);
      match(Grammar2Parser::ID);
      setState(36);
      match(Grammar2Parser::T__6);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatsContext ------------------------------------------------------------------

Grammar2Parser::StatsContext::StatsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::StatContext* Grammar2Parser::StatsContext::stat() {
  return getRuleContext<Grammar2Parser::StatContext>(0);
}

Grammar2Parser::StatsContext* Grammar2Parser::StatsContext::stats() {
  return getRuleContext<Grammar2Parser::StatsContext>(0);
}


size_t Grammar2Parser::StatsContext::getRuleIndex() const {
  return Grammar2Parser::RuleStats;
}


antlrcpp::Any Grammar2Parser::StatsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitStats(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::StatsContext* Grammar2Parser::stats() {
  StatsContext *_localctx = _tracker.createInstance<StatsContext>(_ctx, getState());
  enterRule(_localctx, 10, Grammar2Parser::RuleStats);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(43);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar2Parser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(39);
        stat();
        setState(40);
        stats();
        break;
      }

      case Grammar2Parser::T__5: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

Grammar2Parser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::DeclarationContext* Grammar2Parser::StatContext::declaration() {
  return getRuleContext<Grammar2Parser::DeclarationContext>(0);
}


size_t Grammar2Parser::StatContext::getRuleIndex() const {
  return Grammar2Parser::RuleStat;
}


antlrcpp::Any Grammar2Parser::StatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitStat(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::StatContext* Grammar2Parser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 12, Grammar2Parser::RuleStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    declaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

Grammar2Parser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar2Parser::TnameContext* Grammar2Parser::DeclarationContext::tname() {
  return getRuleContext<Grammar2Parser::TnameContext>(0);
}

tree::TerminalNode* Grammar2Parser::DeclarationContext::ID() {
  return getToken(Grammar2Parser::ID, 0);
}

tree::TerminalNode* Grammar2Parser::DeclarationContext::INT() {
  return getToken(Grammar2Parser::INT, 0);
}


size_t Grammar2Parser::DeclarationContext::getRuleIndex() const {
  return Grammar2Parser::RuleDeclaration;
}


antlrcpp::Any Grammar2Parser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Grammar2Visitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

Grammar2Parser::DeclarationContext* Grammar2Parser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, Grammar2Parser::RuleDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    tname();
    setState(48);
    match(Grammar2Parser::ID);
    setState(49);
    match(Grammar2Parser::T__7);
    setState(50);
    match(Grammar2Parser::INT);
    setState(51);
    match(Grammar2Parser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> Grammar2Parser::_decisionToDFA;
atn::PredictionContextCache Grammar2Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN Grammar2Parser::_atn;
std::vector<uint16_t> Grammar2Parser::_serializedATN;

std::vector<std::string> Grammar2Parser::_ruleNames = {
  "prog", "main", "tname", "body", "rstat", "stats", "stat", "declaration"
};

std::vector<std::string> Grammar2Parser::_literalNames = {
  "", "'main'", "'('", "')'", "'{'", "'int'", "'return'", "';'", "'='"
};

std::vector<std::string> Grammar2Parser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INT", "ID"
};

dfa::Vocabulary Grammar2Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> Grammar2Parser::_tokenNames;

Grammar2Parser::Initializer::Initializer() {
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
    0x3, 0xc, 0x38, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x28, 0xa, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x2e, 0xa, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x2, 0x2, 0xa, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x2, 0x2, 
    0x2, 0x31, 0x2, 0x12, 0x3, 0x2, 0x2, 0x2, 0x4, 0x14, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x8, 0x1e, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xe, 0x2f, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x31, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x5, 
    0x4, 0x3, 0x2, 0x13, 0x3, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x5, 0x6, 
    0x4, 0x2, 0x15, 0x16, 0x7, 0x3, 0x2, 0x2, 0x16, 0x17, 0x7, 0x4, 0x2, 
    0x2, 0x17, 0x18, 0x7, 0x5, 0x2, 0x2, 0x18, 0x19, 0x7, 0x6, 0x2, 0x2, 
    0x19, 0x1a, 0x5, 0x8, 0x5, 0x2, 0x1a, 0x1b, 0x7, 0x5, 0x2, 0x2, 0x1b, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x7, 0x7, 0x2, 0x2, 0x1d, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x5, 0xc, 0x7, 0x2, 0x1f, 0x20, 0x5, 
    0xa, 0x6, 0x2, 0x20, 0x9, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 0x8, 
    0x2, 0x2, 0x22, 0x23, 0x7, 0xb, 0x2, 0x2, 0x23, 0x28, 0x7, 0x9, 0x2, 
    0x2, 0x24, 0x25, 0x7, 0x8, 0x2, 0x2, 0x25, 0x26, 0x7, 0xc, 0x2, 0x2, 
    0x26, 0x28, 0x7, 0x9, 0x2, 0x2, 0x27, 0x21, 0x3, 0x2, 0x2, 0x2, 0x27, 
    0x24, 0x3, 0x2, 0x2, 0x2, 0x28, 0xb, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 
    0x5, 0xe, 0x8, 0x2, 0x2a, 0x2b, 0x5, 0xc, 0x7, 0x2, 0x2b, 0x2e, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0x2d, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x2f, 0x30, 0x5, 0x10, 0x9, 0x2, 0x30, 0xf, 0x3, 0x2, 0x2, 0x2, 
    0x31, 0x32, 0x5, 0x6, 0x4, 0x2, 0x32, 0x33, 0x7, 0xc, 0x2, 0x2, 0x33, 
    0x34, 0x7, 0xa, 0x2, 0x2, 0x34, 0x35, 0x7, 0xb, 0x2, 0x2, 0x35, 0x36, 
    0x7, 0x9, 0x2, 0x2, 0x36, 0x11, 0x3, 0x2, 0x2, 0x2, 0x4, 0x27, 0x2d, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

Grammar2Parser::Initializer Grammar2Parser::_init;
