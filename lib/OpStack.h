//
// Created by Andrey on 17.04.2019.
//

#ifndef HYDROLIB2_OPSTACK_H
#define HYDROLIB2_OPSTACK_H

#include "hydro_types.h"

class OpStack {
    uint8_t mData[100];
    uint8_t mPointer;
public:
    void clear();

    void init(uint8_t *aData, uint8_t aSize) {
        memcpy(mData, aData, aSize);
        mPointer = aSize;
    }

    template <class T>
    void push(T aValue) {
        *(T*)(mData + mPointer) = aValue;
        mPointer += sizeof(T);
    }

    template <typename T>
    T pop() {
        mPointer -= sizeof(T);
        return *(T*)(mData + mPointer);
    }
};


#endif //HYDROLIB2_OPSTACK_H
