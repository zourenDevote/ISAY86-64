
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  ParserLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, POS = 3, FILL = 4, MAIN = 5, QUAD = 6, STACK = 7, 
    MHALT = 8, MNOP = 9, MRRMOVQ = 10, MIRMOVQ = 11, MRMMOVQ = 12, MMRMOVQ = 13, 
    MADDQ = 14, MSUBQ = 15, MANDQ = 16, MXORQ = 17, MJMP = 18, MJLE = 19, 
    MJL = 20, MJE = 21, MJNE = 22, MJQE = 23, MJQ = 24, MCMOVLE = 25, MCMOVL = 26, 
    MCMOVE = 27, MCMOVNE = 28, MCMOVGE = 29, MCMOVG = 30, MCALL = 31, MRET = 32, 
    MPUSHQ = 33, MPOPQ = 34, MRAX = 35, MRCX = 36, MRBX = 37, MRSP = 38, 
    MRBP = 39, MRSI = 40, MRDI = 41, MR8 = 42, MR9 = 43, MR10 = 44, MR11 = 45, 
    MR12 = 46, MR13 = 47, MR14 = 48, NUMBER = 49, LABEL = 50, WS = 51, COMMENT = 52
  };

  explicit ParserLexer(antlr4::CharStream *input);

  ~ParserLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

