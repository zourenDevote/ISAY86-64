//
// Created by 20580 on 2022/10/18.
//
#include "ins_emulator/ins_emulator.h"
#include "util/util.h"
#include <cassert>
#include <iomanip>

using namespace std;

#define PCADD(x) *(decltype(x)*)(memory+pc) = x; pc += sizeof(x);

#define REG_TO_BYTE(name, bt)           \
    if(name == "rax") bt = RAX;         \
    else if(name == "rcx") bt = RCX;    \
    else if(name == "rbx") bt = RBX;    \
    else if(name == "rsp") bt = RSP;    \
    else if(name == "rbp") bt = RBP;    \
    else if(name == "rsi") bt = RSI;    \
    else if(name == "rdi") bt = RDI;    \
    else if(name == "r8")  bt = R8;     \
    else if(name == "r9")  bt = R9;     \
    else if(name == "r10") bt = R10;    \
    else if(name == "r11") bt = R11;    \
    else if(name == "r12") bt = R12;    \
    else if(name == "r13") bt = R13;    \
    else if(name == "r14") bt = R14;    \
    else assert(false && "Unknown register!");

#define GETREG(A, B) case A: \
    return regGroup.B;
Quad &InsEmulator::getReg(unsigned char number)
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

#define MEM_SIZE 1048576
InsEmulator::InsEmulator(): regGroup(), oldGroup(), flags(), oldFlags(), pc(0), memChangeAddr(0), msize(MEM_SIZE){
    memory = new unsigned char[MEM_SIZE];
}
#undef MEM_SIZE


InsEmulator::~InsEmulator() {
    delete[] memory;
}



ErrorOrSuccess InsEmulator::parseAndExecute(const std::vector<std::string>& ins) {

    saveOldRegsAndFlags();
    resetEmulatorFlag();
    if (ins[0] == "nop") {
        return nop();
    } else if (ins[0] == "halt") {
        return halt();
    } else if (ins[0] == "rrmovq"){
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return rrmovq(rAb| rBb);
    } else if(ins[0] == "irmovq"){
        Byte rBb;
        auto v = strToInt(ins[1]);
        REG_TO_BYTE(ins[2], rBb)
        return irmovq(rBb, v.as<Quad>());
    } else if(ins[0] == "rmmovq"){
        Byte rBb;
        auto v = strToInt(ins[2]);
        REG_TO_BYTE(ins[1], rBb)
        return rmmovq(rBb, v.as<Quad>());
    } else if(ins[0] == "mrmovq"){
        Byte rBb;
        auto v = strToInt(ins[1]);
        REG_TO_BYTE(ins[2], rBb)
        return mrmovq(rBb, v.as<Quad>());
    } else if(ins[0] == "addq"){
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return addq(rAb | rBb);
    } else if(ins[0] == "subq"){
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return subq(rAb | rBb);
    } else if(ins[0] == "andq"){
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return andq(rAb | rBb);
    } else if(ins[0] == "xorq"){
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return xorq(rAb | rBb);
    } else if(ins[0] == "cmovle") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmovle(rAb|rBb);
    } else if(ins[0] == "cmovl") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmovl(rAb|rBb);
    } else if(ins[0] == "cmove") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmove(rAb|rBb);
    } else if(ins[0] == "cmovne") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmovne(rAb|rBb);
    } else if(ins[0] == "cmovge") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmovge(rAb|rBb);
    } else if(ins[0] == "cmovg") {
        Byte rAb, rBb;
        REG_TO_BYTE(ins[1], rAb)
        REG_TO_BYTE(ins[2], rBb)
        return cmovg(rAb | rBb);
    } else if(ins[0] == "jmp") {
        auto dest = strToInt(ins[1]);
        return jmp(dest.as<Quad>());
    } else if(ins[0] == "jle") {
        auto dest = strToInt(ins[1]);
        return jle(dest.as<Quad>());
    } else if(ins[0] == "jl") {
        auto dest = strToInt(ins[1]);
        return jl(dest.as<Quad>());
    } else if(ins[0] == "je") {
        auto dest = strToInt(ins[1]);
        return je(dest.as<Quad>());
    } else if(ins[0] == "jne") {
        auto dest = strToInt(ins[1]);
        return jne(dest.as<Quad>());
    } else if(ins[0] == "jqe") {
        auto dest = strToInt(ins[1]);
        return jqe(dest.as<Quad>());
    } else if(ins[0] == "jq") {
        auto dest = strToInt(ins[1]);
        return jq(dest.as<Quad>());
    } else if(ins[0] == "call") {
        auto dest = strToInt(ins[1]);
        return call(dest.as<Quad>());
    } else if(ins[0] == "pushq") {
        Byte bt;
        REG_TO_BYTE(ins[1],bt)
        return pushq(bt);
    } else if(ins[0] == "popq") {
        Byte bt;
        REG_TO_BYTE(ins[1],bt)
        return popq(bt);
    } else if(ins[0] == "ret"){
        return ret();
    }
    return {ERROR_UN_INS, "Unknown Instruction"};
}

