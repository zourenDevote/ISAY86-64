//
// Created by 20580 on 2023/1/11.
//

#ifndef Y8664_ASSEMBLY_AST_BUILDER_H
#define Y8664_ASSEMBLY_AST_BUILDER_H

#include "grammer/ParserVisitor.h"
#include "assember_ast.h"

class AstBuilder : public ParserVisitor {
public:
    AstBuilder() = default;

    std::any visitAssemblyinst(ParserParser::AssemblyinstContext *context) override;
    std::any visitCode(ParserParser::CodeContext *context) override;
    std::any visitFilldecl(ParserParser::FilldeclContext *context) override;
    std::any visitInst(ParserParser::InstContext *context) override;
    std::any visitLabeldecl(ParserParser::LabeldeclContext *context) override;
    std::any visitMaindecl(ParserParser::MaindeclContext *context) override;
    std::any visitOperand(ParserParser::OperandContext *context) override;
    std::any visitPosdecl(ParserParser::PosdeclContext *context) override;
    std::any visitQuaddecl(ParserParser::QuaddeclContext *context) override;
    std::any visitStackdecl(ParserParser::StackdeclContext *context) override;
    std::any visitStmt(ParserParser::StmtContext *context) override;
};

#endif //Y8664_ASSEMBLY_AST_BUILDER_H
