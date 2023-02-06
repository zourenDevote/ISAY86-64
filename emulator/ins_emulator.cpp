//
// Created by 20580 on 2022/10/18.
//
#include "ins_emulator.h"
#include <cassert>
#include <iomanip>

using namespace std;

#define PCADD(x) *(decltype(x)*)(memory+pc) = x; pc += sizeof(x);

#define GETREG(A, B) case A: \
    return regGroup.B;
Quad &InsEmulator::getReg(Byte number)
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
    regGroup.rsp = ((MEM_SIZE/sizeof (Quad))/2) * sizeof (Quad);
    memory = new Byte[MEM_SIZE];
}
#undef MEM_SIZE


InsEmulator::~InsEmulator() {
    delete[] memory;
}



ErrorOrSuccess InsEmulator::parseAndExecute(const MachineInst& ins) {
    saveOldRegsAndFlags();
    resetEmulatorFlag();
    PCADD(ins.op_code);
    switch (ins.op_code) {
        case HALT:
            halt();
            break;
        case NOP:
            nop();
            break;
        case RRMOVQ:
            rrmovq(ins.byte);
            break;
        case IRMOVQ:
            irmovq(ins.byte, ins.other);
            break;
        case RMMOVQ:
            rmmovq(ins.byte, ins.other);
            break;
        case MRMOVQ:
            mrmovq(ins.byte, ins.other);
            break;
        case ADDQ:
            addq(ins.byte);
            break;
        case SUBQ:
            subq(ins.byte);
            break;
        case ANDQ:
            andq(ins.byte);
            break;
        case XORQ:
            xorq(ins.byte);
            break;
        case JMP:
            jmp(ins.other);
            break;
        case JLE:
            jle(ins.other);
            break;
        case JL:
            jl(ins.other);
            break;
        case JE:
            je(ins.other);
            break;
        case JNE:
            jne(ins.other);
            break;
        case JQE:
            jqe(ins.other);
            break;
        case JQ:
            jq(ins.other);
            break;
        case CMOVLE:
            cmovle(ins.byte);
            break;
        case CMOVL:
            cmovl(ins.byte);
            break;
        case CMOVE:
            cmove(ins.byte);
            break;
        case CMOVNE:
            cmovne(ins.byte);
            break;
        case CMOVGE:
            cmovge(ins.byte);
            break;
        case CALL:
            call(ins.other);
            break;
        case RET:
            ret();
            break;
        case PUSHQ:
            pushq(ins.byte);
            break;
        case POPQ:
            popq(ins.byte);
            break;
        default:
            return {ERROR_UN_INS, "Unknown Instruction"};
    }
    return {SUCCESS_CODE, ""};
}

#define PER_ROW_NUMBER_COUNT sizeof(Quad)
void InsEmulator::printMemoryRange(Quad start, Quad end, std::ostream &out) const {
    if(end < start) return;
    if(start > msize) return;
    Quad currentAddr = start;
    int i = -1;
    while(currentAddr < end){
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
    isChangeFlag = true;\
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
    if(isChangeFlag) {out<<"\n"; isChangeFlag = false;}
    if(oldFlags.ZF != flags.ZF){out<<"ZF = "<<unsigned(flags.ZF)<<" "; isChangeFlag = true;}
    if(oldFlags.OF != flags.OF){out<<"OF = "<<unsigned(flags.OF)<<" "; isChangeFlag = true;}
    if(oldFlags.SF != flags.SF){out<<"SF = "<<unsigned(flags.SF)<<" "; isChangeFlag = true;}
    if(hasMemChange){
        if(isChangeFlag) {out << "\n"; isChangeFlag = false;}
        printMemoryRange(memChangeAddr, memChangeAddr+size, out);
    }
    if(isChangeFlag)
        out << "\n";
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
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::halt() {
    // @todo need do something
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::rrmovq(Byte bt) {
    PCADD(bt)
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    Quad& rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = rA;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::irmovq(Byte bt, Quad val) {
    PCADD(bt)
    PCADD(val)
    Quad &rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = val;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::rmmovq(Byte bt, Quad dest) {
    PCADD(bt)
    PCADD(dest)
    Quad &rA = getReg(GET_HIGH_FOUR_BIT(bt));
    hasMemChange = true;
    memChangeAddr = dest;
    size = sizeof(Quad);
    *((Quad*)(memory + dest)) = rA;
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::mrmovq(Byte bt, Quad dest) {
    PCADD(bt)
    PCADD(dest)
    Quad &rB = getReg(GET_LOW_FOUR_BIT(bt));
    rB = *(Quad*)(memory + dest);
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::addq(Byte bt) {opemu(bt, 1); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::subq(Byte bt) {opemu(bt, 2); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::andq(Byte bt) {opemu(bt, 3); return {SUCCESS_CODE, ""};}
ErrorOrSuccess InsEmulator::xorq(Byte bt) {opemu(bt, 4); return {SUCCESS_CODE, ""};}

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
    PCADD(bt)
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    // @todo 需要有堆栈溢出的判断
    *(Quad*)(memory+regGroup.rsp) = rA;
    regGroup.rsp += sizeof (Quad);
    return {SUCCESS_CODE, ""};
}

ErrorOrSuccess InsEmulator::popq(Byte bt) {
    PCADD(bt)
    Quad& rA = getReg(GET_HIGH_FOUR_BIT(bt));
    // @todo 需要添加堆栈溢出的判断
    regGroup.rsp -= sizeof (Quad);
    rA = *(Quad*)(memory+regGroup.rsp);
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


