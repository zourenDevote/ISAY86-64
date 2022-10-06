//
// Created by 20580 on 2022/10/5.
//

#ifndef Y8664_MY_ELF_READER_H
#define Y8664_MY_ELF_READER_H

#include "../base.h"
#include "my_elf.h"
#include "buffer.h"
#include <unistd.h>
#include <string>


class MyElfReader{
    MyElfReader(const char* filepath);

    /// 读取文件头信息
    bool readHeader();
    /// 读取数据段信息
    bool readDataSection();
    /// 读取代码段信息
    bool readCodeSection();

private:
    FILE          *fp;          // 可执行文件句柄
    ElfHeader     header;       // 文件头
    BinaryBuffer  *codeBuffer;  // 代码缓存区
    BinaryBuffer  *dataBuffer;  // 数据缓存区
};


#endif //Y8664_MY_ELF_READER_H
