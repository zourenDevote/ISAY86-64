//
// Created by 20580 on 2022/9/26.
//

#include "computer.h"
#include <cstring>
#include <cassert>

#define ILL_ADR(dest)         if(dest < memory.startAddr || dest > memory.endAddr - sizeof (Quad)) \
                              {                                                    \
                                setStatue(ADR);                                     \
                                }

Y8664Computer::Y8664Computer(): memory(),
                                regGroup(),
                                flag(),
                                stat(AOK),
                                pc(0),
                                stackBase(0)
                                {
    // 初始化内存
    memset(memory.data, 0, MEMORY_SIZE);
    memory.startAddr = 0x0;
    memory.endAddr = MEMORY_SIZE;

    // 重置寄存器
    memset(&regGroup, 0, sizeof (Regs));

    // 重置标志位
    resetOFFlag();
    resetSFFlag();
    resetZFFlag();
}

void Y8664Computer::loadAndRunProgram(const char *filepath)
{

}

#define GETREG(A, B) case A: \
    return regGroup.B;
Quad &Y8664Computer::getReg(unsigned char number)
{
    switch (number)
    {
        GETREG(RAX, rax)
        GETREG(RCX, rcx)
        GETREG(RBX, rbx)
        GETREG(RSP, rsp)
        GETREG(RBP, rbp)
        GETREG(RSI, rsi)
        GETREG(RDI, rdi)
        GETREG(R8, r8)
        GETREG(R9, r9)
        GETREG(R10, r10)
        GETREG(R11, r11)
        GETREG(R12, r12)
        GETREG(R13, r13)
        GETREG(R14, r14)
        default:
            assert(false && "Unknown reg number");
    }
}
#undef GETREG

void Y8664Computer::execute() {}

void Y8664Computer::step() {}

void Y8664Computer::loadProgramFromDisk(const char *filepath) {}

void Y8664Computer::halt()
{
    pcAdd(INS_ONE);
    setStatue(HALT);
}

void Y8664Computer::nop()
{
    pcAdd(INS_ONE);
}

void Y8664Computer::ret()
{
    pcAdd(INS_ONE);
    if(regGroup.rsp == stackBase){
        setStatue(ADR);
        // @todo 跳转到对应的处理程序
    }else{
        pc = regGroup.rsp;
        regGroup.rsp += QUAD_DATA_LEN;
    }
}

void Y8664Computer::rrmovq(Quad &rA, Quad &rB)
{
    pcAdd(INS_TWO);
    rB = rA;
}

void Y8664Computer::irmovq(Quad V, Quad &rB)
{
    pcAdd(INS_TEN);
    rB = V;
}

void Y8664Computer::rmmovq(Quad &rA, Quad dest)
{
    ILL_ADR(dest)
    else{
        pcAdd(INS_TEN);
        Quad* p = (Quad*)(memory.data + (dest - memory.startAddr));
        *p = rA;
    }
}

void Y8664Computer::mrmovq(Quad dest, Quad &rB) {
    pcAdd(INS_TEN);
    ILL_ADR(dest)
    else{
        Quad* p = (Quad*)(memory.data + (dest - memory.startAddr));
        rB = *p;
    }
}

#define FLAG_SET(res)   if(res | ZF_MASK){setZFFlag();}\
                        else{resetZFFlag();}\
                        if(res & SF_MASK){setSFFlag();}\
                        else{resetSFFlag();}

void Y8664Computer::addq(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    Quad res = rA + rB;
    if(res < rA || res < rB){setOFFlag();}
    else{resetOFFlag();}
    FLAG_SET(res)
    rB = res;
}

void Y8664Computer::subq(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    Quad res = rA - rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}


void Y8664Computer::andq(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    Quad res = rA & rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}

void Y8664Computer::xorq(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    Quad res = rA ^ rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}
#undef FLAG_SET

void Y8664Computer::cmovle(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    if(rA <= rB){rB = rA;}
}

void Y8664Computer::cmovl(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    if(rA < rB){rB = rA;}
}

void Y8664Computer::cmove(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    if(rA == rB){rB = rA;}
}

void Y8664Computer::cmovne(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    if(rA != rB){rB = rA;}
}

void Y8664Computer::cmovge(Quad &rA, Quad &rB) {
    pcAdd(INS_TWO);
    if(rA >= rB){rB = rA;}
}

void Y8664Computer::cmovg(Quad &rA, Quad &rB)
{
    pcAdd(INS_TWO);
    if(rA > rB){rB = rA;}

}

void Y8664Computer::jmp(Quad dest)
{
    pcAdd(INS_NINE);
    ILL_ADR(dest)
    else{pc = dest;}
}

/// 跳转条件 ZF = 1 || SF != OF
void Y8664Computer::jle(Quad dest)
{
    pcAdd(INS_NINE);
    if(flag.ZF == 1 || (flag.SF != flag.OF))
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 SF != OF
void Y8664Computer::jl(Quad dest)
{
    pcAdd(INS_NINE);
    if(flag.ZF != flag.OF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 1
void Y8664Computer::je(Quad dest)
{
    pcAdd(INS_NINE);
    if(flag.ZF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 0
void Y8664Computer::jne(Quad dest)
{
    pcAdd(INS_NINE);
    if(!flag.ZF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 SF = OF
void Y8664Computer::jqe(Quad dest)
{
    pcAdd(INS_NINE);
    if(flag.SF == flag.OF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 0 && SF = OF
void Y8664Computer::jq(Quad dest)
{
    pcAdd(INS_NINE);
    if(flag.ZF == 0 && (flag.SF == flag.OF))
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

void Y8664Computer::call(Quad dest)
{
    pcAdd(INS_NINE);
    if(stackFull >= regGroup.rsp)
    {
        setStatue(ADR);
        // @todo 转到中断服务历程
    }
    else
    {
        Quad *p = (Quad*)(memory.data + regGroup.rsp);
        regGroup.rsp -= QUAD_DATA_LEN;
        *p = pc;
        ILL_ADR(dest)
        else{pc = dest;}
    }

}

void Y8664Computer::pushq(Quad &rA) {
    pcAdd(INS_TWO);
    if(stackFull >= regGroup.rsp)
    {
        setStatue(ADR);
        // @todo 转到中断服务历程
    }
    else
    {
        Quad *p = (Quad*)(memory.data + regGroup.rsp);
        regGroup.rsp -= QUAD_DATA_LEN;
        *p = rA;
    }
}

void Y8664Computer::popq(Quad &rA) {
    pcAdd(INS_TWO);
    if((stackBase - QUAD_DATA_LEN) <= regGroup.rsp)
    {
        setStatue(ADR);
        // @todo 转到中断服务历程
    }
    else
    {
        Quad *p = (Quad*)(memory.data + regGroup.rsp);
        regGroup.rsp += QUAD_DATA_LEN;
        rA = *p;
    }
}

#undef ILL_ADR


