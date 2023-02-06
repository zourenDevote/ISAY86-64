//
// Created by 20580 on 2023/1/11.
//
#include "assember_generate.h"
#include "assember_support.h"
#include <cassert>

static inline void arrayAppendQuad(Byte* p, std::vector<Byte>& array, unsigned size) {
    for(int i = 0 ; i < size ; i++) {
        array.push_back(*(p+i));
    }
}

void AssemblySimplyElfGenerate::visit(AssemblyCode *v) {
    this->currentAddress = 0;
    for(const auto& stmt : v->getStmts()) {
        switch(stmt->astType()) {
            case AstType::main : {
                elf.header.main_entry = dynamic_cast<MainDeclNode*>(stmt)->getInstStartAddress();
                break;
            }
            case AstType::quad : {
                visit(dynamic_cast<QuadDeclNode*>(stmt));
                break;
            }
            case AstType::assembly_stmt : {
                visit(dynamic_cast<AssemblyInstNode*>(stmt));
                break;
            }
            case AstType::stack : {
                auto stack = dynamic_cast<StackDeclNode*>(stmt);
                stack_address = stack->getAddress();
                stack_size = stack->getStackSize();
                break;
            }
            case AstType::pos : {
                // @todo pos指令如何处理
                visit(dynamic_cast<PosDeclNode*>(stmt));
                break;
            }
            case AstType::label : {
                // @todo label被替换成地址
                visit(dynamic_cast<LabelDeclNode*>(stmt));
                break;
            }
            case AstType::fill : {
                visit(dynamic_cast<FillDeclNode*>(stmt));
                break;
            }
            default :
                assert(false && "Error ast node type.");
        }
    }
    elf.header.code_size = elf.codes.size();
    elf.header.data_size = elf.datas.size();
}

void AssemblySimplyElfGenerate::visit(AssemblyInstNode *v) {
    currentAddress += sizeof(Byte);
    elf.codes.push_back(v->getInst()->getInstOp());
    switch (v->getOperatorCount()) {
        case 1 : {
            auto op = v->getFirstOperand();
            if(op->isReg()) {
                currentAddress += sizeof(Byte);
                elf.codes.push_back(getReg(op->getRegName()).as<Byte>() << 4);
            }
            else if(op->isQuad() || op->isLabel()) {
                currentAddress += sizeof(Quad);
                Quad number = op->getNumber();
                arrayAppendQuad((Byte*)(&number), elf.codes, sizeof(Quad));
            }
            break;
        }
        case 2 : {
            auto op1 = v->getFirstOperand();
            auto op2 = v->getSecondOperand();
            if(op1->isReg() && op2->isReg()) {
                currentAddress += sizeof(Byte);
                Byte high = getReg(op1->getRegName()).as<Byte>() << 4;
                Byte low = getReg(op2->getRegName()).as<Byte>();
                elf.codes.push_back(high | low);
            }
            else if(op1->isReg() && op2->isQuad()) {
                currentAddress += (sizeof(Byte) + sizeof(Quad));
                Byte high = getReg(op1->getRegName()).as<Byte>() << 4;
                Quad number = op2->getNumber();
                elf.codes.push_back(high);
                arrayAppendQuad((Byte*)(&number), elf.codes, sizeof(Quad));
            }
            else if(op1->isQuad() && op2->isReg()) {
                currentAddress += (sizeof(Byte) + sizeof(Quad));
                Byte high = getReg(op2->getRegName()).as<Byte>() << 4;
                Quad number = op1->getNumber();
                elf.codes.push_back(high);
                arrayAppendQuad((Byte*)(&number), elf.codes, sizeof(Quad));
            }
            else if(op1->isLabel() && op2->isReg()) {
                currentAddress += (sizeof(Byte) + sizeof(Quad));
                Quad addr = label_map[op1->getLabelName()];
                Byte high = getReg(op2->getRegName()).as<Byte>() << 4;
                elf.codes.push_back(high);
                arrayAppendQuad((Byte*)(&addr), elf.codes, sizeof(Quad));
            }
            else if(op1->isReg() && op2->isLabel()) {
                currentAddress += (sizeof(Byte) + sizeof(Quad));
                Quad addr = label_map[op2->getLabelName()];
                Byte high = getReg(op1->getRegName()).as<Byte>() << 4;
                elf.codes.push_back(high);
                arrayAppendQuad((Byte*)(&addr), elf.codes, sizeof(Quad));
            }
            break;
        }
        default :
            break;
    }
}

void AssemblySimplyElfGenerate::visit(FillDeclNode *v) {
    currentAddress += v->getFillSize();
    for(int i = 0 ; i < v->getFillSize() ; i++)
        elf.datas.push_back(v->getFillValue());
}

void AssemblySimplyElfGenerate::visit(InstNode *v) {

}

void AssemblySimplyElfGenerate::visit(LabelDeclNode *v) {
    label_map.insert({v->getLabelName(), v->getInstStartAddress()});
}

void AssemblySimplyElfGenerate::visit(MainDeclNode *v) {

}

void AssemblySimplyElfGenerate::visit(OperandNode *v) {

}

void AssemblySimplyElfGenerate::visit(PosDeclNode *v) {
    while(currentAddress < v->getAddress()) {
        elf.codes.push_back(NOP);
        currentAddress++;
    }
}

void AssemblySimplyElfGenerate::visit(QuadDeclNode *v) {
    currentAddress += sizeof (Quad) * v->getDataDecl().size();
    for(const auto& value : v->getDataDecl()) {
        arrayAppendQuad((Byte*)(&value), elf.datas, sizeof (Quad));
    }
}

