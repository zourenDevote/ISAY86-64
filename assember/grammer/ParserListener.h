
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ParserParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ParserParser.
 */
class  ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCode(ParserParser::CodeContext *ctx) = 0;
  virtual void exitCode(ParserParser::CodeContext *ctx) = 0;

  virtual void enterStmt(ParserParser::StmtContext *ctx) = 0;
  virtual void exitStmt(ParserParser::StmtContext *ctx) = 0;

  virtual void enterAssemblyinst(ParserParser::AssemblyinstContext *ctx) = 0;
  virtual void exitAssemblyinst(ParserParser::AssemblyinstContext *ctx) = 0;

  virtual void enterInst(ParserParser::InstContext *ctx) = 0;
  virtual void exitInst(ParserParser::InstContext *ctx) = 0;

  virtual void enterOperand(ParserParser::OperandContext *ctx) = 0;
  virtual void exitOperand(ParserParser::OperandContext *ctx) = 0;

  virtual void enterQuaddecl(ParserParser::QuaddeclContext *ctx) = 0;
  virtual void exitQuaddecl(ParserParser::QuaddeclContext *ctx) = 0;

  virtual void enterFilldecl(ParserParser::FilldeclContext *ctx) = 0;
  virtual void exitFilldecl(ParserParser::FilldeclContext *ctx) = 0;

  virtual void enterPosdecl(ParserParser::PosdeclContext *ctx) = 0;
  virtual void exitPosdecl(ParserParser::PosdeclContext *ctx) = 0;

  virtual void enterMaindecl(ParserParser::MaindeclContext *ctx) = 0;
  virtual void exitMaindecl(ParserParser::MaindeclContext *ctx) = 0;

  virtual void enterStackdecl(ParserParser::StackdeclContext *ctx) = 0;
  virtual void exitStackdecl(ParserParser::StackdeclContext *ctx) = 0;

  virtual void enterLabeldecl(ParserParser::LabeldeclContext *ctx) = 0;
  virtual void exitLabeldecl(ParserParser::LabeldeclContext *ctx) = 0;


};

