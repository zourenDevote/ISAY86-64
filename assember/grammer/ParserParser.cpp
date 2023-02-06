
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1


#include "ParserListener.h"
#include "ParserVisitor.h"

#include "ParserParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ParserParserStaticData final {
  ParserParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ParserParserStaticData(const ParserParserStaticData&) = delete;
  ParserParserStaticData(ParserParserStaticData&&) = delete;
  ParserParserStaticData& operator=(const ParserParserStaticData&) = delete;
  ParserParserStaticData& operator=(ParserParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag parserParserOnceFlag;
ParserParserStaticData *parserParserStaticData = nullptr;

void parserParserInitialize() {
  assert(parserParserStaticData == nullptr);
  auto staticData = std::make_unique<ParserParserStaticData>(
    std::vector<std::string>{
      "code", "stmt", "assemblyinst", "inst", "operand", "quaddecl", "filldecl", 
      "posdecl", "maindecl", "stackdecl", "labeldecl"
    },
    std::vector<std::string>{
      "", "','", "':'", "'.pos'", "'.fill'", "'.main'", "'.quad'", "'.stack'", 
      "'halt'", "'nop'", "'rrmovq'", "'irmovq'", "'rmmovq'", "'mrmovq'", 
      "'addq'", "'subq'", "'andq'", "'xorq'", "'jmp'", "'jle'", "'jl'", 
      "'je'", "'jne'", "'jqe'", "'jq'", "'cmovle'", "'cmovl'", "'cmove'", 
      "'cmovne'", "'cmovge'", "'cmovg'", "'call'", "'ret'", "'pushq'", "'popq'", 
      "'rax'", "'rcx'", "'rbx'", "'rsp'", "'rbp'", "'rsi'", "'rdi'", "'r8'", 
      "'r9'", "'r10'", "'r11'", "'r12'", "'r13'", "'r14'"
    },
    std::vector<std::string>{
      "", "", "", "POS", "FILL", "MAIN", "QUAD", "STACK", "MHALT", "MNOP", 
      "MRRMOVQ", "MIRMOVQ", "MRMMOVQ", "MMRMOVQ", "MADDQ", "MSUBQ", "MANDQ", 
      "MXORQ", "MJMP", "MJLE", "MJL", "MJE", "MJNE", "MJQE", "MJQ", "MCMOVLE", 
      "MCMOVL", "MCMOVE", "MCMOVNE", "MCMOVGE", "MCMOVG", "MCALL", "MRET", 
      "MPUSHQ", "MPOPQ", "MRAX", "MRCX", "MRBX", "MRSP", "MRBP", "MRSI", 
      "MRDI", "MR8", "MR9", "MR10", "MR11", "MR12", "MR13", "MR14", "NUMBER", 
      "LABEL", "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,52,78,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,5,0,24,8,0,10,0,12,0,27,9,0,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,3,1,36,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,47,8,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,5,5,57,8,5,10,5,12,5,60,9,5,
  	1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,
  	10,0,0,11,0,2,4,6,8,10,12,14,16,18,20,0,2,1,0,8,34,1,0,35,50,76,0,25,
  	1,0,0,0,2,35,1,0,0,0,4,46,1,0,0,0,6,48,1,0,0,0,8,50,1,0,0,0,10,52,1,0,
  	0,0,12,61,1,0,0,0,14,65,1,0,0,0,16,68,1,0,0,0,18,70,1,0,0,0,20,74,1,0,
  	0,0,22,24,3,2,1,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,0,25,26,1,0,
  	0,0,26,1,1,0,0,0,27,25,1,0,0,0,28,36,3,4,2,0,29,36,3,10,5,0,30,36,3,12,
  	6,0,31,36,3,14,7,0,32,36,3,16,8,0,33,36,3,18,9,0,34,36,3,20,10,0,35,28,
  	1,0,0,0,35,29,1,0,0,0,35,30,1,0,0,0,35,31,1,0,0,0,35,32,1,0,0,0,35,33,
  	1,0,0,0,35,34,1,0,0,0,36,3,1,0,0,0,37,47,3,6,3,0,38,39,3,6,3,0,39,40,
  	3,8,4,0,40,47,1,0,0,0,41,42,3,6,3,0,42,43,3,8,4,0,43,44,5,1,0,0,44,45,
  	3,8,4,0,45,47,1,0,0,0,46,37,1,0,0,0,46,38,1,0,0,0,46,41,1,0,0,0,47,5,
  	1,0,0,0,48,49,7,0,0,0,49,7,1,0,0,0,50,51,7,1,0,0,51,9,1,0,0,0,52,53,5,
  	6,0,0,53,58,5,49,0,0,54,55,5,1,0,0,55,57,5,49,0,0,56,54,1,0,0,0,57,60,
  	1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,0,59,11,1,0,0,0,60,58,1,0,0,0,61,62,
  	5,4,0,0,62,63,5,49,0,0,63,64,5,49,0,0,64,13,1,0,0,0,65,66,5,3,0,0,66,
  	67,5,49,0,0,67,15,1,0,0,0,68,69,5,5,0,0,69,17,1,0,0,0,70,71,5,7,0,0,71,
  	72,5,49,0,0,72,73,5,49,0,0,73,19,1,0,0,0,74,75,5,50,0,0,75,76,5,2,0,0,
  	76,21,1,0,0,0,4,25,35,46,58
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  parserParserStaticData = staticData.release();
}

}

ParserParser::ParserParser(TokenStream *input) : ParserParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ParserParser::ParserParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ParserParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *parserParserStaticData->atn, parserParserStaticData->decisionToDFA, parserParserStaticData->sharedContextCache, options);
}

