//
// Created by Andrey on 17.04.2019.
//

#include "Operation.h"
#include "HydroObject.h"
#include "ObjPeriodic.h"

op_func_t OPS2[] = {FUNC_CODES(FUNC_POINTER)};

#define OP_FUNC(NAME) op_result_t op##NAME(Context & aContext, BinQueue & mQueue, OpStack &aStack)

#define OP_BIN_SIMPLE(NAME, TYPE, OP) \
OP_FUNC(NAME) {\
auto right = aStack.pop<TYPE>(); \
auto left = aStack.pop<TYPE>(); \
aStack.push(left OP right);\
return Operation::RESULT_OK;\
}

OP_BIN_SIMPLE(Plus, int, +);
OP_BIN_SIMPLE(Minus, int, -);
OP_BIN_SIMPLE(Mul, int, *);
OP_BIN_SIMPLE(Div, int, /);

#define OP_ARG_FUNC(NAME, TYPE) OP_FUNC(NAME) {\
    aStack.push(mQueue.pop<TYPE>());\
    return Operation::RESULT_OK;\
}
OP_ARG_FUNC(ArgInt, int)
OP_ARG_FUNC(ArgFloat, float)
OP_ARG_FUNC(ArgBool, bool)
OP_ARG_FUNC(ArgInt8, uint8_t)

/**
 * Push true of falst depending on specified by next arg event is active or not.
 *
 * @param aContext A context.
 * @param mQueue A command and data queue.
 * @param aStack A Stack.
 * @return Operation::OP_RESULT_OK if operation successfuly completed.
 */
OP_FUNC(ArgEvent) {
    auto right = mQueue.pop<event_id_t>();
    aStack.push(aContext.isEventActive(right));
    return Operation::RESULT_OK;
}

#define OP_GET_SET_VAL(NAME, TYPE) \
    OP_FUNC(Set##NAME) {\
    auto right = mQueue.pop<var_id_t >();\
    auto left = aStack.pop<TYPE>();\
    aContext.setValue(right, new ValueImpl<TYPE>(left));\
    return Operation::RESULT_OK;\
    }\
    OP_FUNC(Get##NAME) {\
        auto right = mQueue.pop<var_id_t >();\
        aStack.push(aContext.getValue(right)->get##NAME());\
        return Operation::RESULT_OK;\
    }

OP_GET_SET_VAL(Int, int);
OP_GET_SET_VAL(Float, float);
OP_GET_SET_VAL(Bool, bool);

OP_FUNC(SetObj) {
    auto right = mQueue.pop<var_id_t>();
    auto left = aStack.pop<HydroObject *>();
    aContext.setValue(right, new ValueObj(left));
    return Operation::RESULT_OK;
}

OP_FUNC(GetObj) {
        auto right = mQueue.pop<var_id_t>();
        aStack.push(aContext.getValue(right)->getObj());
        return Operation::RESULT_OK;
}

OP_FUNC(IfEvent) {
    auto right = mQueue.pop<event_id_t>();
    return aContext.isEventActive(right) ? Operation::RESULT_OK : Operation::RESULT_SKIP;
}

OP_FUNC(Periodic) {
    auto periods = aStack.pop<uint8_t>();
    if (!periods) {
        return Operation::RESULT_ERROR;
    }
    auto *obj = new ObjPeriodic(aContext);
    for(uint8_t i = 0 ; i < periods; i++) {
        obj->add(aStack.pop<int>(), aStack.pop<event_id_t> ());
    }
    aStack.push(obj);
    return Operation::RESULT_OK;
}

OP_FUNC(DailyEvents) {
    auto periods = aStack.pop<uint8_t>();
    if (!periods) {
        return Operation::RESULT_ERROR;
    }
    auto *obj = new ObjPeriodic(aContext);
    for(uint8_t i = 0 ; i < periods; i++) {
        obj->add(aStack.pop<int>(), aStack.pop<event_id_t> ());
    }
    aStack.push(obj);
    return Operation::RESULT_OK;
}

#define OP_DUMMY(NAME) OP_FUNC(NAME) {return Operation::RESULT_OK;}
OP_DUMMY(And)
OP_DUMMY(Or)
