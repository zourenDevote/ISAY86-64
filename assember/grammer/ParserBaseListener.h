
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ParserListener.h"


/**
 * This class provides an empty implementation of ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ParserBaseListener : public ParserListener {
public:

  virtual void enterCode(ParserParser::CodeContext * /*ctx*/) override { }
  virtual void exitCode(ParserParser::CodeContext * /*ctx*/) override { }

  virtual void enterStmt(ParserParser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(ParserParser::StmtContext * /*ctx*/) override { }

  virtual void enterAssemblyinst(ParserParser::AssemblyinstContext * /*ctx*/) override { }
  virtual void exitAssemblyinst(ParserParser::AssemblyinstContext * /*ctx*/) override { }

  virtual void enterInst(ParserParser::InstContext * /*ctx*/) override { }
  virtual void exitInst(ParserParser::InstContext * /*ctx*/) override { }

  virtual void enterOperand(ParserParser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(ParserParser::OperandContext * /*ctx*/) override { }

  virtual void enterQuaddecl(ParserParser::QuaddeclContext * /*ctx*/) override { }
  virtual void exitQuaddecl(ParserParser::QuaddeclContext * /*ctx*/) override { }

  virtual void enterFilldecl(ParserParser::FilldeclContext * /*ctx*/) override { }
  virtual void exitFilldecl(ParserParser::FilldeclContext * /*ctx*/) override { }

  virtual void enterPosdecl(ParserParser::PosdeclContext * /*ctx*/) override { }
  virtual void exitPosdecl(ParserParser::PosdeclContext * /*ctx*/) override { }

  virtual void enterMaindecl(ParserParser::MaindeclContext * /*ctx*/) override { }
  virtual void exitMaindecl(ParserParser::MaindeclContext * /*ctx*/) override { }

  virtual void enterStackdecl(ParserParser::StackdeclContext * /*ctx*/) override { }
  virtual void exitStackdecl(ParserParser::StackdeclContext * /*ctx*/) override { }

  virtual void enterLabeldecl(ParserParser::LabeldeclContext * /*ctx*/) override { }
  virtual void exitLabeldecl(ParserParser::LabeldeclContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

