
// Generated from .\assember\grammer\Parser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ParserParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ParserParser.
 */
class  ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ParserParser.
   */
    virtual std::any visitCode(ParserParser::CodeContext *context) = 0;

    virtual std::any visitStmt(ParserParser::StmtContext *context) = 0;

    virtual std::any visitAssemblyinst(ParserParser::AssemblyinstContext *context) = 0;

    virtual std::any visitInst(ParserParser::InstContext *context) = 0;

    virtual std::any visitOperand(ParserParser::OperandContext *context) = 0;

    virtual std::any visitQuaddecl(ParserParser::QuaddeclContext *context) = 0;

    virtual std::any visitFilldecl(ParserParser::FilldeclContext *context) = 0;

    virtual std::any visitPosdecl(ParserParser::PosdeclContext *context) = 0;

    virtual std::any visitMaindecl(ParserParser::MaindeclContext *context) = 0;

    virtual std::any visitStackdecl(ParserParser::StackdeclContext *context) = 0;

    virtual std::any visitLabeldecl(ParserParser::LabeldeclContext *context) = 0;


};

