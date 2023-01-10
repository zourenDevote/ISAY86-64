
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ParserVisitor.h"


/**
 * This class provides an empty implementation of ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ParserBaseVisitor : public ParserVisitor {
public:

  virtual std::any visitCode(ParserParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(ParserParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssemblyinst(ParserParser::AssemblyinstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInst(ParserParser::InstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperand(ParserParser::OperandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuaddecl(ParserParser::QuaddeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilldecl(ParserParser::FilldeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPosdecl(ParserParser::PosdeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMaindecl(ParserParser::MaindeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStackdecl(ParserParser::StackdeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabeldecl(ParserParser::LabeldeclContext *ctx) override {
    return visitChildren(ctx);
  }


};

