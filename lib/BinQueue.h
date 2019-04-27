//
// Created by Andrey on 20.04.2019.
//

#ifndef HYDROLIB2_BINSTACK_H
#define HYDROLIB2_BINSTACK_H

#include "hydro_types.h"

#define BQ_HEADER_SIZE sizeof(uint8_t)
class BinQueue {
public:
    uint8_t mData[100];
    uint8_t mSize;
    /** the current get position */
    uint8_t mPopPointer;
    uint8_t mStatementPointer;

    BinQueue() : mData(), mSize(), mPopPointer(), mStatementPointer() {clear();}

    void reset() {
        mPopPointer = mStatementPointer = 0;
    }

    template <class T>
    void add(T aValue) {
        *(T *)(mData + mSize) = aValue;
        mSize += sizeof(T);
    }

    template <typename T>
    T pop() {
        T val = *(T *)(mData + mPopPointer);
        mPopPointer += sizeof(T);
        return val;
    }

    /**
     * Commit the current statement has been ended.
     */
    void end() {
        mData[mStatementPointer] = mSize - mStatementPointer;
        mStatementPointer = mSize;
        add((uint8_t)0);
    }

    /**
     * Check if statement is valid  and ready for execution.
     */
    bool prepareStatement() {
        uint8_t size = mData[mStatementPointer];
        if (!size) {
            // if size == 0 it means the last statement.
            return false;
        }

        // the first statement: mPopPointer = mStatementPointer = 0
        // after last pop: mPopPointer = mStatementPointer + size

        if (mStatementPointer + size == mPopPointer) {
            mStatementPointer = mPopPointer;
        }

        if (mPopPointer == mStatementPointer) {
            mPopPointer = mStatementPointer + BQ_HEADER_SIZE;
            return inStatement();
        }

        return false;
    }

    void clear() {
        mStatementPointer = mSize = mPopPointer = 0;
        add((uint8_t)0);
    }

    void skip() {
        mPopPointer = mStatementPointer + mData[mStatementPointer];
    }

    bool inStatement() {
        return mPopPointer < mStatementPointer + mData[mStatementPointer];
    }
};


#endif //HYDROLIB2_BINSTACK_H
