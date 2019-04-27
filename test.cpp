//
// Created by Andrey on 17.04.2019.
//

#include <iostream>
#include "lib/Script.h"
#include "lib/Operation.h"


Board board;
Context context(board);


void testBinScriptSource() {
    Board board;
    Context context(board);

    Script ss(context);

    // time_day = time(8, 20)
    ss.addVarId(0).addInt8(20).addInt8(8).addOp(Operation::OP_Time).addOp(Operation::OP_SetObj).end();

    // time_night = time(19, 50)
    ss.addVarId(1).addInt8(50).addInt8(19).addOp(Operation::OP_Time).addOp(Operation::OP_SetObj).end();

    // f_day = period(time_day, time_night)
    ss.addVarId(2).addVarId(1).addVarId(0).addOp(Operation::OP_Period).addOp(Operation::OP_SetObj).end();

    // f_day = when(
//    ss.print();

}

int main() {
    std::cout << "Test" << std::endl;
    testBinScriptSource();
}

