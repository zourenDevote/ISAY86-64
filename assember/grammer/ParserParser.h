
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  ParserParser : public antlr4::Parser {
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

  enum {
    RuleCode = 0, RuleStmt = 1, RuleAssemblyinst = 2, RuleInst = 3, RuleOperand = 4, 
    RuleQuaddecl = 5, RuleFilldecl = 6, RulePosdecl = 7, RuleMaindecl = 8, 
    RuleStackdecl = 9, RuleLabeldecl = 10
  };

  explicit ParserParser(antlr4::TokenStream *input);

  ParserParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ParserParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CodeContext;
  class StmtContext;
  class AssemblyinstContext;
  class InstContext;
  class OperandContext;
  class QuaddeclContext;
  class FilldeclContext;
  class PosdeclContext;
  class MaindeclContext;
  class StackdeclContext;
  class LabeldeclContext; 

  class  CodeContext : public antlr4::ParserRuleContext {
  public:
    CodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodeContext* code();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyinstContext *assemblyinst();
    QuaddeclContext *quaddecl();
    FilldeclContext *filldecl();
    PosdeclContext *posdecl();
    MaindeclContext *maindecl();
    StackdeclContext *stackdecl();
    LabeldeclContext *labeldecl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmtContext* stmt();

  class  AssemblyinstContext : public antlr4::ParserRuleContext {
  public:
    AssemblyinstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InstContext *inst();
    std::vector<OperandContext *> operand();
    OperandContext* operand(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssemblyinstContext* assemblyinst();

  class  InstContext : public antlr4::ParserRuleContext {
  public:
    InstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MHALT();
    antlr4::tree::TerminalNode *MNOP();
    antlr4::tree::TerminalNode *MRRMOVQ();
    antlr4::tree::TerminalNode *MIRMOVQ();
    antlr4::tree::TerminalNode *MMRMOVQ();
    antlr4::tree::TerminalNode *MRMMOVQ();
    antlr4::tree::TerminalNode *MADDQ();
    antlr4::tree::TerminalNode *MSUBQ();
    antlr4::tree::TerminalNode *MANDQ();
    antlr4::tree::TerminalNode *MXORQ();
    antlr4::tree::TerminalNode *MJMP();
    antlr4::tree::TerminalNode *MJLE();
    antlr4::tree::TerminalNode *MJL();
    antlr4::tree::TerminalNode *MJE();
    antlr4::tree::TerminalNode *MJNE();
    antlr4::tree::TerminalNode *MJQE();
    antlr4::tree::TerminalNode *MJQ();
    antlr4::tree::TerminalNode *MCMOVLE();
    antlr4::tree::TerminalNode *MCMOVL();
    antlr4::tree::TerminalNode *MCMOVE();
    antlr4::tree::TerminalNode *MCMOVNE();
    antlr4::tree::TerminalNode *MCMOVGE();
    antlr4::tree::TerminalNode *MCMOVG();
    antlr4::tree::TerminalNode *MCALL();
    antlr4::tree::TerminalNode *MRET();
    antlr4::tree::TerminalNode *MPUSHQ();
    antlr4::tree::TerminalNode *MPOPQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstContext* inst();

  class  OperandContext : public antlr4::ParserRuleContext {
  public:
    OperandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MRAX();
    antlr4::tree::TerminalNode *MRCX();
    antlr4::tree::TerminalNode *MRBX();
    antlr4::tree::TerminalNode *MRSP();
    antlr4::tree::TerminalNode *MRBP();
    antlr4::tree::TerminalNode *MRSI();
    antlr4::tree::TerminalNode *MRDI();
    antlr4::tree::TerminalNode *MR8();
    antlr4::tree::TerminalNode *MR9();
    antlr4::tree::TerminalNode *MR10();
    antlr4::tree::TerminalNode *MR11();
    antlr4::tree::TerminalNode *MR12();
    antlr4::tree::TerminalNode *MR13();
    antlr4::tree::TerminalNode *MR14();
    antlr4::tree::TerminalNode *LABEL();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperandContext* operand();

  class  QuaddeclContext : public antlr4::ParserRuleContext {
  public:
    QuaddeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *QUAD();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuaddeclContext* quaddecl();

  class  FilldeclContext : public antlr4::ParserRuleContext {
  public:
    FilldeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FILL();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilldeclContext* filldecl();

  class  PosdeclContext : public antlr4::ParserRuleContext {
  public:
    PosdeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *POS();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PosdeclContext* posdecl();

  class  MaindeclContext : public antlr4::ParserRuleContext {
  public:
    MaindeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MAIN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MaindeclContext* maindecl();

  class  StackdeclContext : public antlr4::ParserRuleContext {
  public:
    StackdeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STACK();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StackdeclContext* stackdecl();

  class  LabeldeclContext : public antlr4::ParserRuleContext {
  public:
    LabeldeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LABEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabeldeclContext* labeldecl();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

