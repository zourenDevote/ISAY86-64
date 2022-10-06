//
// Created by 20580 on 2022/10/6.
//

#ifndef Y8664_BUFFER_H
#define Y8664_BUFFER_H

#include <memory>

enum FileLoc{
    HD, // 文件头
    TL, // 文件结尾
};

enum BFlag{
    ReadOnly,
    WriteOnly,
    Both
};

class BinaryBuffer{
public:
    BinaryBuffer(BFlag fg, unsigned int sz);
    BinaryBuffer(const BinaryBuffer&) = delete;
    BinaryBuffer(BinaryBuffer&&) = delete;
    ~BinaryBuffer();

    unsigned char* get() { return bufPtr; }

    /// 读取一个值
    bool read(unsigned char& value);
    /// 写入一个值
    bool write(unsigned char value);

    /// 将指针设置回文件
    inline void toHead();
    inline void toTail();
    inline void seek(FileLoc loc, int i);
    inline unsigned int getBufSize() const { return size; }
protected:
    const BFlag flag;
    unsigned int size;
    unsigned int curInd;
    unsigned char *bufPtr;
};

#endif //Y8664_BUFFER_H
