//
// Created by 20580 on 2023/1/5.
//
#include "assember_support.h"
#include "../util/util.h"
#include <sstream>
#include <cstring>
#include <unordered_map>

std::string intToHexStr(Quad v) //transfer string to hex-string
{
    std::string result = "0x";
    std::stringstream ss;
    ss << std::hex << v;
    result += ss.str();
    return result;
}

const std::unordered_map<Byte , std::string> regMap{
        {RAX, "rax"}, {RCX, "rcx"}, {RBX, "rbx"}, {RSP, "rsp"},
        {RBP, "rbp"}, {RSI, "rsi"}, {RDI, "rdi"}, {R8, "r8"},
        {R9, "r9"}, {R10, "r10"}, {R11, "r11"}, {R12, "r12"},
        {R13, "r13"}, {R14, "r14"}
};


ErrorOrSuccess getReg(Byte byte) {
    auto it = regMap.find(byte);
    if(it != regMap.end())
        return {SUCCESS_CODE, *it};
    return {ERROR_CODE, ERROR_CODE};
}

static ErrorOrSuccess getReg(const std::string& reg) {
    for(const auto& it : regMap) {
        if(strcmp(it.second.c_str(), reg.c_str()) == 0)
            return {SUCCESS_CODE, it.first};
    }
    return {ERROR_CODE, ERROR_CODE};
}

const std::unordered_map<Byte , std::string> assemblyMap{
        {HALT, "halt"}, {NOP, "nop"}, {RRMOVQ, "rrmovq"}, {IRMOVQ, "irmovq"},
        {RMMOVQ, "rmmovq"}, {MRMOVQ, "mrmovq"}, {ADDQ, "addq"}, {SUBQ, "subq"},
        {ANDQ, "andq"}, {XORQ, "xorq"}, {JMP, "jmp"}, {JLE, "jle"},
        {JL, "jl"}, {JE, "je"}, {JNE, "jne"}, {JQE, "jqe"},
        {JQ, "jq"}, {CMOVLE, "cmovle"}, {CMOVL, "cmovl"}, {CMOVNE, "cmovne"},
        {CMOVGE, "cmovge"}, {CMOVG, "cmovg"}, {CALL, "call"}, {RET, "ret"},
        {PUSHQ, "pushq"}, {POPQ, "popq"}
};

// 汇编代码转换成机器码
ErrorOrSuccess assemblyToCode(const std::string& inst) {
    for(const auto& it : assemblyMap) {
        if(strcmp(it.second.c_str(), inst.c_str()) == 0)
            return {SUCCESS_CODE, it.first};
    }
    return {ERROR_CODE, ERROR_CODE};
}

ErrorOrSuccess assemblyToCode(Byte byte) {
    auto it = regMap.find(byte);
    if(it != regMap.end())
        return {SUCCESS_CODE, *it};
    return {ERROR_CODE, ERROR_CODE};
}

DisAssemblyConverter* DisAssemblyConverter::instance = nullptr;

DisAssemblyConverter *DisAssemblyConverter::getInstance() {
    if(instance == nullptr) {
        instance = new DisAssemblyConverter();
    }
    return instance;
}

ErrorOrSuccess DisAssemblyConverter::disassembly(const MachineInst &inst) {
    switch (inst.op_code) {
        case HALT: { return {SUCCESS_CODE, AssemblyInst{"halt", {}}};}
        case NOP: { return {SUCCESS_CODE, AssemblyInst{"nop", {}}}; }
        case RRMOVQ: {
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"rrmovq", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case IRMOVQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            if(res1.code())
                return {ERROR_CODE, ERROR_CODE};
            auto imm = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"irmovq", {res1.as<std::string>(), imm}}};
        }
        case RMMOVQ: {
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            if (res1.code())
                return {ERROR_CODE, ERROR_CODE};
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"irmovq", {res1.as<std::string>(), dest}}};
        }
        case MRMOVQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            if(res1.code())
                return {ERROR_CODE, ERROR_CODE};
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"mrmovq", {res1.as<std::string>(), dest}}};
        }
        case ADDQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"addq", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case SUBQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"subq", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case ANDQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"andq", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case XORQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"xorq", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case JMP:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jmp", {dest}}};
        }
        case JLE:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jle", {dest}}};
        }
        case JL:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jl", {dest}}};
        }
        case JE:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"je", {dest}}};
        }
        case JNE:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jne", {dest}}};
        }
        case JQE:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jqe", {dest}}};
        }
        case JQ:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"jq", {dest}}};
        }
        case CMOVLE:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmovle", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CMOVL:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmovl", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CMOVE:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmove", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CMOVNE:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmovne", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CMOVGE:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmovge", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CMOVG:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            auto res2 = getReg(GET_LOW_FOUR_BIT(inst.byte));
            if(res1.code() || res2.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"cmovg", {res1.as<std::string>(), res2.as<std::string>()}}};
        }
        case CALL:{
            auto dest = intToHexStr(inst.other);
            return {SUCCESS_CODE, AssemblyInst{"call", {dest}}};
        }
        case RET:{
            return {SUCCESS_CODE, AssemblyInst{"ret"}};
        }
        case PUSHQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            if(res1.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"pushq", {res1.as<std::string>()}}};
        }
        case POPQ:{
            auto res1 = getReg(GET_HIGH_FOUR_BIT(inst.byte));
            if(res1.code())
                return {ERROR_CODE, ERROR_CODE};
            return {SUCCESS_CODE, AssemblyInst{"popq", {res1.as<std::string>()}}};
        }
        default:
            return {ERROR_CODE, ERROR_CODE};
    }
}

