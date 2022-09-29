//
// Created by 20580 on 2022/9/26.
//

#ifndef Y8664_CPUMSG_H
#define Y8664_CPUMSG_H

#include "../base.h"

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
    char data[MEMORY_SIZE];     // 内存区域
    Quad startAddr;            // 内存起始地址
    Quad endAddr;              // 内存结束地址
};

/// 标志位
struct Flag{
    unsigned char ZF: 1;
    unsigned char SF: 1;
    unsigned char OF: 1;
};

/// Y86-64指令集架构计算机
class Y8664Computer{
public:
    Y8664Computer();
    /// 获取程序计数器的值
    inline Quad getPc() const{ return pc; }
    /// 获取当前寄存器的值
    inline Regs getRegMsg() const{ return regGroup; }
    /// 获取计算机执行的状态码
    inline unsigned getStatue() const{ return stat; }
    /// 获得标志位是否置位的方法
    inline bool isZFSet() const { return flag.ZF == 1; }
    inline bool isSFSet() const { return flag.SF == 1; }
    inline bool isOFSet() const { return flag.OF == 1; }
    /// 获得状态码
    inline bool statueIsAOK() const { return stat == AOK; }
    inline bool statueIsHLT() const { return stat == HLT; }
    inline bool statueIsADR() const { return stat == ADR; }
    inline bool statueIsINS() const { return stat == INS; }

    /// 执行程序
    void loadAndRunProgram(const char* filepath);

private:
    /// 程序计数器改变
    void pcAdd(Quad i, bool isAdd = true)
    {
        if(isAdd)
        {
            pc = pc + i;
        }
        else
        {
            pc = pc - i;
        }
    }
    /// 置位标志位
    inline void setZFFlag() { flag.ZF = 1; }
    inline void setSFFlag() { flag.SF = 1; }
    inline void setOFFlag() { flag.OF = 1; }
    /// 重置标志位
    inline void resetZFFlag() { flag.ZF = 0; }
    inline void resetSFFlag() { flag.SF = 0; }
    inline void resetOFFlag() { flag.OF = 0; }
    /// 设置状态码
    inline void setStatue(unsigned char stu){ stat = stu; }

private:
    /// 获取特定寄存器的引用
    Quad& getReg(unsigned char number);

    /// 指令的分发执行
    void execute();
    void step();

    /// 从磁盘中加载程序执行
    void loadProgramFromDisk(const char* filepath);

    /// 具体的指令
    void halt();
    void nop();
    void ret();

    void rrmovq(Quad& rA, Quad& rB);
    void irmovq(Quad V, Quad& rB);
    void rmmovq(Quad& rA, Quad dest);
    void mrmovq(Quad dest, Quad& rB);
    void addq(Quad& rA, Quad& rB);
    void subq(Quad& rA, Quad& rB);
    void andq(Quad& rA, Quad& rB);
    void xorq(Quad& rA, Quad& rB);
    void cmovle(Quad& rA, Quad& rB);
    void cmovl(Quad& rA, Quad& rB);
    void cmove(Quad& rA, Quad& rB);
    void cmovne(Quad& rA, Quad& rB);
    void cmovge(Quad& rA, Quad& rB);
    void cmovg(Quad& rA, Quad& rB);

    void jmp(Quad dest);
    void jle(Quad dest);
    void jl(Quad dest);
    void je(Quad dest);
    void jne(Quad dest);
    void jqe(Quad dest);
    void jq(Quad dest);
    void call(Quad dest);
    void pushq(Quad& rA);
    void popq(Quad& rA);

private:
    Quad    pc;         // 程序计数器
    Regs    regGroup;   // 寄存器组
    Memory  memory;     // 内存
    Flag    flag;       // 标志位
    unsigned char stat; // 状态码
    Quad    stackBase;  // 栈基址
    Quad    stackFull;  // 栈最小地址
};



#endif //Y8664_CPUMSG_H
