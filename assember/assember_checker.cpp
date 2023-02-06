
//
// Created by 20580 on 2023/1/10.
//
#include "assember_checker.h"
#include <cassert>

void AssemblyVisitor::reset() {
    currentAddress = 0x0;
    haveMain = false;
    chk_results.clear();
    label_set.clear();
}

void AssemblyVisitor::visit(AssemblyCode *v) {
    reset();
    for(const auto& stmt : v->getStmts()) {
        switch (stmt->astType()) {
            case AstType::quad:
                visit(dynamic_cast<QuadDeclNode*>(stmt));
                break;
            case AstType::pos:
                visit(dynamic_cast<PosDeclNode*>(stmt));
                break;
            case AstType::main:
                if(haveMain){
                    chk_results.push_back({stmt->getLineNo(), 2, "too many .main declaration"});
                    haveError = true;
                }
                haveMain = true;
//                visit(dynamic_cast<MainDeclNode*>(stmt));
                break;
            case AstType::label:
                visit(dynamic_cast<LabelDeclNode*>(stmt));
                break;
            case AstType::assembly_stmt:
                visit(dynamic_cast<AssemblyInstNode*>(stmt));
                break;
            case AstType::fill:
                visit(dynamic_cast<FillDeclNode*>(stmt));
                break;
            default:
                assert(false && "This place has not other result!");
        }
    }
}

void AssemblyVisitor::visit(AssemblyInstNode *v) {
    v->setInstStartAddress(currentAddress);
//    visit(v->getInst());
    currentAddress += sizeof (Byte);
    switch (v->getOperatorCount()) {
        case 1:
            assert(v->getFirstOperand() != nullptr && "op1 is nullptr");
            if(v->getFirstOperand()->isReg())
                currentAddress += sizeof (Byte);
            else{
                currentAddress += sizeof (Quad);
            }
            visit(v->getFirstOperand());
            break;
        case 2:
            if(v->getFirstOperand()->isReg() && v->getSecondOperand()->isReg())
                currentAddress += sizeof (Byte);
            else{
                currentAddress += sizeof (Quad);
            }
            visit(v->getFirstOperand());
            visit(v->getSecondOperand());
    }
}

void AssemblyVisitor::visit(FillDeclNode *v) {
    v->setInstStartAddress(currentAddress);
    currentAddress += v->getFillSize();
}

void AssemblyVisitor::visit(InstNode *v) {
    // nothing
}

void AssemblyVisitor::visit(LabelDeclNode *v) {
    v->setInstStartAddress(currentAddress);
    if(label_set.find(v->getLabelName()) != label_set.end()){
        chk_results.push_back({v->getLineNo(), 2, "Declare the same label"});
        haveError = true;
    }
    else {
        label_set.insert(v->getLabelName());
    }
}

void AssemblyVisitor::visit(MainDeclNode *v) {
    // do nothing
}

void AssemblyVisitor::visit(OperandNode *v) {
    // do nothing
}

void AssemblyVisitor::visit(PosDeclNode *v) {
    if(v->getAddress() < currentAddress) {
        chk_results.push_back({v->getLineNo(), 2, "error .pos address give"});
        haveError = true;
    }
    else {
        currentAddress = v->getAddress();
    }
}

void AssemblyVisitor::visit(QuadDeclNode *v) {
    v->setInstStartAddress(currentAddress);
    currentAddress += v->getDataDecl().size() * sizeof(Quad);
}


