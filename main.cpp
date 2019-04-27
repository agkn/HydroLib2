#include <iostream>

#include "lib/Board.h"
#include "lib/Operation.h"

int main() {
    op_id_t  ff = Operation::OP_And;
    std::cout << "Hello! " << (int)ff << "," << (int)Operation::OP_Set << std::endl;
    return 0;
}