ParserParser::~ParserParser() {
  delete _interpreter;
}

const atn::ATN& ParserParser::getATN() const {
  return *parserParserStaticData->atn;
}

std::string ParserParser::getGrammarFileName() const {
  return "Parser.g4";
}

const std::vector<std::string>& ParserParser::getRuleNames() const {
  return parserParserStaticData->ruleNames;
}

const dfa::Vocabulary& ParserParser::getVocabulary() const {
  return parserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ParserParser::getSerializedATN() const {
  return parserParserStaticData->serializedATN;
}


//----------------- CodeContext ------------------------------------------------------------------

ParserParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ParserParser::StmtContext *> ParserParser::CodeContext::stmt() {
  return getRuleContexts<ParserParser::StmtContext>();
}

ParserParser::StmtContext* ParserParser::CodeContext::stmt(size_t i) {
  return getRuleContext<ParserParser::StmtContext>(i);
}


size_t ParserParser::CodeContext::getRuleIndex() const {
  return ParserParser::RuleCode;
}

void ParserParser::CodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode(this);
}

void ParserParser::CodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode(this);
}


std::any ParserParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::CodeContext* ParserParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 0, ParserParser::RuleCode);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1125934266580984) != 0) {
      setState(22);
      stmt();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

ParserParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ParserParser::AssemblyinstContext* ParserParser::StmtContext::assemblyinst() {
  return getRuleContext<ParserParser::AssemblyinstContext>(0);
}

ParserParser::QuaddeclContext* ParserParser::StmtContext::quaddecl() {
  return getRuleContext<ParserParser::QuaddeclContext>(0);
}

ParserParser::FilldeclContext* ParserParser::StmtContext::filldecl() {
  return getRuleContext<ParserParser::FilldeclContext>(0);
}

ParserParser::PosdeclContext* ParserParser::StmtContext::posdecl() {
  return getRuleContext<ParserParser::PosdeclContext>(0);
}

ParserParser::MaindeclContext* ParserParser::StmtContext::maindecl() {
  return getRuleContext<ParserParser::MaindeclContext>(0);
}

ParserParser::StackdeclContext* ParserParser::StmtContext::stackdecl() {
  return getRuleContext<ParserParser::StackdeclContext>(0);
}

ParserParser::LabeldeclContext* ParserParser::StmtContext::labeldecl() {
  return getRuleContext<ParserParser::LabeldeclContext>(0);
}


size_t ParserParser::StmtContext::getRuleIndex() const {
  return ParserParser::RuleStmt;
}

void ParserParser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void ParserParser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}


