//
// Created by 20580 on 2023/1/10.
//
#include "assember_ast.h"

OperandNode::OperandNode(const std::string& str, bool isLabel) :
    reg_or_label(str), is_label(isLabel), is_reg(!isLabel), is_quad(false), number(0) {}

OperandNode::OperandNode(Quad number) :
    reg_or_label(), is_label(false), is_reg(false), is_quad(true), number(number) {}

InstNode::InstNode(const std::string &inst, Byte op) : inst_op(op), inst(inst) {}

QuadDeclNode::QuadDeclNode(const std::vector<Quad> &data) : numbers(data) {}

FillDeclNode::FillDeclNode(Quad number, Byte value) : fill_size(number), fill_value(value){}

PosDeclNode::PosDeclNode(Quad addr) : address(addr){}

StackDeclNode::StackDeclNode(Quad size, Quad addr) : stack_size(size), address(addr){}

LabelDeclNode::LabelDeclNode(const std::string &label_name) : label_name(label_name){}

AssemblyInstNode::AssemblyInstNode(InstNode *inst, OperandNode *op1, OperandNode *op2) : inst(inst), op1(op1), op2(op2) {}

int AssemblyInstNode::getOperatorCount() {
    if(op1 == nullptr)
        return 0;
    if(op2 == nullptr)
        return 1;
    return 2;
}
