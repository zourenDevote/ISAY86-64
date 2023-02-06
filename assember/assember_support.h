//
// Created by 20580 on 2023/1/5.
//

#ifndef Y8664_ASSEMBER_SUPPORT_H
#define Y8664_ASSEMBER_SUPPORT_H

#include "../base.h"
#include "../error/error.h"

ErrorOrSuccess assemblyToCode(const std::string& inst);
ErrorOrSuccess getReg(const std::string& reg);

// 汇编转换器
class AssemblyConverter{;
public:
    //汇编转换
    ErrorOrSuccess assembly(const AssemblyInst& inst);

SIGNAL_INSTANCE(AssemblyConverter)
};

// 反汇编转换器
class DisAssemblyConverter{
public:

    ErrorOrSuccess disassembly(const MachineInst& inst);

SIGNAL_INSTANCE(DisAssemblyConverter)
};


// 机器指令转换
class MachineInstConverter {
public:

    ErrorOrSuccess readMachineInstFromBytes(const std::vector<Byte>& bytes);

SIGNAL_INSTANCE(MachineInstConverter)
};

#endif //Y8664_ASSEMBER_SUPPORT_H
