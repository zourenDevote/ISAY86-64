//
// Created by 20580 on 2022/10/6.
//
#include "buffer.h"

BinaryBuffer::BinaryBuffer(BFlag fg, unsigned int sz) : size(sz),
                                                        curInd(0),
                                                        flag(fg),
                                                        bufPtr(new unsigned char [sz]){
}

BinaryBuffer::~BinaryBuffer() {
    delete[] bufPtr;
}

bool BinaryBuffer::read(unsigned char &value) {
    if(curInd >= size){
        return false;
    }
    value = *(bufPtr+curInd);
    curInd++;
    return true;
}

bool BinaryBuffer::write(unsigned char value) {
    if(curInd >= size){
        return false;
    }
    *(bufPtr+curInd) = value;
    curInd++;
    return true;
}

void BinaryBuffer::seek(FileLoc loc, int i) {
    if(loc == HD){
        curInd = i;
    }else if(loc == TL){
        curInd = size - (i+1);
    }
}

void BinaryBuffer::toHead() { seek(HD, 0); }

void BinaryBuffer::toTail() { seek(TL, 0); }
