//
// Created by Andrey on 17.04.2019.
//

#include "Operation.h"

op_func_t OPS2[] = {FUNC_CODES(FUNC_POINTER)};

#define OP_FUNC(NAME) op_result_t op##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack)

#define OP_BIN_SIMPLE(NAME, TYPE, OP) \
OP_FUNC(NAME) {\
auto right = aStack.pop<TYPE>(); \
auto left = aStack.pop<TYPE>(); \
aStack.push(left OP right);\
return Operation::OP_RESULT_OK;\
}

OP_BIN_SIMPLE(Plus, int, +);
OP_BIN_SIMPLE(Minus, int, -);
OP_BIN_SIMPLE(Mul, int, *);
OP_BIN_SIMPLE(Div, int, /);

#define OP_ARG_FUNC(NAME, TYPE) op_result_t op##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack) {\
    aStack.push(mQueue.pop<TYPE>());\
    return Operation::OP_RESULT_OK;\
}
OP_ARG_FUNC(ArgInt, int)
OP_ARG_FUNC(ArgFloat, float)
OP_ARG_FUNC(ArgBool, bool)

/**
 * Push true of falst depending on specified by next arg event is active or not.
 *
 * @param aContext A context.
 * @param mQueue A command and data queue.
 * @param aStack A Stack.
 * @return Operation::OP_RESULT_OK if operation successfuly completed.
 */
op_result_t opArgEvent(Context & aContext, BinQueue & mQueue, OpStack &aStack) {
    auto right = mQueue.pop<event_id_t>();
    aStack.push(aContext.isEventActive(right));
    return Operation::OP_RESULT_OK;
}

#define OP_GET_SET_VAL(NAME, TYPE) \
    op_result_t opSet##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack) {\
    auto right = mQueue.pop<var_id_t >();\
    auto left = aStack.pop<TYPE>();\
    aContext.setValue(right, new ValueImpl<TYPE>(left));\
    return Operation::OP_RESULT_OK;\
    }\
    op_result_t opGet##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack) {\
        auto right = mQueue.pop<var_id_t >();\
        aStack.push(aContext.getValue(right)->get##NAME());\
        return Operation::OP_RESULT_OK;\
    }

OP_GET_SET_VAL(Int, int);
OP_GET_SET_VAL(Float, float);
OP_GET_SET_VAL(Bool, bool);
//OP_GET_SET_VAL(Obj, void *);

op_result_t opIfEvent(Context & aContext, BinQueue & mQueue, OpStack &aStack) {
    auto right = mQueue.pop<event_id_t>();
    return aContext.isEventActive(right) ? Operation::OP_RESULT_OK : Operation::OP_RESULT_SKIP;
}

#define OP_DUMMY(NAME)  op_result_t op##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack) {return Operation::OP_RESULT_OK;}
OP_DUMMY(SetObj)
OP_DUMMY(And)
OP_DUMMY(Or)
OP_DUMMY(Period)
OP_DUMMY(Time)