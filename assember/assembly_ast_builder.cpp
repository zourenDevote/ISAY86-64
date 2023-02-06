//
// Created by 20580 on 2023/1/11.
//

#include "assembly_ast_builder.h"
#include "../util/util.h"
#include "assember_support.h"

using namespace std;

std::any AstBuilder::visitCode(ParserParser::CodeContext *context){
    auto code = new AssemblyCode();
    for(const auto&stmt : context->stmt())
        code->addStmt(any_cast<BaseAst*>(visitStmt(stmt)));
    return code;
}

std::any AstBuilder::visitStmt(ParserParser::StmtContext *context) {

    if(context->assemblyinst()) {
        return visitAssemblyinst(context->assemblyinst());
    }
    else if(context->quaddecl()) {
        return visitQuaddecl(context->quaddecl());
    }
    else if(context->filldecl()) {
        return visitFilldecl(context->filldecl());
    }
    else if(context->posdecl()) {
        return visitPosdecl(context->posdecl());
    }
    else if(context->maindecl()) {
        return visitMaindecl(context->maindecl());
    }
    else if(context->stackdecl()) {
        return visitStackdecl(context->stackdecl());
    }
    return visitLabeldecl(context->labeldecl());
}

std::any AstBuilder::visitAssemblyinst(ParserParser::AssemblyinstContext *context) {
    auto inst = any_cast<InstNode*>(visit(context->inst()));
    switch (context->operand().size()) {
        case 0:{
            return dynamic_cast<BaseAst*>(new AssemblyInstNode(inst));
        }
        default:{
            auto op1 = any_cast<OperandNode*>(visitOperand(context->operand(0)));
            OperandNode* op2 = nullptr;
            if(context->operand().size() >= 2) {
                op2 = any_cast<OperandNode*>(visitOperand(context->operand(1)));
            }
            return dynamic_cast<BaseAst*>(new AssemblyInstNode(inst, op1, op2));
        }
    }
}

std::any AstBuilder::visitInst(ParserParser::InstContext *context) {
    auto inst = new InstNode(context->getText(), assemblyToCode(context->getText()).as<Byte>());
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
    return dynamic_cast<BaseAst*>(new QuadDeclNode(data));
}

std::any AstBuilder::visitFilldecl(ParserParser::FilldeclContext *context) {
    return dynamic_cast
            <BaseAst*>(
            new FillDeclNode(strToInt(context->NUMBER(0)->getText()).as<Quad>(), (Byte)(strToInt(context->NUMBER(1)->getText()).as<Quad>()))
            );
}

std::any AstBuilder::visitPosdecl(ParserParser::PosdeclContext *context) {
    return dynamic_cast<BaseAst*>(new PosDeclNode(strToInt(context->NUMBER()->getText()).as<Quad>()));
}

std::any AstBuilder::visitMaindecl(ParserParser::MaindeclContext *context) {
    return dynamic_cast<BaseAst*>(new MainDeclNode());
}

std::any AstBuilder::visitStackdecl(ParserParser::StackdeclContext *context) {
    return dynamic_cast<BaseAst*>(new StackDeclNode(strToInt(context->NUMBER(0)->getText()).as<Quad>(), strToInt(context->NUMBER(1)->getText()).as<Quad>()));
}

std::any AstBuilder::visitLabeldecl(ParserParser::LabeldeclContext *context) {
    return dynamic_cast<BaseAst*>(new LabelDeclNode(context->LABEL()->getText()));
}

