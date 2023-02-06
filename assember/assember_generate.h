//
// Created by 20580 on 2023/1/11.
//

#ifndef Y8664_ASSEMBER_GENERATE_H
#define Y8664_ASSEMBER_GENERATE_H

#include "assember_checker.h"
#include "../elf/myelf.h"
#include <map>



class AssemblySimplyElfGenerate : public AstBaseVisitor {
public:
    AssemblySimplyElfGenerate() : elf() {}

    void visit(AssemblyCode *v) override;
    void visit(AssemblyInstNode *v) override;
    void visit(FillDeclNode *v) override;
    void visit(InstNode *v) override;
    void visit(LabelDeclNode *v) override;
    void visit(MainDeclNode *v) override;
    void visit(OperandNode *v) override;
    void visit(PosDeclNode *v) override;
    void visit(QuadDeclNode *v) override;

    const MySimpleElf& getElf() const { return elf; }
private:
    MySimpleElf elf;
    // 由于汇编到elf会发生地址的相对变化，所以需要维护一个地址映射，方便一一对应
    std::map<Quad, Quad> address_map;
    // 存储Label -> Address 的映射关系
    std::map<std::string, Quad> label_map;
    // 存储栈信息
    Quad stack_address;
    Quad stack_size;
    // 指针地址
    Quad currentAddress;
};


#endif //Y8664_ASSEMBER_GENERATE_H
