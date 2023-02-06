//
// Created by 20580 on 2023/1/11.
//

#include "myelf.h"
#include <cassert>
#include <iomanip>
#include "../assember/assember_support.h"


ErrorOrSuccess dumpElfToFile(const MySimpleElf& elf, const std::string& filepath) {
    FILE* fp = fopen(filepath.c_str(), "wb");
    if(fp == NULL)
        assert(false && "Error to open file!");
    // 将文件头写入文件
    fwrite(&elf.header, sizeof (MyElfHeader), 1, fp);
    // 将代码写入elf文件, 此处写入需要优化
    for(const auto& bt : elf.codes)
        fwrite(&bt, sizeof (Byte), 1, fp);
    // 将数据写入elf文件, 此处写入需要优化
    for(const auto& bt : elf.datas)
        fwrite(&bt, sizeof (Byte), 1, fp);
    // 将符号表写入文件, symbols table
    fclose(fp);
    return {SUCCESS_CODE, SUCCESS_CODE};
}


ErrorOrSuccess readElfFromFile(MySimpleElf& elf, const std::string& filepath) {
    FILE *fp = fopen(filepath.c_str(), "rb+");
    if(fp == NULL)
        return {ERROR_CODE, ERROR_CODE};
    fread(&elf.header, sizeof(MyElfHeader), 1, fp);
//    if(elf.header.magic != ELF)
//        return {ERROR_CODE, ERROR_CODE};
    Byte bt;
    for(int i = 0 ; i < elf.header.code_size ; i++) {
        fread(&bt, sizeof(Byte), 1, fp);
        elf.codes.push_back(bt);
    }
    for(int i = 0 ; i < elf.header.data_size ; i++) {
        fread(&bt, sizeof(Byte), 1, fp);
        elf.datas.push_back(bt);
    }
    return {SUCCESS_CODE, SUCCESS_CODE};
}


ErrorOrSuccess readElfFromMemory(MySimpleElf& elf, unsigned char* ptr, Quad size) {

    return {SUCCESS_CODE, SUCCESS_CODE};
}

ErrorOrSuccess objdumpElf(const std::string& filepath,std::ostream& out) {
    MySimpleElf elf;
    auto res = readElfFromFile(elf, filepath);
    if(res.code())
        return res;

    Quad code_address = elf.header.code_entry;
    Quad data_address = elf.header.data_entry;

    out << "----------------------------------------\n";
    out << "MAGIC: ELF FILE\n";
    out << "MAIN ENTRY: " << elf.header.main_entry << "\n";
    out << "CODE ENTRY: " << elf.header.code_entry << "\n";
    out << "DATA_ENTRY: " << elf.header.data_entry << "\n";
    out << "STACK ENTRY: " << elf.header.stack_entry << "\n";
    out << "----------------------------------------\n";

    if(elf.codes.empty()) {
        out << "EMPTY CODE\n";
    }
    else {
        int i = 0;
        auto res = MachineInstConverter::getInstance()->readMachineInstFromBytes(elf.codes);
        auto disassember = DisAssemblyConverter::getInstance();
        if(res.code())
            return res;
        for(const auto& inst : res.as<std::vector<MachineInst>>()) {

            i = inst.byteLen;
            auto assembe_inst = disassember->disassembly(inst).as<AssemblyInst>();

            // 输出机器指令
            out << std::hex << std::setw(16) << std::setfill('0') << code_address << "  ";
            code_address += inst.byteLen;
            out << std::hex << std::setw(2) << std::setfill('0') << (int)inst.op_code;
            if (inst.byteLen == 2) {
                out << " " << std::hex << std::setw(2) << std::setfill('0') << (int)inst.byte;
            }
            else if(inst.byteLen == 9) {
                Byte *p = (Byte*)&inst.other;
                for(int k = 0; k < 8 ; k++) {
                        out << " " << std::hex << std::setw(2) << std::setfill('0') << (int)(*p++);
                }
            }
            else if(inst.byteLen == 10) {
                out  << " " << std::hex << std::setw(2) << std::setfill('0') << (int)inst.byte;
                Byte *p = (Byte*)&inst.other;
                for(int k = 0; k < 8 ; k++) {
                    out << " " << std::hex << std::setw(2) << std::setfill('0') << (int)(*p++);
                }
            }

            while((10-i) >= 0) {
                out << "   ";
                i++;
            }

            out << "\t";

            // 输出汇编指令
            out << assembe_inst.inst << " ";
            unsigned k = assembe_inst.opcode.size() - 1;
            for(unsigned j = 0 ; j < assembe_inst.opcode.size(); j++) {
                if(j == k)
                    out << assembe_inst.opcode[j];
                else
                    out << assembe_inst.opcode[j] << ", ";
            }
            out << "\n";
        }
    }
    out << "----------------------------------------\n";

    if(elf.datas.empty()) {
        out << "NO GLOBAL DATA\n";
    }
    else {
        int i = 0;
        for(const auto& byte : elf.datas) {
            if(i % 8 == 0) {
                out << std::hex << std::setw(16) << std::setfill('0') << data_address <<" ";
                out << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
            }
            else if((i + 1) % 8 == 0){
                out << std::hex << std::setw(2) << std::setfill('0') << (int)byte << "\n";
            }
            else {
                out << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
            }
            i++;
            data_address++;
        }

        if(i % 8 != 0)
            out << "\n";
    }
    out << "----------------------------------------\n";
    return {SUCCESS_CODE, SUCCESS_CODE};
}


