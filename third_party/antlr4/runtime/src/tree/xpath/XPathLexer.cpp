
// Generated from XPathLexer.g4 by ANTLR 4.9.3


#include "XPathLexer.h"


using namespace antlr4;

namespace {

struct XPathLexerStaticData final {
  XPathLexerStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> channelNames,
                        std::vector<std::string> modeNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  XPathLexerStaticData(const XPathLexerStaticData&) = delete;
  XPathLexerStaticData(XPathLexerStaticData&&) = delete;
  XPathLexerStaticData& operator=(const XPathLexerStaticData&) = delete;
  XPathLexerStaticData& operator=(XPathLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag xpathLexerOnceFlag;
XPathLexerStaticData *xpathLexerStaticData = nullptr;

void xpathLexerInitialize() {
  assert(xpathLexerStaticData == nullptr);
  auto staticData = std::make_unique<XPathLexerStaticData>(
    std::vector<std::string>{
      "ANYWHERE", "ROOT", "WILDCARD", "BANG", "ID", "NameChar", "NameStartChar",
      "STRING"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "", "'//'", "'/'", "'*'", "'!'"
    },
    std::vector<std::string>{
      "", "TOKEN_REF", "RULE_REF", "ANYWHERE", "ROOT", "WILDCARD", "BANG", "ID",
      "STRING"
    }
  );
  static const int32_t serializedATNSegment[] = {
    0x4, 0x0, 0x8, 0x32, 0x6, -1, 0x2, 0x0, 0x7, 0x0, 0x2, 0x1, 0x7,
       0x1, 0x2, 0x2, 0x7, 0x2, 0x2, 0x3, 0x7, 0x3, 0x2, 0x4, 0x7, 0x4,
       0x2, 0x5, 0x7, 0x5, 0x2, 0x6, 0x7, 0x6, 0x2, 0x7, 0x7, 0x7, 0x1,
       0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x2, 0x1, 0x2,
       0x1, 0x3, 0x1, 0x3, 0x1, 0x4, 0x1, 0x4, 0x5, 0x4, 0x1d, 0x8, 0x4,
       0xa, 0x4, 0xc, 0x4, 0x20, 0x9, 0x4, 0x1, 0x4, 0x1, 0x4, 0x1, 0x5,
       0x1, 0x5, 0x3, 0x5, 0x26, 0x8, 0x5, 0x1, 0x6, 0x1, 0x6, 0x1, 0x7,
       0x1, 0x7, 0x5, 0x7, 0x2c, 0x8, 0x7, 0xa, 0x7, 0xc, 0x7, 0x2f, 0x9,
       0x7, 0x1, 0x7, 0x1, 0x7, 0x1, 0x2d, 0x0, 0x8, 0x1, 0x3, 0x3, 0x4,
       0x5, 0x5, 0x7, 0x6, 0x9, 0x7, 0xb, 0x0, 0xd, 0x0, 0xf, 0x8, 0x1,
       0x0, 0x2, 0x5, 0x0, 0x30, 0x39, 0x5f, 0x5f, 0xb7, 0xb7, 0x300, 0x36f,
       0x203f, 0x2040, 0xd, 0x0, 0x41, 0x5a, 0x61, 0x7a, 0xc0, 0xd6, 0xd8,
       0xf6, 0xf8, 0x2ff, 0x370, 0x37d, 0x37f, 0x1fff, 0x200c, 0x200d, 0x2070,
       0x218f, 0x2c00, 0x2fef, 0x3001, 0xd7ff, 0xf900, 0xfdcf, 0xfdf0, -1,
       0x0, 0x32, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x0, 0x0,
       0x0, 0x0, 0x5, 0x1, 0x0, 0x0, 0x0, 0x0, 0x7, 0x1, 0x0, 0x0, 0x0,
       0x0, 0x9, 0x1, 0x0, 0x0, 0x0, 0x0, 0xf, 0x1, 0x0, 0x0, 0x0, 0x1,
       0x11, 0x1, 0x0, 0x0, 0x0, 0x3, 0x14, 0x1, 0x0, 0x0, 0x0, 0x5, 0x16,
       0x1, 0x0, 0x0, 0x0, 0x7, 0x18, 0x1, 0x0, 0x0, 0x0, 0x9, 0x1a, 0x1,
       0x0, 0x0, 0x0, 0xb, 0x25, 0x1, 0x0, 0x0, 0x0, 0xd, 0x27, 0x1, 0x0,
       0x0, 0x0, 0xf, 0x29, 0x1, 0x0, 0x0, 0x0, 0x11, 0x12, 0x5, 0x2f, 0x0,
       0x0, 0x12, 0x13, 0x5, 0x2f, 0x0, 0x0, 0x13, 0x2, 0x1, 0x0, 0x0, 0x0,
       0x14, 0x15, 0x5, 0x2f, 0x0, 0x0, 0x15, 0x4, 0x1, 0x0, 0x0, 0x0, 0x16,
       0x17, 0x5, 0x2a, 0x0, 0x0, 0x17, 0x6, 0x1, 0x0, 0x0, 0x0, 0x18, 0x19,
       0x5, 0x21, 0x0, 0x0, 0x19, 0x8, 0x1, 0x0, 0x0, 0x0, 0x1a, 0x1e, 0x3,
       0xd, 0x6, 0x0, 0x1b, 0x1d, 0x3, 0xb, 0x5, 0x0, 0x1c, 0x1b, 0x1, 0x0,
       0x0, 0x0, 0x1d, 0x20, 0x1, 0x0, 0x0, 0x0, 0x1e, 0x1c, 0x1, 0x0, 0x0,
       0x0, 0x1e, 0x1f, 0x1, 0x0, 0x0, 0x0, 0x1f, 0x21, 0x1, 0x0, 0x0, 0x0,
       0x20, 0x1e, 0x1, 0x0, 0x0, 0x0, 0x21, 0x22, 0x6, 0x4, 0x0, 0x0, 0x22,
       0xa, 0x1, 0x0, 0x0, 0x0, 0x23, 0x26, 0x3, 0xd, 0x6, 0x0, 0x24, 0x26,
       0x7, 0x0, 0x0, 0x0, 0x25, 0x23, 0x1, 0x0, 0x0, 0x0, 0x25, 0x24, 0x1,
       0x0, 0x0, 0x0, 0x26, 0xc, 0x1, 0x0, 0x0, 0x0, 0x27, 0x28, 0x7, 0x1,
       0x0, 0x0, 0x28, 0xe, 0x1, 0x0, 0x0, 0x0, 0x29, 0x2d, 0x5, 0x27, 0x0,
       0x0, 0x2a, 0x2c, 0x9, 0x0, 0x0, 0x0, 0x2b, 0x2a, 0x1, 0x0, 0x0, 0x0,
       0x2c, 0x2f, 0x1, 0x0, 0x0, 0x0, 0x2d, 0x2e, 0x1, 0x0, 0x0, 0x0, 0x2d,
       0x2b, 0x1, 0x0, 0x0, 0x0, 0x2e, 0x30, 0x1, 0x0, 0x0, 0x0, 0x2f, 0x2d,
       0x1, 0x0, 0x0, 0x0, 0x30, 0x31, 0x5, 0x27, 0x0, 0x0, 0x31, 0x10,
       0x1, 0x0, 0x0, 0x0, 0x4, 0x0, 0x1e, 0x25, 0x2d, 0x1, 0x1, 0x4, 0x0,
  };

  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  xpathLexerStaticData = staticData.release();
}

}

XPathLexer::XPathLexer(CharStream *input) : Lexer(input) {
  XPathLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *xpathLexerStaticData->atn, xpathLexerStaticData->decisionToDFA, xpathLexerStaticData->sharedContextCache);
}

XPathLexer::~XPathLexer() {
  delete _interpreter;
}

std::string XPathLexer::getGrammarFileName() const {
  return "XPathLexer.g4";
}

const std::vector<std::string>& XPathLexer::getRuleNames() const {
  return xpathLexerStaticData->ruleNames;
}

const std::vector<std::string>& XPathLexer::getChannelNames() const {
  return xpathLexerStaticData->channelNames;
}

const std::vector<std::string>& XPathLexer::getModeNames() const {
  return xpathLexerStaticData->modeNames;
}

const dfa::Vocabulary& XPathLexer::getVocabulary() const {
  return xpathLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView XPathLexer::getSerializedATN() const {
  return xpathLexerStaticData->serializedATN;
}

const atn::ATN& XPathLexer::getATN() const {
  return *xpathLexerStaticData->atn;
}

void XPathLexer::action(RuleContext *context, size_t ruleIndex, size_t actionIndex) {
  switch (ruleIndex) {
    case 4: IDAction(antlrcpp::downCast<antlr4::RuleContext *>(context), actionIndex); break;

  default:
    break;
  }
}

void XPathLexer::IDAction(antlr4::RuleContext *context, size_t actionIndex) {
  switch (actionIndex) {
    case 0:
    				if (isupper(getText()[0]))
    				  setType(TOKEN_REF);
    				else
    				  setType(RULE_REF);
    				 break;

  default:
    break;
  }
}

void XPathLexer::initialize() {
  ::antlr4::internal::call_once(xpathLexerOnceFlag, xpathLexerInitialize);
}
