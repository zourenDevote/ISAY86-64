//
// Created by 20580 on 2023/1/11.
//

#include "assembly_ast_builder.h"
#include "../util/util.h"
#include "assember_support.h"

using namespace std;

std::any AstBuilder::visitCode(ParserParser::CodeContext *context){
    AssemblyCode* code = new AssemblyCode();
    for(const auto&stmt : context->stmt())
        code->addStmt(any_cast<BaseAst*>(visitStmt(stmt)));
    return code;
}

std::any AstBuilder::visitStmt(ParserParser::StmtContext *context) {

    if(context->assemblyinst()) {
        return any_cast<BaseAst*>(visitAssemblyinst(context->assemblyinst()));
    }
    else if(context->quaddecl()) {
        return any_cast<BaseAst*>(visitQuaddecl(context->quaddecl()));
    }
    else if(context->filldecl()) {
        return any_cast<BaseAst*>(visitFilldecl(context->filldecl()));
    }
    else if(context->posdecl()) {
        return any_cast<BaseAst*>(visitPosdecl(context->posdecl()));
    }
    else if(context->maindecl()) {
        return any_cast<BaseAst*>(visitMaindecl(context->maindecl()));
    }
    else if(context->stackdecl()) {
        return any_cast<BaseAst*>(visitStackdecl(context->stackdecl()));
    }
    return any_cast<BaseAst*>(visitLabeldecl(context->labeldecl()));
}

std::any AstBuilder::visitInst(ParserParser::InstContext *context) {
    InstNode* inst = new InstNode(context->getText(), assemblyToCode(context->getText()).as<Byte>());
    return inst;
}


std::any AstBuilder::visitOperand(ParserParser::OperandContext *context) {
    if(context->NUMBER()) {
        return new OperandNode(strToInt(context->NUMBER()->getText()).as<Quad>());
    }
    if(context->LABEL()) {
        return new OperandNode(context->getText(), true);
    }
    return new OperandNode(context->getText(), false);
}

std::any AstBuilder::visitQuaddecl(ParserParser::QuaddeclContext *context) {
    std::vector<Quad> data;
    for(const auto& number : context->NUMBER()) {
        data.push_back(strToInt(number->getText()).as<Quad>());
    }
    return new QuadDeclNode(data);
}

std::any AstBuilder::visitFilldecl(ParserParser::FilldeclContext *context) {
    return new FillDeclNode(strToInt(context->NUMBER(0)->getText()).as<Quad>(), strToInt(context->NUMBER(1)->getText()).as<Byte>());
}

std::any AstBuilder::visitPosdecl(ParserParser::PosdeclContext *context) {
    return new PosDeclNode(strToInt(context->NUMBER()->getText()).as<Quad>());
}

std::any AstBuilder::visitMaindecl(ParserParser::MaindeclContext *context) {
    return new MainDeclNode();
}

std::any AstBuilder::visitStackdecl(ParserParser::StackdeclContext *context) {
    return new StackDeclNode(strToInt(context->NUMBER(0)->getText()).as<Quad>(), strToInt(context->NUMBER(1)->getText()).as<Quad>());
}

std::any AstBuilder::visitLabeldecl(ParserParser::LabeldeclContext *context) {
    return new LabelDeclNode(context->LABEL()->getText());
}



