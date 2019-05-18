//
// Created by Andrey on 17.04.2019.
//

#ifndef HYDROLIB2_OPERATION_H
#define HYDROLIB2_OPERATION_H

#include "hydro_types.h"
#include "OpStack.h"
#include "Context.h"
#include "BinQueue.h"

// define tokens of functions.
#define FUNC_CODES(F) \
    F(ArgInt) \
    F(ArgInt8) \
    F(ArgFloat) \
    F(ArgBool) \
    F(Plus) \
    F(Minus) \
    F(Mul) \
    F(Div) \
    F(SetInt) \
    F(GetInt) \
    F(SetFloat) \
    F(GetFloat) \
    F(SetBool) \
    F(GetBool) \
    F(SetObj) \
    F(GetObj) \
    F(And) \
    F(Or) \
    F(IfEvent) \
    F(DailyEvents) \
    F(Periodic) \

class ScriptSource;
// Extern declarations generator
#define FUNC_EXTERN(NAME) extern op_result_t op##NAME(Context & , BinQueue &, OpStack &);
FUNC_CODES(FUNC_EXTERN)

// func pointer generator
#define FUNC_POINTER(NAME) op##NAME,
#define FUNC_CONST(NAME) constexpr static op_id_t OP_##NAME = __COUNTER__;

typedef op_result_t (* op_func_t )(Context & aContext, BinQueue & mQueue, OpStack &aStack);

extern op_func_t OPS2[];

class Operation {
public:
    constexpr const static op_func_t OPS[] = {FUNC_CODES(FUNC_POINTER)};
    // Generate operations constants.
    FUNC_CODES(FUNC_CONST);
    constexpr static op_id_t OP_TEST = 100;

    // Operations result codes
    constexpr static op_result_t RESULT_OK = 0;
    constexpr static op_result_t RESULT_SKIP = 1;
    constexpr static op_result_t RESULT_ERROR = 2;
};

#endif //HYDROLIB2_OPERATION_H
