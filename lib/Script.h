//
// Created by Andrey on 17.04.2019.
//

#ifndef HYDROLIB2_SCRIPT_H
#define HYDROLIB2_SCRIPT_H

#include "hydro_types.h"
#include "Context.h"
#include "BinQueue.h"
#include "OpStack.h"
#include "Operation.h"

#define STACK_SIZE 100


class Script {
    OpStack mStack;
    BinQueue mOpQueue;
    Context &mContext;
public:
    Script(Context &mContext);

    Script & addData(int aData) {
        mOpQueue.add(Operation::OP_ArgInt);
        mOpQueue.add(aData);
        return *this;
    }

    Script & addOperation(op_id_t aOpId){
        mOpQueue.add(aOpId);
        return *this;
    }

    Script &endStatement() {
        mOpQueue.end();
        return *this;
    }

    bool execute();

    template <typename T>
    T pop() {
        return mStack.pop<T>();
    }

    void addVarId(uint8_t aVarId);

    void addSetInt(var_id_t aVarRef);
    void addGetInt(var_id_t aVarRef);

    /**
     * CheckEvent checks an event specified by arg and skips the current statement if event is not present.
     *
     * @param aEventId the event to check.
     */
    void addIfEvent(event_id_t aEventId);
};


#endif //HYDROLIB2_SCRIPT_H
