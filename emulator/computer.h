//
// Created by 20580 on 2022/9/26.
//

#ifndef Y8664_CPUMSG_H
#define Y8664_CPUMSG_H

#include "base.h"
#include "config.h"

/// 记录寄存器信息
struct Regs{
    Quad rax;
    Quad rcx;
    Quad rdx;
    Quad rbx;
    Quad rsp;
    Quad rbp;
    Quad rdi;

    Quad r8;
    Quad r9;
    Quad r10;
    Quad r11;
    Quad r12;
    Quad r13;
    Quad r14;

    Quad rsi;
};

/// 内存
struct Memory{
    char data[MEMORY_SIZE];
    char* startAddr;
    char* endAddr;
};

/// 标志位
struct Flag{
    ZF: 1;
    SF: 1;
    OF: 1;
};

/// Y86-64指令集架构计算机
class Y8664Computer{
private:
    enum Statue: char{
        AOK = 1,    // 正常操作
        HLT,        // 遇到halt指令
        ADR,        // 非法地址
        INS         // 非法指令
    };
public:
    Y8664Computer();
    /// 获取程序计数器的值
    Quad getPc() const{ return pc; }
    /// 获取当前寄存器的值
    Regs getRegMsg() const{ return regGroup; }
    /// 获取计算机执行的状态码
    unsigned getStatue() const{ return statue; }
    /// 获得标志位是否置位的方法
    bool isZFSet() const { return flag.ZF == 1; }
    bool isSFSet() const { return flag.SF == 1; }
    bool isOFSet() const { return flag.OF == 1; }
    /// 获得状态码
    bool statueIsAOK() const { return statue == Statue.AOK; }
    bool statueIsHLT() const { return statue == Statue.HLT; }
    bool statueIsADR() const { return statue == Statue.ADR; }
    bool statueIsINS() const { return statue == Statue.INS; }
private:
    /// 程序计数器改变
    void pcAdd(long long i){pc = Quad(long long(pc) + i);}
    /// 置位标志位
    void setZFFlag() { flag.ZF = 1; }
    void setSFFlag() { flag.SF = 1; }
    void setOFFlag() { flag.OF = 1; }
    /// 重置标志位
    void resetZFFlag() { flag.ZF = 0; }
    void resetSFFlag() { flag.SF = 0; }
    void resetOFFlag() { flag.OF = 0; }
    /// 设置状态码
    void setStatue(Statue stu){ statue = stu; }
private:
    Quad    pc;         // 程序计数器
    Regs    regGroup;   // 寄存器组
    Memory  memory;     // 内存
    Flag    flag;       // 标志位
    Statue  statue      // 状态码
};



#endif //Y8664_CPUMSG_H