#define PER_ROW_NUMBER_COUNT sizeof(Quad)
void InsEmulator::printMemoryRange(Quad start, Quad end, std::ostream &out) const {
    if(end < start) return;
    if(start > msize) return;
    Quad currentAddr = start;
    int i = -1;
    while(currentAddr <= end){
        i = 0;
        out<<std::hex<<setw(8)<<setfill('0')<<currentAddr;
        out<<"-"<<std::hex<<setw(8)<<setfill('0')<<(currentAddr+8<end?currentAddr+8:end)<<": ";
        while(i < PER_ROW_NUMBER_COUNT && currentAddr <= end) {
            out<<std::hex<<setw(2)<<setfill('0')<<unsigned(memory[currentAddr])<<" ";
            currentAddr++;
            i++;
        }
        out<<"\n";
    }
    out<<"\n";
}

void InsEmulator::printCpuRegAndFlagMsg(std::ostream &out) const {
    out<<"RegGroup:\n";
    out<<"\tRAX = "<<hex<<setw(8)<<setfill('0')<<regGroup.rax<<",";
    out<<"RCX = "<<hex<<setw(8)<<setfill('0')<<regGroup.rcx<<"\n";
    out<<"\tRBX = "<<hex<<setw(8)<<setfill('0')<<regGroup.rbx<<",";
    out<<"RSP = "<<hex<<setw(8)<<setfill('0')<<regGroup.rsp<<"\n";
    out<<"\tRBP = "<<hex<<setw(8)<<setfill('0')<<regGroup.rbp<<",";
    out<<"RSI = "<<hex<<setw(8)<<setfill('0')<<regGroup.rsi<<"\n";
    out<<"\tRDI = "<<hex<<setw(8)<<setfill('0')<<regGroup.rdi<<",";
    out<<"R8 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r8<<"\n";
    out<<"\tR9 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r9<<",";
    out<<"R10 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r10<<"\n";
    out<<"\tR11 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r11<<",";
    out<<"R12 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r12<<"\n";
    out<<"\tR13 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r13<<",";
    out<<"R14 = "<<hex<<setw(8)<<setfill('0')<<regGroup.r14<<"\n";
    out<<"Flag:\n"<<"\tZF = "<<int(flags.ZF)<<", OF = "<<int(flags.OF)<<", SF = "<<int(flags.SF)<<"\n";
}

#define COMP_AND_COUT(out, reg, i) if(oldGroup.reg != regGroup.reg){ \
    if(i%2 == 0){                                                    \
        out<<#reg<<" = "<<hex<<setw(8)<<setfill('0')<<regGroup.reg<<" ";          \
    }else{                                                           \
        out<<#reg<<" = "<<hex<<setw(8)<<setfill('0')<<regGroup.reg<<"\n";          \
    }                                                                \
    i++;\
}

void InsEmulator::printEmuExecResult(std::ostream &out) const {
    int i = 0;
    bool isChangeFlag = false;
    COMP_AND_COUT(out, rax, i)
    COMP_AND_COUT(out, rcx, i)
    COMP_AND_COUT(out, rbx, i)
    COMP_AND_COUT(out, rsp, i)
    COMP_AND_COUT(out, rbp, i)
    COMP_AND_COUT(out, rsi, i)
    COMP_AND_COUT(out, rdi, i)
    COMP_AND_COUT(out, r8, i)
    COMP_AND_COUT(out, r9, i)
    COMP_AND_COUT(out, r10, i)
    COMP_AND_COUT(out, r11, i)
    COMP_AND_COUT(out, r12, i)
    COMP_AND_COUT(out, r13, i)
    COMP_AND_COUT(out, r14, i)
    if(i%2 == 0) out<<"\n";
    if(oldFlags.ZF != flags.ZF){out<<"ZF = "<<flags.ZF<<" "; isChangeFlag = true;}
    if(oldFlags.OF != flags.OF){out<<"OF = "<<flags.OF<<" "; isChangeFlag = true;}
    if(oldFlags.SF != flags.SF){out<<"SF = "<<flags.SF<<" "; isChangeFlag = true;}
    if(isChangeFlag){out<<"\n";}
    if(hasMemChange){
        printMemoryRange(memChangeAddr, memChangeAddr+size, out);
    }
    out<<"\n";
}

void InsEmulator::printInsEmuMsg(std::ostream &out) const {
    printCpuRegAndFlagMsg(out);
    printPcMsg(out);
}

