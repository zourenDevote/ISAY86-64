//
// Created by 20580 on 2022/10/5.
//

#include "my_elf_writer.h"

#define HEAD_LEN sizeof(Quad) + 6 * sizeof (unsigned int)

MyElfWriter::MyElfWriter(const char *filename) : Data(),
                                                 Code(),
                                                 stackSize(0),
                                                 dataSize(0),
                                                 codeSize(0)
                                                 {
    if(!(fp = fopen(filename, "wb+")))
    {
        perror("Unable to open file");
        exit(-1);
    }
}

MyElfWriter::~MyElfWriter()
{
    fclose(fp);
}

void MyElfWriter::writeData(Quad value)
{
    Data.push_back(value);
    dataSize += sizeof (Quad);
}

void MyElfWriter::writeIns(const Inst& ins)
{
    Code.push_back(ins);
    codeSize += ins.sz;
}

void MyElfWriter::dump() {

    unsigned int codeOffset = HEAD_LEN;
    unsigned int dataOffset = codeSize + codeOffset;
    unsigned int stackOffset = codeSize + dataOffset + stackSize;

    fwrite((void*)MAGIC, sizeof (unsigned char), sizeof (Quad), fp);
    fwrite(&codeOffset, sizeof (unsigned int), 1, fp);
    fwrite(&codeSize, sizeof (unsigned int), 1, fp);
    fwrite(&dataOffset, sizeof (unsigned int), 1, fp);
    fwrite(&dataSize, sizeof (unsigned int), 1, fp);
    fwrite(&stackOffset, sizeof (unsigned int), 1, fp);
    fwrite(&stackSize, sizeof (unsigned int), 1, fp);

    for(const auto& ins : Code){
        fwrite(ins.ptr, sizeof (unsigned char), ins.sz, fp);
    }

    for(const auto& data : Data){
        fwrite(&data, sizeof (Quad), 1, fp);
    }
}

void MyElfWriter::setStackSize(Quad sz) {
    stackSize = sz;
}

