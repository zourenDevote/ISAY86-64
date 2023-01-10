//
// Created by 20580 on 2022/9/26.
//

#ifndef Y8664_CONFIG_H
#define Y8664_CONFIG_H

#include <string>
#include <vector>

#define MEMORY_SIZE 1048576

#define RAX     0x0
#define RCX     0x1
#define RBX     0x2
#define RSP     0x3
#define RBP     0x4
#define RSI     0x5
#define RDI     0x6
#define R8      0x7
#define R9      0x8
#define R10     0x9
#define R11     0xA
#define R12     0xB
#define R13     0xC
#define R14     0xD

#define HALT    0x00
#define NOP     0x10
#define RRMOVQ  0x20
#define IRMOVQ  0x30
#define RMMOVQ  0x40
#define MRMOVQ  0x50
#define ADDQ    0x60
#define SUBQ    0x61
#define ANDQ    0x62
#define XORQ    0x63
#define JMP     0x70
#define JLE     0x71
#define JL      0x72
#define JE      0x73
#define JNE     0x74
#define JQE     0x75
#define JQ      0x76
#define CMOVLE  0x21
#define CMOVL   0x22
#define CMOVE   0x23
#define CMOVNE  0x24
#define CMOVGE  0x25
#define CMOVG   0x26
#define CALL    0x80
#define RET     0x90
#define PUSHQ   0xA0
#define POPQ    0xB0

#define AOK 1
#define HLT 2
#define ADR 3
#define INS 4

#define INS_ONE 1
#define INS_EIGHT 8

#define SF_MASK 0x8000000000000000
#define ZF_MASK 0x0000000000000000

#define GET_LOW_FOUR_BIT(number) ((unsigned char)number & 0x0F)
#define GET_HIGH_FOUR_BIT(number) (((unsigned char)number >> 4) & 0x0F)

#define GET_RA_FROM_MEM(index, data) \
    Quad &rA = getReg(GET_HIGH_FOUR_BIT(data[index]));

#define GET_RB_FROM_MEM(index, data) \
    Quad &rB = getReg(GET_LOW_FOUR_BIT(data[index]));

#define GET_DATA_FROM_MEM(name, index, data) \
    Quad name = *((Quad*)(data + index));

typedef unsigned long long Quad;
typedef unsigned char Byte;

#define QUAD_DATA_LEN sizeof(Quad)

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

/// 标志位
struct Flag{
    unsigned char ZF: 1;
    unsigned char SF: 1;
    unsigned char OF: 1;
};

/// 错误码, 目前只有一个
#define ERROR_CODE -1
#define SUCCESS_CODE 0
#define ERROR_UN_INS 1

// Machine Instruction 机器指令
struct MachineInst {
    // 操作码
    Byte op_code;
    // 操作数
    Byte byte;
    // 附加立即数
    Quad other;
    // 指令字节
    unsigned char byteLen;
};

// Assembly Instruction 汇编指令
struct AssemblyInst{
    std::string inst;
    std::vector<std::string> opcode;
};


#endif //Y8664_CONFIG_H