void InsEmulator::printPcMsg(std::ostream &out) const {
    out<<"PC = "<<hex<<setw(8)<<setfill('0')<<pc<<"\n";
}

void InsEmulator::resetEmulatorFlag() {
    hasMemChange = false;
}

ErrorOrSuccess InsEmulator::nop() {
    PCADD((Byte)NOP)
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::halt() {
    PCADD((Byte)HALT)
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::rrmovq(Byte bt) {
    PCADD((Byte)RRMOVQ)
    PCADD(bt)
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = rA;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::irmovq(Byte bt, Quad val) {
    PCADD((Byte)IRMOVQ)
    PCADD(bt)
    PCADD(val)
    Quad &rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = val;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::rmmovq(Byte bt, Quad dest) {
    PCADD((Byte)RMMOVQ)
    PCADD(bt)
    PCADD(dest)
    Quad &rA = getReg(GET_HIGH_FOUR_BIT(bt));
    hasMemChange = true;
    memChangeAddr = dest;
    size = sizeof(Quad);
    *(Quad*)(memory + dest) = rA;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::mrmovq(Byte bt, Quad dest) {
    PCADD((Byte)RMMOVQ)
    PCADD(bt)
    PCADD(dest)
    Quad &rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = *(Quad*)(memory + dest);
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::addq(Byte bt) { PCADD((Byte)ADDQ) opemu(bt, 1); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::subq(Byte bt) { PCADD((Byte)SUBQ) opemu(bt, 2); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::andq(Byte bt) { PCADD((Byte)ANDQ) opemu(bt, 3); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::xorq(Byte bt) { PCADD((Byte)XORQ) opemu(bt, 4); return {SUCCESS_CODE, ""};}

ErrorOrSuccess InsEmulator::opemu(Byte bt, int op) {

    PCADD(bt)
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
    Quad res;
    switch (op) {
        case 1:  res = rA + rB; setCC(res, rA, rB,true); break;
        case 2:  res = rA - rB; setCC(res, rA, rB); break;
        case 3:  res = rA & rB; setCC(res, rA, rB); break;
        default: res = rA ^ rB; setCC(res, rA, rB); break;
    }
    rB = res;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmovle(Byte bt) {
    PCADD(bt)
    if((flags.SF ^ flags.OF) | flags.ZF) {
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmovl(Byte bt) {
    PCADD(bt)
    if(flags.SF ^ flags.OF){
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmove(Byte bt) {
    PCADD(bt)
    if(flags.ZF) {
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmovne(Byte bt) {
    PCADD(bt)
    if(~flags.ZF) {
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmovge(Byte bt) {
    PCADD(bt)
    if(~(flags.SF ^ flags.OF)) {
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::cmovg(Byte bt) {
    PCADD(bt)
    if((~(flags.SF ^ flags.OF)) & (~flags.ZF)) {
        Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
        Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
        rB = rA;    
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jmp(Quad dest) {
    PCADD(dest)
    /// @todo 需要检测dest是否超过目标地址
    pc = dest;
    int i = 0;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jle(Quad dest) {
    PCADD(dest)
    if((flags.SF ^ flags.OF) | flags.ZF) {
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jl(Quad dest) {
    PCADD(dest)
    if(flags.SF ^ flags.OF) {
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::je(Quad dest) {
    PCADD(dest)
    if(flags.ZF) {
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jne(Quad dest) {
    PCADD(dest)
    if(~flags.ZF){
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jqe(Quad dest) {
    PCADD(dest)
    if(~(flags.SF ^ flags.OF)){
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::jq(Quad dest) {
    PCADD(dest)
    if((~(flags.SF ^ flags.OF)) & ~flags.ZF){
        pc = dest;
    }
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::call(Quad dest) {
    PCADD(dest)
    popq(pc);
    pc = dest;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::pushq(Byte bt) {
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    // @todo 需要有堆栈溢出的判断
    *(Quad*)(memory+regGroup.rsp) = rA;
    regGroup.rsp += sizeof (Quad);
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::popq(Byte bt) {
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    // @todo 需要添加堆栈溢出的判断
    rA = *(Quad*)(memory+regGroup.rsp);
    regGroup.rsp -= sizeof (Quad);
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::ret() {
    pc = *(Quad*)(memory+regGroup.rsp);
    regGroup.rsp -= sizeof(Quad);
    return {SUCCESS_CODE, ""};
}

void InsEmulator::setCC(Quad res, Quad rA, Quad rB, bool isAdd) {
    if(isAdd){
        if(res < rA || res < rB) {setOFFlag();}
        else{resetOFFlag();}
    }
    else{resetOFFlag();}

    if(res | ZF_MASK){setZFFlag();}
    else{resetZFFlag();}

    if(res & SF_MASK){setSFFlag();}
    else{resetSFFlag();}
}


