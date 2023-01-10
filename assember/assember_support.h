//
// Created by 20580 on 2023/1/5.
//

#ifndef Y8664_ASSEMBER_SUPPORT_H
#define Y8664_ASSEMBER_SUPPORT_H

#include "../base.h"
#include "../error/error.h"

ErrorOrSuccess assemblyToCode(const std::string& inst);

// 汇编转换器
class AssemblyConverter{
public:
    AssemblyConverter() = default;
    static AssemblyConverter* getInstance();
    //汇编转换
    ErrorOrSuccess assembly(const AssemblyInst& inst);
private:
    static AssemblyConverter* instance;
};

// 反汇编转换器
class DisAssemblyConverter{
public:
    DisAssemblyConverter() = default;
    static DisAssemblyConverter* getInstance();

    ErrorOrSuccess disassembly(const MachineInst& inst);
private:
    static DisAssemblyConverter* instance;
};

#endif //Y8664_ASSEMBER_SUPPORT_H
