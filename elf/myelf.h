//
// Created by 20580 on 2023/1/11.
//

#ifndef Y8664_MYELF_H
#define Y8664_MYELF_H

#include "../base.h"
#include "../error/error.h"

/**
 * 自定义的一个简单的elf文件格式
 * 包括
 * ---------------
 *  简单的文件头介绍
 *  main主函数入口
 *   code代码段
 *   data数据段
 *   stack栈声明
 * ---------------
 */


struct Symbol {
    char syn_name[64];
    Quad addr;
};

#define ELF 0x00ff

struct MyElfHeader {
    /// magic 模数，代表elf文件的类型，目前仅仅是可执行文件，后续可能会考虑链接
    int magic;
    /// main函数入口地址
    Quad main_entry;
    /// 代码段的初始地址
    Quad code_entry;
    /// 代码段大小
    Quad code_size;
    /// 数据段的初始地址
    Quad data_entry;
    /// 数据段的大小
    Quad data_size;
    /// 栈的地址
    Quad stack_entry;
    /// 栈的大小
    Quad stack_size;
    /// 符号表的位置
    Quad symbol_entry;
};


struct MySimpleElf {
    MyElfHeader header;
    std::vector<Byte> codes;
    std::vector<Byte> datas;
    std::vector<Symbol> symbols;
};


/// 将elf数据结构序列化到文件中
ErrorOrSuccess dumpElfToFile(const MySimpleElf& elf, const std::string& filepath);
/// 从文件中读取ELF文件
ErrorOrSuccess readElfFromFile(MySimpleElf& elf, const std::string& filepath);
/// 从内存中读取ELF文件
ErrorOrSuccess readElfFromMemory(MySimpleElf& elf, unsigned char* ptr, Quad size);

ErrorOrSuccess objdumpElf(const std::string& filepath, std::ostream& out = std::cout);

#endif //Y8664_MYELF_H

