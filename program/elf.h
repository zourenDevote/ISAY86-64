//
// Created by 20580 on 2023/1/8.
//

#ifndef Y8664_PROGRAM_H
#define Y8664_PROGRAM_H

#include "../base.h"
#include <vector>
#include <string>

class Elf{
public:
    Elf(const std::string& name, const std::string& filepath);
    Quad getStackSize() const { return stack_size; }
    Quad getStackStartPtr() const { return stack_start_ptr; }
    Quad getDataSize() const { return data_size; }
    Quad getDataStartPtr() const { return data_start_ptr; }
    Quad getCodeSize() const { return code_size; }
    Quad getCodeStartPtr() const { return code_start_ptr; }

    void setStackSize(Quad v) { stack_size = v; }
    void setStackStartPtr(Quad v) { stack_start_ptr = v; }
    void setDataSize(Quad v) { data_size = v; }
    void setDataStartPtr(Quad v) { data_start_ptr = v; }
    void setCodeSize(Quad v) { code_size = v; }
    void setCodeStartPtr(Quad v) { code_start_ptr = v; }

    void addDatas(Quad v) { datas.push_back(v); data_size += sizeof (Quad); }
    void addCodes(const MachineInst& inst) { codes.push_back(inst); code_size += inst.byteLen; }

    void setProgramName(const std::string& name) { program_name = name; }
    void setFilepath(const std::string& path) { filepath = path; }
    std::string getProgramName() const { return program_name; }
    std::string getFilePath() const { return filepath; }
private:
    Quad stack_size;                 // 栈大小
    Quad stack_start_ptr;            // 栈起始指针
    Quad data_size;                  // 数据区大小
    Quad data_start_ptr;             // 数据区起始指针
    Quad code_size;                  // 代码区大小
    Quad code_start_ptr;             // 代码区开始地址
    std::vector<MachineInst> codes;  // 代码
    std::vector<Quad> datas;         // 数据
private:
    std::string program_name;         // 程序名称
    std::string filepath;            // 文件路径
};

#endif //Y8664_PROGRAM_H