AssemblyConverter* AssemblyConverter::instance = nullptr;

AssemblyConverter *AssemblyConverter::getInstance() {
    if(instance == nullptr) {
        instance = new AssemblyConverter();
    }
    return instance;
}

ErrorOrSuccess AssemblyConverter::assembly(const AssemblyInst &inst) {

    if(strcmp(inst.inst.c_str(), "halt") == 0) {
        if(inst.opcode.size() != 0)
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{HALT, 0, 0, 1}};
    }
    else if(strcmp(inst.inst.c_str(), "nop") == 0) {
        if(inst.opcode.size() != 0)
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{NOP, 0, 0, 1}};
    }
    else if(strcmp(inst.inst.c_str(), "rrmovq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{RRMOVQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "irmovq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto imm = strToInt(inst.opcode[0]);
        auto res1 = getReg(inst.opcode[1]);
        if(imm.code() || res1.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4);
        return {SUCCESS_CODE, MachineInst{IRMOVQ, bt, imm.as<Quad>(), 10}};
    }
    else if(strcmp(inst.inst.c_str(), "rmmovq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto imm = strToInt(inst.opcode[1]);
        if(imm.code() || res1.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4);
        return {SUCCESS_CODE, MachineInst{RMMOVQ, bt, imm.as<Quad>(), 10}};
    }
    else if(strcmp(inst.inst.c_str(), "mrmovq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto imm = strToInt(inst.opcode[0]);
        auto res1 = getReg(inst.opcode[1]);
        if(imm.code() || res1.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4);
        return {SUCCESS_CODE, MachineInst{MRMOVQ, bt, imm.as<Quad>(), 10}};
    }
    else if(strcmp(inst.inst.c_str(), "addq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{ADDQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "subq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{SUBQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "andq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{ANDQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "xorq") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{XORQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "jmp") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JMP, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "jle") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JLE, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "jl") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JL, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "je") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JE, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "jne") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JNE, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "jqe") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JQE, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "jq") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{JQ, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "cmovle") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVLE, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "cmovl") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVL, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "cmove") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVE, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "cmovne") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVNE, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "cmovge") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVGE, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "cmovg") == 0) {
        if(inst.opcode.size() != 2)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        auto res2 = getReg(inst.opcode[1]);
        if(res1.code() || res2.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4 | res2.as<Byte>());
        return {SUCCESS_CODE, MachineInst{CMOVG, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "call") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto dest = strToInt(inst.opcode[0]);
        if(dest.code())
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{CALL, 0, dest.as<Quad>(), 9}};
    }
    else if(strcmp(inst.inst.c_str(), "ret") == 0) {
        if(inst.opcode.size() != 0)
            return {ERROR_CODE, ERROR_CODE};
        return {SUCCESS_CODE, MachineInst{RET, 0, 0, 1}};
    }
    else if(strcmp(inst.inst.c_str(), "pushq") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        if(res1.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4);
        return {SUCCESS_CODE, MachineInst{PUSHQ, bt, 0, 2}};
    }
    else if(strcmp(inst.inst.c_str(), "popq") == 0) {
        if(inst.opcode.size() != 1)
            return {ERROR_CODE, ERROR_CODE};
        auto res1 = getReg(inst.opcode[0]);
        if(res1.code())
            return {ERROR_CODE, ERROR_CODE};
        Byte bt = (Byte)(res1.as<Byte>() << 4);
        return {SUCCESS_CODE, MachineInst{POPQ, bt, 0, 2}};
    }
    return {ERROR_CODE, ERROR_CODE};
}