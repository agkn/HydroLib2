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
    explicit Script(Context &mContext);

    /**
     * This value will be pushed to the stack during execution.
     *
     * @param aData A data to be pushed to the stack.
     * @return
     */
    Script & addUint8(uint8_t aData);

    /**
     * This value will be pushed to the stack during execution.
     *
     * @param aData A data to be pushed to the stack.
     * @return
     */
    Script & addInt(int aData);

    /**
     * This value will be pushed to the stack during execution.
     *
     * @param aEventId A data to be pushed to the stack.
     * @return
     */
    Script & addEvent(event_id_t aEventId);

    /**
     * A var reference will be pushed to the stack during execution.
     *
     * @param aVarId A data to be pushed to the stack.
     * @return
     */
    Script & addVarId(uint8_t aVarId);

    /**
     * Add operation to be executed. All necessary arguments will be popped from the stack.
     *
     * @param aData A data to be pushed to the stack.
     * @return
     */
    Script & addOperation(op_id_t aOpId);

    // Store and get variables from context;
    void addSetInt(var_id_t aVarRef);
    void addGetInt(var_id_t aVarRef);

    Script addSetObj(var_id_t aVarRef);
    Script addGetObj(var_id_t aVarRef);

    /**
     * CheckEvent checks an event specified by arg and skips the current statement if event is not present.
     *
     * @param aEventId the event to check.
     */
    void addIfEvent(event_id_t aEventId);

    /**
     * Completes the current statement.
     *
     * @return
     */
    Script &endStatement();

    /**
     * Execute the script.
     *
     * @return true if all statement were executes or false if some statement aborts the execution.
     */
    bool execute();

    /**
     * Retrieve the value stored in the stack during script execution.
     */
    template <typename T> T popResult() {
        return mStack.pop<T>();
    }
};


#endif //HYDROLIB2_SCRIPT_H
