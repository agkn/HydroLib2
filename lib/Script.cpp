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
            if (Operation::OP_RESULT_SKIP == res) {
                mOpQueue.skip();
            }
        }
    }
    return false;
}

void Script::addVarId(uint8_t aVarId) {
    addData(aVarId);
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
