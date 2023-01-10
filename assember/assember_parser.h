//
// Created by 20580 on 2023/1/10.
//

#ifndef Y8664_ASSEMBER_PARSER_H
#define Y8664_ASSEMBER_PARSER_H

#include "assember_ast.h"

class AstBaseVisitor{
public:
    AstBaseVisitor() = default;

    virtual void visit(AssemblyCode* v) = 0;
    virtual void visit(AssemblyInstNode* v) = 0;
    virtual void visit(LabelDeclNode* v) = 0;
    virtual void visit(MainDeclNode* v) = 0;
    virtual void visit(PosDeclNode* v) = 0;
    virtual void visit(FillDeclNode* v) = 0;
    virtual void visit(QuadDeclNode* v) = 0;
    virtual void visit(InstNode* v) = 0;
    virtual void visit(OperandNode* v) = 0;
};

// 从汇编器的ast构建语法树
class AssemblyVisitor : public AstBaseVisitor{
public:
    AssemblyVisitor() = default;

    void visit(AssemblyCode *v) override;
    void visit(AssemblyInstNode *v) override;
    void visit(FillDeclNode *v) override;
    void visit(InstNode *v) override;
    void visit(LabelDeclNode *v) override;
    void visit(MainDeclNode *v) override;
    void visit(OperandNode *v) override;
    void visit(PosDeclNode *v) override;
    void visit(QuadDeclNode *v) override;
};

#endif //Y8664_ASSEMBER_PARSER_H
