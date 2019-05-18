//
// Created by Andrey on 17.04.2019.
//

#include "Script.h"
#include "Operation.h"

Script::Script(Context &mContext) : mContext(mContext) {}

bool Script::execute() {
    mOpQueue.reset();

    while(mOpQueue.prepareStatement()) {
        mStack.clear();
        while(mOpQueue.inStatement()) {
            auto op = mOpQueue.pop<op_id_t>();
            op_func_t func = OPS2[op];
            op_result_t res = func(mContext, mOpQueue, mStack);
            if (Operation::RESULT_SKIP == res) {
                mOpQueue.skip();
            }
        }
    }
    return false;
}

void Script::addSetInt(var_id_t aVarRef) {
    mOpQueue.add(Operation::OP_SetInt);
    mOpQueue.add(aVarRef);
}

void Script::addGetInt(var_id_t aVarRef) {
    mOpQueue.add(Operation::OP_GetInt);
    mOpQueue.add(aVarRef);
}

void Script::addIfEvent(event_id_t aEventId) {
    mOpQueue.add(Operation::OP_IfEvent);
    mOpQueue.add(aEventId);
}

Script &Script::addOperation(op_id_t aOpId) {
    mOpQueue.add(aOpId);
    return *this;
}

Script &Script::endStatement() {
    mOpQueue.end();
    return *this;
}

Script &Script::addInt(int aData) {
    mOpQueue.add(Operation::OP_ArgInt);
    mOpQueue.add(aData);
    return *this;
}

Script &Script::addUint8(uint8_t aData) {
    // uint8 and int8 has the same size;
    mOpQueue.add(Operation::OP_ArgInt8);
    mOpQueue.add(aData);
    return *this;
}

Script & Script::addEvent(event_id_t aEventId) {
    mOpQueue.add(Operation::OP_ArgInt8);
    mOpQueue.add(aEventId);
    return *this;
}

Script & Script::addVarId(uint8_t aVarId) {
    mOpQueue.add(Operation::OP_ArgInt8);
    mOpQueue.add(aVarId);
    return *this;
}

Script Script::addSetObj(var_id_t aVarRef) {
    return *this;
}

Script Script::addGetObj(var_id_t aVarRef) {
    return *this;
}

