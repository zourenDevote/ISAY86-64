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
            assert(false && "Unknown reg index!");
    }
}
#undef GETREG

void Y8664Computer::execute() {
    while (statueIsAOK()){
        decode();
    }
}

void Y8664Computer::step() {}

void Y8664Computer::decode() {

    unsigned char ins_byte = memory.data[pc];
    pcAdd(INS_ONE);
    switch (ins_byte) {
        case NOP:       {nop();     break;}
        case HALT:      {halt();    break;}
        case RRMOVQ:    {rrmovq();  break;}
        case MRMOVQ:    {rrmovq();  break;}
        case IRMOVQ:    {irmovq();  break;}
        case RMMOVQ:    {rmmovq();  break;}
        case ADDQ:      {addq();    break;}
        case SUBQ:      {subq();    break;}
        case ANDQ:      {andq();    break;}
        case XORQ:      {xorq();    break;}
        case JMP:       {jmp();     break;}
        case JLE:       {jle();     break;}
        case JQE:       {jqe();     break;}
        case JNE:       {jne();     break;}
        case JL:        {jl();      break;}
        case JE:        {je();      break;}
        case JQ:        {jq();      break;}
        case CMOVLE:    {cmovle();  break;}
        case CMOVL:     {cmovl();   break;}
        case CMOVE:     {cmove();   break;}
        case CMOVNE:    {cmovne();  break;}
        case CMOVGE:    {cmovge();  break;}
        case CMOVG:     {cmovg();   break;}
        case RET:       {ret();     break;}
        case CALL:      {call();    break;}
        case PUSHQ:     {pushq();   break;}
        case POPQ:      {popq();    break;}
        default:
            setStatue(INS);
            // @todo 跳转到中断服务程序
    }
}

void Y8664Computer::loadProgramFromDisk(const char *filepath) {}

void Y8664Computer::halt()
{
    setStatue(HALT);
    // 进入Halt中断服务处理程序
}

void Y8664Computer::nop(){}

/// ret返回指令模拟，对应操作
/// PC = *stack.top
/// stack.top += sizeof(Quad)
void Y8664Computer::ret()
{
    if(regGroup.rsp == stackBase){
        setStatue(ADR);
        // @todo 跳转到对应的处理程序
    }else{
        pc = regGroup.rsp;
        regGroup.rsp += QUAD_DATA_LEN;
    }
}

/// rrmovq指令模拟，将寄存器rA的值赋予寄存器rB
void Y8664Computer::rrmovq()
{
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    rB = rA;
}

/// irmovq指令模拟，将立即数V的值赋予寄存器rB
void Y8664Computer::irmovq()
{
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    GET_DATA_FROM_MEM(V, pc-memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    rB = V;
}

/// rmmovq指令模拟，将寄存器rA的值赋予对应的内存位置
void Y8664Computer::rmmovq()
{
    GET_RA_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    GET_DATA_FROM_MEM(dest, pc-memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    ILL_ADR(dest)
    else{
        Quad* p = (Quad*)(memory.data + (dest - memory.startAddr));
        *p = rA;
    }
}

/// mrmovq指令模拟，将特定内存位置的值存入寄存器rB
void Y8664Computer::mrmovq() {
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
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

/// addq指令模拟，将rA和rB的值相加，并将得到的值放入rB
void Y8664Computer::addq() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    Quad res = rA + rB;
    if(res < rA || res < rB){setOFFlag();}
    else{resetOFFlag();}
    FLAG_SET(res)
    rB = res;
}
void Y8664Computer::subq() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    Quad res = rA - rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}


void Y8664Computer::andq() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    Quad res = rA & rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}

void Y8664Computer::xorq() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    Quad res = rA ^ rB;
    resetOFFlag();
    FLAG_SET(res)
    rB = res;
}
#undef FLAG_SET

#define COND_MOV(COND, rA, rB) if(COND){ rB = rA; }
void Y8664Computer::cmovle() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(flag.ZF == 1 || (flag.SF != flag.OF), rA, rB)
}

void Y8664Computer::cmovl() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(flag.SF != flag.OF, rA, rB)
}

void Y8664Computer::cmove() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(flag.ZF, rA, rB)
}

void Y8664Computer::cmovne() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(!flag.ZF, rA, rB)
}

void Y8664Computer::cmovge() {
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(flag.SF == flag.OF, rA, rB)
}

void Y8664Computer::cmovg()
{
    GET_RA_FROM_MEM(pc, memory.data)
    GET_RB_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
    COND_MOV(flag.ZF && (flag.SF == flag.OF), rA, rB)
}
#undef COND_MOV

void Y8664Computer::jmp()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    ILL_ADR(dest)
    else{pc = dest;}
}

/// 跳转条件 ZF = 1 || SF != OF
void Y8664Computer::jle()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(flag.ZF == 1 || (flag.SF != flag.OF))
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 SF != OF
void Y8664Computer::jl()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(flag.ZF != flag.OF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 1
void Y8664Computer::je()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(flag.ZF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 0
void Y8664Computer::jne()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(!flag.ZF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 SF = OF
void Y8664Computer::jqe()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(flag.SF == flag.OF)
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

/// 跳转条件 ZF = 0 && SF = OF
void Y8664Computer::jq()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
    if(flag.ZF == 0 && (flag.SF == flag.OF))
    {
        ILL_ADR(dest)
        else{pc = dest;}
    }
}

void Y8664Computer::call()
{
    GET_DATA_FROM_MEM(dest, pc - memory.startAddr, memory.data)
    pcAdd(INS_EIGHT);
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

void Y8664Computer::pushq() {
    GET_RA_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
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

void Y8664Computer::popq() {
    GET_RA_FROM_MEM(pc, memory.data)
    pcAdd(INS_ONE);
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


