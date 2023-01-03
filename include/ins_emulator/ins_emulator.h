//
// Created by 20580 on 2022/10/18.
//

#ifndef Y8664_INS_EMULATOR_H
#define Y8664_INS_EMULATOR_H

#include "base.h"
#include "error/error.h"
#include <string>
#include <iostream>
#include <vector>




class InsEmulator{
public:
    InsEmulator();
    ~InsEmulator();
    /// 获取寄存器组
    Regs getRegGroup() const { return regGroup; }
    /// 获取程序计数器的值
    Quad getPcValue()  const { return pc; }
    /// 获取标志位的状态
    Flag getFlags() const { return flags; }
    /// 解析和执行指令
    ErrorOrSuccess parseAndExecute(const std::vector<std::string>& ins);
public:
    ///打印内存分布
    ///@param start 起始地址
    ///@param end   结束地址
    void printMemoryRange(Quad start, Quad end, std::ostream& = std::cout) const;
    /// 打印寄存器和标志位信息
    void printCpuRegAndFlagMsg(std::ostream& = std::cout) const;
    /// 打印程序计数器信息
    void printPcMsg(std::ostream& = std::cout) const;
    /// 打印整个指令模拟器当前的信息
    void printInsEmuMsg(std::ostream& = std::cout) const;
    /// 打印仿真器执行结果(输出修改后的内存位置，寄存器，标志位，PC的信息)
    void printEmuExecResult(std::ostream& = std::cout) const;
private:
    /// 重置指令仿真器内部标志
    void resetEmulatorFlag();
    /// 保存指令仿真器原有的数据信息
    void saveOldRegsAndFlags(){ oldGroup = regGroup; oldFlags = flags;}

private:
    /// 置位标志位
    inline void setZFFlag() { flags.ZF = 1; }
    inline void setSFFlag() { flags.SF = 1; }
    inline void setOFFlag() { flags.OF = 1; }
    /// 重置标志位
    inline void resetZFFlag() { flags.ZF = 0; }
    inline void resetSFFlag() { flags.SF = 0; }
    inline void resetOFFlag() { flags.OF = 0; }

private:
    /// 获取寄存器指令
    Quad& getReg(Byte);
    /// 设置标志位
    void setCC(Quad res, Quad rA, Quad rB, bool isAdd = false);
    /// 执行指令
    inline ErrorOrSuccess nop();
    inline ErrorOrSuccess halt();
    /// 传送指令
    inline ErrorOrSuccess rrmovq(Byte bt);
    inline ErrorOrSuccess irmovq(Byte bt, Quad val);
    inline ErrorOrSuccess rmmovq(Byte bt, Quad dest);
    inline ErrorOrSuccess mrmovq(Byte bt, Quad dest);
    /// 算术指令
    inline ErrorOrSuccess addq(Byte bt);
    inline ErrorOrSuccess subq(Byte bt);
    inline ErrorOrSuccess andq(Byte bt);
    inline ErrorOrSuccess xorq(Byte bt);
    inline ErrorOrSuccess opemu(Byte by, int op);
    /// 条件传送指令
    inline ErrorOrSuccess cmovle(Byte bt);
    inline ErrorOrSuccess cmovl(Byte bt);
    inline ErrorOrSuccess cmove(Byte bt);
    inline ErrorOrSuccess cmovne(Byte bt);
    inline ErrorOrSuccess cmovge(Byte bt);
    inline ErrorOrSuccess cmovg(Byte bt);
    /// 跳转指令
    inline ErrorOrSuccess jmp(Quad dest);
    inline ErrorOrSuccess jle(Quad dest);
    inline ErrorOrSuccess jl(Quad dest);
    inline ErrorOrSuccess je(Quad dest);
    inline ErrorOrSuccess jne(Quad dest);
    inline ErrorOrSuccess jqe(Quad dest);
    inline ErrorOrSuccess jq(Quad dest);
    /// 过程调用/返回指令
    inline ErrorOrSuccess call(Quad dest);
    inline ErrorOrSuccess ret();
    /// 入栈/出栈指令
    inline ErrorOrSuccess pushq(Byte bt);
    inline ErrorOrSuccess popq(Byte bt);
private:
    Regs regGroup;              // 指令执行完之后的寄存器组
    Regs oldGroup;              // 指令执行完之前的寄存器组

    Flag flags;                 // 指令执行完之后的标志位
    Flag oldFlags;              // 指令执行完之前的标志位

    unsigned char* memory;      // 内存地址
    unsigned int msize;         // 内存大小
    bool hasMemChange{false};   // 内存改变标志
    Quad memChangeAddr;         // 内存改变的位置
    unsigned int size{sizeof (Quad)};

    Quad pc;                    // 程序计数器
};

#endif //Y8664_INS_EMULATOR_H
