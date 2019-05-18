#include <iostream>

#include "lib/Board.h"
#include "lib/ObjPeriodic.h"
#include "lib/Script.h"

int main() {
    Board board;
    Scheduler scheduler;
    Context context(board, &scheduler);
    ObjPeriodic test(context, 1, 2, 3, 4, 5);
    std::cout << "Hello! " << std::endl;
    return 0;
}