std::any ParserParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::StmtContext* ParserParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 2, ParserParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ParserParser::MHALT:
      case ParserParser::MNOP:
      case ParserParser::MRRMOVQ:
      case ParserParser::MIRMOVQ:
      case ParserParser::MRMMOVQ:
      case ParserParser::MMRMOVQ:
      case ParserParser::MADDQ:
      case ParserParser::MSUBQ:
      case ParserParser::MANDQ:
      case ParserParser::MXORQ:
      case ParserParser::MJMP:
      case ParserParser::MJLE:
      case ParserParser::MJL:
      case ParserParser::MJE:
      case ParserParser::MJNE:
      case ParserParser::MJQE:
      case ParserParser::MJQ:
      case ParserParser::MCMOVLE:
      case ParserParser::MCMOVL:
      case ParserParser::MCMOVE:
      case ParserParser::MCMOVNE:
      case ParserParser::MCMOVGE:
      case ParserParser::MCMOVG:
      case ParserParser::MCALL:
      case ParserParser::MRET:
      case ParserParser::MPUSHQ:
      case ParserParser::MPOPQ: {
        setState(28);
        assemblyinst();
        break;
      }

      case ParserParser::QUAD: {
        setState(29);
        quaddecl();
        break;
      }

      case ParserParser::FILL: {
        setState(30);
        filldecl();
        break;
      }

      case ParserParser::POS: {
        setState(31);
        posdecl();
        break;
      }

      case ParserParser::MAIN: {
        setState(32);
        maindecl();
        break;
      }

      case ParserParser::STACK: {
        setState(33);
        stackdecl();
        break;
      }

      case ParserParser::LABEL: {
        setState(34);
        labeldecl();
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

//----------------- AssemblyinstContext ------------------------------------------------------------------

ParserParser::AssemblyinstContext::AssemblyinstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ParserParser::InstContext* ParserParser::AssemblyinstContext::inst() {
  return getRuleContext<ParserParser::InstContext>(0);
}

std::vector<ParserParser::OperandContext *> ParserParser::AssemblyinstContext::operand() {
  return getRuleContexts<ParserParser::OperandContext>();
}

ParserParser::OperandContext* ParserParser::AssemblyinstContext::operand(size_t i) {
  return getRuleContext<ParserParser::OperandContext>(i);
}


size_t ParserParser::AssemblyinstContext::getRuleIndex() const {
  return ParserParser::RuleAssemblyinst;
}

void ParserParser::AssemblyinstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssemblyinst(this);
}

void ParserParser::AssemblyinstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssemblyinst(this);
}


