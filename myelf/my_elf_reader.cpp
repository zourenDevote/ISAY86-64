//
// Created by 20580 on 2022/10/5.
//

#include <cstring>
#include "my_elf_reader.h"


MyElfReader::MyElfReader(const char *filepath): header(){
    if(!(fp = fopen(filepath, "rb+"))){
        perror("Unable to open file!");
        exit(-1);
    }
    codeBuffer = nullptr;
    dataBuffer = nullptr;
}

bool MyElfReader::readHeader(){

    fread(&header.magic, sizeof (Quad), 1, fp);
    if(header.magic != *((Quad*)MAGIC)){
        return false;
    }

    fread(&header.code.offset, sizeof (header.code.offset), 1, fp);
    fread(&header.code.size, sizeof (header.code.size), 1, fp);
    fread(&header.data.offset, sizeof (header.data.offset), 1, fp);
    fread(&header.data.size, sizeof (header.data.size), 1, fp);
    fread(&header.stackOff, sizeof (header.stackOff), 1, fp);
    fread(&header.stackSize, sizeof (header.stackSize), 1, fp);
    return true;
}

bool MyElfReader::readDataSection() {
    dataBuffer = new BinaryBuffer(ReadOnly, header.data.size);
    fseek(fp, (long)header.data.offset, SEEK_SET);
    fread(dataBuffer->get(), sizeof (unsigned char), header.data.size, fp);
    return true;
}

bool MyElfReader::readCodeSection() {
    codeBuffer = new BinaryBuffer(ReadOnly, header.code.size);
    fseek(fp, (long)header.code.offset, SEEK_SET);
    fread(codeBuffer->get(), sizeof (unsigned char), header.code.size, fp);
    return true;
}

