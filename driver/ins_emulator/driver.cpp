//
// Created by 20580 on 2022/10/18.
//
#include <iostream>
#include <cstring>
#include "util/util.h"
#include "ins_emulator/ins_emulator.h"

using namespace std;

InsEmulator* emulator = nullptr;

#define PRINT_REG(regA, X) printf(#regA);printf(" = %#016lx ", X.regA);
#define ENDL printf("\n");

/// 打印寄存器信息
void printAllRegGroup(){
    auto regs = emulator->getRegGroup();
    PRINT_REG(rax, regs)
    PRINT_REG(rcx, regs)
    ENDL

    PRINT_REG(rdx, regs)
    PRINT_REG(rbx, regs)
    ENDL

    PRINT_REG(rsp, regs)
    PRINT_REG(rbp, regs)
    ENDL

    PRINT_REG(rdi, regs)
    ENDL

    PRINT_REG(r8, regs)
    PRINT_REG(r9, regs)
    ENDL

    PRINT_REG(r10, regs)
    PRINT_REG(r11, regs)
    ENDL

    PRINT_REG(r12, regs)
    PRINT_REG(r13, regs)
    ENDL

    PRINT_REG(r14, regs)
    ENDL

    PRINT_REG(rsi, regs)
    ENDL
}

/// 打印PC的信息
void printPc(){
    printf("PC: %#016lx\n", emulator->getPcValue());
}

/// 解析和执行指令
bool parseAndExecuteInst(string& ins){

    if(ins == "help") {
        cout<<"Y8664 Emulator:\n-------------------------\n";
        cout<<"Usage:\n";
        cout<<"\tshowpc ---- 显示程序计数器的值\n";
        cout<<"\tshowreg ---- 显示寄存器的值\n";
        cout<<"\tshowmem ---- 显示内存位置\n";
        cout<<"\tclear/cls ---- 清空屏幕\n";
        return true;
    }

    // 拆分指令
    replace(ins, ',', ' ');
    replace(ins, ';', ' ');
    auto insSplit = split(ins, ' ');

    if(insSplit.empty()){
        cerr<<"No inst input!\n";
        return true;
    }

    if(insSplit[0] == "showpc"){
        emulator->printPcMsg();
    }
    else if(insSplit[0] == "showreg"){
        emulator->printCpuRegAndFlagMsg();
    }
    else if(insSplit[0] == "showmem"){
        emulator->printMemoryRange(Quad(atoi(insSplit[1].c_str())),
                                   Quad(atoi(insSplit[2].c_str())));
    }
    else if(insSplit[0] == "cls" || insSplit[0] == "clear") {
        system("cls");
    }
    else{
        auto res = emulator->parseAndExecute(insSplit); emulator->printEmuExecResult();
        if(res.code()) {exitWithErrorCode(res);}
    }
    return true;
}

int main(){

    char ins[256];
    string inst;
    emulator = new InsEmulator();

    // 执行指令模拟执行
    while(true){
        // 1. 读取一条指令
        cout<<"Y8664InstEmulator>>:";
        cin.getline(ins, 256);
        inst = ins;

        if(strcmp(ins, "exit") == 0
           || strcmp(ins, "quit") == 0){
            cout<<"Program exit\n";
            break;
        }

        // 2. 解析并执行指令
        parseAndExecuteInst(inst);
    }
}

