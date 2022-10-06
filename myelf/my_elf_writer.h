//
// Created by 20580 on 2022/10/5.
//

#ifndef Y8664_MY_ELF_WRITER_H
#define Y8664_MY_ELF_WRITER_H

#include "../base.h"
#include "my_elf.h"
#include "buffer.h"
#include <string>
#include <array>

struct Inst{
    Inst(size_t sz, unsigned char* ptr): sz(sz), ptr(ptr){}
    unsigned char* ptr;
    size_t sz;
};

class MyElfWriter{
public:
    MyElfWriter(const char* filename);
    ~MyElfWriter();

    /// 写入一个数据
    void writeData(Quad value);
    /// 写入一条指令
    void writeIns(const Inst& ins);
    /// 设置栈的大小
    void setStackSize(Quad sz);
    /// 组织到文件中
    void dump();
private:
    FILE *fp;
    std::vector<Quad> Data;
    std::vector<Inst> Code;
    size_t dataSize;
    size_t codeSize;
    Quad stackSize;
};

#endif //Y8664_MY_ELF_WRITER_H
