/**
 * 定义我的可执行文件的elf格式
 */

#ifndef Y8664_MY_ELF_H
#define Y8664_MY_ELF_H

#define MAGIC "ELF_MGIC"
#include <vector>

struct Section{
    unsigned int offset;  // 偏移量
    unsigned int size;    // 大小
};

typedef struct {
    Quad magic;
    Section code;           // 代码段
    Section data;           // 数据段
    Quad stackOff;          // 栈指针
    std::size_t stackSize;  // 栈大小
} ElfHeader;


#endif //Y8664_MY_ELF_H