std::any ParserParser::AssemblyinstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitAssemblyinst(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::AssemblyinstContext* ParserParser::assemblyinst() {
  AssemblyinstContext *_localctx = _tracker.createInstance<AssemblyinstContext>(_ctx, getState());
  enterRule(_localctx, 4, ParserParser::RuleAssemblyinst);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(46);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(37);
      inst();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(38);
      inst();
      setState(39);
      operand();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(41);
      inst();
      setState(42);
      operand();
      setState(43);
      match(ParserParser::T__0);
      setState(44);
      operand();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstContext ------------------------------------------------------------------

ParserParser::InstContext::InstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::InstContext::MHALT() {
  return getToken(ParserParser::MHALT, 0);
}

tree::TerminalNode* ParserParser::InstContext::MNOP() {
  return getToken(ParserParser::MNOP, 0);
}

tree::TerminalNode* ParserParser::InstContext::MRRMOVQ() {
  return getToken(ParserParser::MRRMOVQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MIRMOVQ() {
  return getToken(ParserParser::MIRMOVQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MMRMOVQ() {
  return getToken(ParserParser::MMRMOVQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MRMMOVQ() {
  return getToken(ParserParser::MRMMOVQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MADDQ() {
  return getToken(ParserParser::MADDQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MSUBQ() {
  return getToken(ParserParser::MSUBQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MANDQ() {
  return getToken(ParserParser::MANDQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MXORQ() {
  return getToken(ParserParser::MXORQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJMP() {
  return getToken(ParserParser::MJMP, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJLE() {
  return getToken(ParserParser::MJLE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJL() {
  return getToken(ParserParser::MJL, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJE() {
  return getToken(ParserParser::MJE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJNE() {
  return getToken(ParserParser::MJNE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJQE() {
  return getToken(ParserParser::MJQE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MJQ() {
  return getToken(ParserParser::MJQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVLE() {
  return getToken(ParserParser::MCMOVLE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVL() {
  return getToken(ParserParser::MCMOVL, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVE() {
  return getToken(ParserParser::MCMOVE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVNE() {
  return getToken(ParserParser::MCMOVNE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVGE() {
  return getToken(ParserParser::MCMOVGE, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCMOVG() {
  return getToken(ParserParser::MCMOVG, 0);
}

tree::TerminalNode* ParserParser::InstContext::MCALL() {
  return getToken(ParserParser::MCALL, 0);
}

tree::TerminalNode* ParserParser::InstContext::MRET() {
  return getToken(ParserParser::MRET, 0);
}

tree::TerminalNode* ParserParser::InstContext::MPUSHQ() {
  return getToken(ParserParser::MPUSHQ, 0);
}

tree::TerminalNode* ParserParser::InstContext::MPOPQ() {
  return getToken(ParserParser::MPOPQ, 0);
}


size_t ParserParser::InstContext::getRuleIndex() const {
  return ParserParser::RuleInst;
}

void ParserParser::InstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInst(this);
}

void ParserParser::InstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInst(this);
}


std::any ParserParser::InstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitInst(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::InstContext* ParserParser::inst() {
  InstContext *_localctx = _tracker.createInstance<InstContext>(_ctx, getState());
  enterRule(_localctx, 6, ParserParser::RuleInst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34359738112) != 0)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandContext ------------------------------------------------------------------

ParserParser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::OperandContext::MRAX() {
  return getToken(ParserParser::MRAX, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRCX() {
  return getToken(ParserParser::MRCX, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRBX() {
  return getToken(ParserParser::MRBX, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRSP() {
  return getToken(ParserParser::MRSP, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRBP() {
  return getToken(ParserParser::MRBP, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRSI() {
  return getToken(ParserParser::MRSI, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MRDI() {
  return getToken(ParserParser::MRDI, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR8() {
  return getToken(ParserParser::MR8, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR9() {
  return getToken(ParserParser::MR9, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR10() {
  return getToken(ParserParser::MR10, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR11() {
  return getToken(ParserParser::MR11, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR12() {
  return getToken(ParserParser::MR12, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR13() {
  return getToken(ParserParser::MR13, 0);
}

tree::TerminalNode* ParserParser::OperandContext::MR14() {
  return getToken(ParserParser::MR14, 0);
}

tree::TerminalNode* ParserParser::OperandContext::LABEL() {
  return getToken(ParserParser::LABEL, 0);
}

tree::TerminalNode* ParserParser::OperandContext::NUMBER() {
  return getToken(ParserParser::NUMBER, 0);
}


size_t ParserParser::OperandContext::getRuleIndex() const {
  return ParserParser::RuleOperand;
}

void ParserParser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void ParserParser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}


std::any ParserParser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::OperandContext* ParserParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 8, ParserParser::RuleOperand);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    _la = _input->LA(1);
    if (!(((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2251765453946880) != 0)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuaddeclContext ------------------------------------------------------------------

ParserParser::QuaddeclContext::QuaddeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::QuaddeclContext::QUAD() {
  return getToken(ParserParser::QUAD, 0);
}

std::vector<tree::TerminalNode *> ParserParser::QuaddeclContext::NUMBER() {
  return getTokens(ParserParser::NUMBER);
}

tree::TerminalNode* ParserParser::QuaddeclContext::NUMBER(size_t i) {
  return getToken(ParserParser::NUMBER, i);
}


size_t ParserParser::QuaddeclContext::getRuleIndex() const {
  return ParserParser::RuleQuaddecl;
}

void ParserParser::QuaddeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuaddecl(this);
}

void ParserParser::QuaddeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuaddecl(this);
}


std::any ParserParser::QuaddeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitQuaddecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::QuaddeclContext* ParserParser::quaddecl() {
  QuaddeclContext *_localctx = _tracker.createInstance<QuaddeclContext>(_ctx, getState());
  enterRule(_localctx, 10, ParserParser::RuleQuaddecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(ParserParser::QUAD);
    setState(53);
    match(ParserParser::NUMBER);
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ParserParser::T__0) {
      setState(54);
      match(ParserParser::T__0);
      setState(55);
      match(ParserParser::NUMBER);
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilldeclContext ------------------------------------------------------------------

ParserParser::FilldeclContext::FilldeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::FilldeclContext::FILL() {
  return getToken(ParserParser::FILL, 0);
}

std::vector<tree::TerminalNode *> ParserParser::FilldeclContext::NUMBER() {
  return getTokens(ParserParser::NUMBER);
}

tree::TerminalNode* ParserParser::FilldeclContext::NUMBER(size_t i) {
  return getToken(ParserParser::NUMBER, i);
}


size_t ParserParser::FilldeclContext::getRuleIndex() const {
  return ParserParser::RuleFilldecl;
}

void ParserParser::FilldeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilldecl(this);
}

void ParserParser::FilldeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilldecl(this);
}


std::any ParserParser::FilldeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitFilldecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::FilldeclContext* ParserParser::filldecl() {
  FilldeclContext *_localctx = _tracker.createInstance<FilldeclContext>(_ctx, getState());
  enterRule(_localctx, 12, ParserParser::RuleFilldecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(ParserParser::FILL);
    setState(62);
    match(ParserParser::NUMBER);
    setState(63);
    match(ParserParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PosdeclContext ------------------------------------------------------------------

ParserParser::PosdeclContext::PosdeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::PosdeclContext::POS() {
  return getToken(ParserParser::POS, 0);
}

tree::TerminalNode* ParserParser::PosdeclContext::NUMBER() {
  return getToken(ParserParser::NUMBER, 0);
}


size_t ParserParser::PosdeclContext::getRuleIndex() const {
  return ParserParser::RulePosdecl;
}

void ParserParser::PosdeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPosdecl(this);
}

void ParserParser::PosdeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPosdecl(this);
}


std::any ParserParser::PosdeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitPosdecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::PosdeclContext* ParserParser::posdecl() {
  PosdeclContext *_localctx = _tracker.createInstance<PosdeclContext>(_ctx, getState());
  enterRule(_localctx, 14, ParserParser::RulePosdecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(ParserParser::POS);
    setState(66);
    match(ParserParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaindeclContext ------------------------------------------------------------------

ParserParser::MaindeclContext::MaindeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::MaindeclContext::MAIN() {
  return getToken(ParserParser::MAIN, 0);
}


size_t ParserParser::MaindeclContext::getRuleIndex() const {
  return ParserParser::RuleMaindecl;
}

void ParserParser::MaindeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaindecl(this);
}

void ParserParser::MaindeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaindecl(this);
}


std::any ParserParser::MaindeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitMaindecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::MaindeclContext* ParserParser::maindecl() {
  MaindeclContext *_localctx = _tracker.createInstance<MaindeclContext>(_ctx, getState());
  enterRule(_localctx, 16, ParserParser::RuleMaindecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(ParserParser::MAIN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StackdeclContext ------------------------------------------------------------------

ParserParser::StackdeclContext::StackdeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::StackdeclContext::STACK() {
  return getToken(ParserParser::STACK, 0);
}

std::vector<tree::TerminalNode *> ParserParser::StackdeclContext::NUMBER() {
  return getTokens(ParserParser::NUMBER);
}

tree::TerminalNode* ParserParser::StackdeclContext::NUMBER(size_t i) {
  return getToken(ParserParser::NUMBER, i);
}


size_t ParserParser::StackdeclContext::getRuleIndex() const {
  return ParserParser::RuleStackdecl;
}

void ParserParser::StackdeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStackdecl(this);
}

void ParserParser::StackdeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStackdecl(this);
}


std::any ParserParser::StackdeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitStackdecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::StackdeclContext* ParserParser::stackdecl() {
  StackdeclContext *_localctx = _tracker.createInstance<StackdeclContext>(_ctx, getState());
  enterRule(_localctx, 18, ParserParser::RuleStackdecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70);
    match(ParserParser::STACK);
    setState(71);
    match(ParserParser::NUMBER);
    setState(72);
    match(ParserParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeldeclContext ------------------------------------------------------------------

ParserParser::LabeldeclContext::LabeldeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ParserParser::LabeldeclContext::LABEL() {
  return getToken(ParserParser::LABEL, 0);
}


size_t ParserParser::LabeldeclContext::getRuleIndex() const {
  return ParserParser::RuleLabeldecl;
}

void ParserParser::LabeldeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeldecl(this);
}

void ParserParser::LabeldeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeldecl(this);
}


std::any ParserParser::LabeldeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ParserVisitor*>(visitor))
    return parserVisitor->visitLabeldecl(this);
  else
    return visitor->visitChildren(this);
}

ParserParser::LabeldeclContext* ParserParser::labeldecl() {
  LabeldeclContext *_localctx = _tracker.createInstance<LabeldeclContext>(_ctx, getState());
  enterRule(_localctx, 20, ParserParser::RuleLabeldecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(ParserParser::LABEL);
    setState(75);
    match(ParserParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ParserParser::initialize() {
  ::antlr4::internal::call_once(parserParserOnceFlag, parserParserInitialize);
}
