//
// Created by 20580 on 2022/10/18.
//
#include <iostream>
#include <cstring>
#include <iomanip>
#ifdef GNU
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include "ins_emulator.h"
#include "../util/util.h"
#include "../third_party/cxxopts.hpp"
#include "../assember/assember_support.h"
#include "../third_party/antlr4/runtime/src/antlr4-runtime.h"
#include "../assember/grammer/ParserParser.h"
#include "../assember/grammer/ParserLexer.h"

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
    printf("PC = %#018lx\n", emulator->getPcValue());
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
        return false;
    }

    if(insSplit[0] == "showpc"){
        emulator->printPcMsg();
    }
    else if(insSplit[0] == "showreg"){
        emulator->printCpuRegAndFlagMsg();
    }
    else if(insSplit[0] == "showmem"){
        auto start = strToInt(insSplit[1]);
        auto end = strToInt(insSplit[2]);
        if(start.code() || end.code()){
            std::cerr << "Error memory range was given\n";
            return false;
        }
        emulator->printMemoryRange(start.as<Quad>(), end.as<Quad>());
    }
    else if(insSplit[0] == "cls" || insSplit[0] == "clear") {
        system("cls");
    }
    else{
        AssemblyInst inst;
        inst.inst = insSplit[0];
        if(insSplit.size() > 1){
            inst.opcode.assign(insSplit.begin()+1, insSplit.end());
        }
        auto machineCode = AssemblyConverter::getInstance()->assembly(inst);
        if(machineCode.code()){
            std::cout<<"Unknown Instruction!\n";
            return false;
        }
        auto res = emulator->parseAndExecute(machineCode.as<MachineInst>());
        if(res.code()) {exitWithErrorCode(res);}
        else {
            printPc();
            // 打印汇编指令
            cout <<"Ox"<<hex<<setw(16)<<setfill('0')<<emulator->getOldPcValue()<<": ";
            cout << inst.inst << " ";
            unsigned i = inst.opcode.size() - 1;
            for(unsigned j = 0 ; j < inst.opcode.size(); j++) {
                if(j == i)
                    cout << inst.opcode[j];
                else
                    cout << inst.opcode[j] << ", ";
            }
            cout<<endl;
            emulator->printEmuExecResult();
        }
    }
    return true;
}

void domain(int argc, char* argv[]) {

    cxxopts::Options opt{"Y8664Emulator", ""};

    opt.add_options()
    ("h,help", "Get help for this program.")
    ("i,input", "The filepath of input assembly file.", cxxopts::value<std::string>())
    ("o,output", "The output filepath of this file.", cxxopts::value<std::string>()->default_value("a.elf"))
    ("e,elf", "The filepath of elf file.", cxxopts::value<std::string>());

    std::string inputPath;

    auto res= opt.parse(argc, argv);
    if(res.count("help") || res.count("h")) {
        cout << opt.help();
        ::exit(0);
    }

    if(res.count("i") || res.count("input")) {
        inputPath = res["input"].as<std::string>();
    }

    std::string outPath = res["output"].as<std::string>();
    if(res.count("e") || res.count(("elf"))) {
        inputPath = res["elf"].as<std::string>();
    }

    /// 首先做一个简单的识别器，.s文件介绍自己定义一个格式
    if(endsWith(inputPath, ".s")) {
        antlr4::ANTLRFileStream stream;
        stream.loadFromFile(inputPath);

        ParserLexer lexer(&stream);

        antlr4::CommonTokenStream token(&lexer);

        ParserParser parser(&token);

        for(const auto& tk : lexer.getAllTokens()) {
            cout << tk->toString() << endl;
        }
    }
    else if(endsWith(inputPath, ".elf")) {

    }

}

int main(int argc, char* argv[]){
    domain(argc, argv);
//    char ins[256];
//    string inst;
//    emulator = new InsEmulator();
//
//    // 执行指令模拟执行
//    while(true){
//        // 1. 读取一条指令
//        cout<<"Y8664InstEmulator>>:";
//        cin.getline(ins, 256);
//#ifdef GNU
//        add_history(ins);
//#endif
//        inst = ins;
//        if(strcmp(ins, "exit") == 0
//           || strcmp(ins, "quit") == 0){
//            cout<<"Program exit\n";
//            break;
//        }
//        // 2. 解析并执行指令
//        parseAndExecuteInst(inst);
//    }
//    delete emulator;
}

