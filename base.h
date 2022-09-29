//
// Created by 20580 on 2022/9/26.
//

#ifndef Y8664_CONFIG_H
#define Y8664_CONFIG_H

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
#define COMVL   0x22
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
#define INS_TWO 2
#define INS_NINE 9
#define INS_TEN 10

#define SF_MASK 0x8000000000000000
#define ZF_MASK 0x0000000000000000

typedef unsigned long int Quad;

#define QUAD_DATA_LEN sizeof(Quad)


#endif //Y8664_CONFIG_H
