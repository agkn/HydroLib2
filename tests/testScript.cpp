//
// Created by Andrey on 20.04.2019.
//

#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"
#include "../lib/Script.h"
#include "../lib/BinQueue.h"
#include "../lib/Operation.h"
#include "../lib/HydroObject.h"
#include "../lib/ObjPeriodic.h"


TEST_CASE("BinQueue basics", "[BinQueue]") {
    BinQueue q;
    q.clear();
    REQUIRE(q.mData[0] == 0);
    REQUIRE(q.mStatementPointer == 0);
    REQUIRE(q.mSize == 1);
    REQUIRE(q.mPopPointer == 0);
    q.add((uint8_t)1);
    q.add((uint8_t)2);
    q.end();
    q.add((uint8_t)3);
    q.add((uint8_t)4);
    q.end();
    q.reset();
    REQUIRE(q.mData[0] == 3);
    REQUIRE(q.mStatementPointer == 0);
    REQUIRE(q.mSize == 7);
    REQUIRE(q.mPopPointer == 0);

    REQUIRE(q.prepareStatement() != 0);
    REQUIRE(q.mPopPointer == 1);
    REQUIRE(q.inStatement() != 0);

    SECTION("Check data fetch sequence") {
        REQUIRE(q.pop<uint8_t >() == 1);
        REQUIRE(q.pop<uint8_t >() == 2);
        REQUIRE(q.inStatement() == 0);

        REQUIRE(q.prepareStatement());
        REQUIRE(q.inStatement() != 0);
        REQUIRE(q.pop<uint8_t >() == 3);
        REQUIRE(q.pop<uint8_t >() == 4);
        REQUIRE(q.inStatement() == 0);

        REQUIRE(q.prepareStatement() == 0);
    }

    SECTION("Check skip statements") {
        REQUIRE(q.pop<uint8_t >() == 1);
        q.skip();
        REQUIRE(q.inStatement() == 0);
        REQUIRE(q.prepareStatement() != 0);
        REQUIRE(q.pop<uint8_t >() == 3);
        q.skip();
        REQUIRE(q.inStatement() == 0);
        REQUIRE(q.prepareStatement() == 0);
    }
}

TEST_CASE("Script basic", "[Script]") {
    Board board;
    Context context(board);
    Script script(context);

    // (12 + 8) / (7 - 2) * 10
    script.addData(12);
    script.addData(8);
    script.addOperation(Operation::OP_Plus);
    script.addData(7);
    script.addData(2);
    script.addOperation(Operation::OP_Minus);
    script.addOperation(Operation::OP_Div);
    script.addData(10);
    script.addOperation(Operation::OP_Mul);
    script.endStatement();

    for(int i = 0; i < 10; i++) {
        script.execute();
        auto result = script.pop<int>();
        REQUIRE(result == 40);
    }
}

TEST_CASE("Script context", "[Script]") {
    Board board;
    Context context(board);
    Script script(context);

    // Var_1 = 10 , Var1 = Var1 + 1
    script.addData(10);
    script.addSetInt(1);

    script.addGetInt(1);
    script.addData(15);
    script.addOperation(Operation::OP_Plus); // + 1

    script.addSetInt(1);
    script.endStatement();
    for(int i = 0; i < 10; i++) {
        script.execute();
        REQUIRE(context.getValue(1)->getInt() == 25);
    }
}

TEST_CASE("Script event", "[Script]") {
    Board board;
    Context context(board);
    Script script(context);

    script.addData(0);
    script.addSetInt(1);
    script.endStatement();

    script.addIfEvent(0);
    script.addData(10);
    script.addSetInt(1);
    script.endStatement();

    SECTION("Check event not flagged") {
        script.execute();
        REQUIRE(context.getValue(1)->getInt() == 0);
    }
    SECTION("Check event flagged") {
        context.setEvent(0);
        script.execute();
        REQUIRE(context.getValue(1)->getInt() == 10);
    }
}

TEST_CASE("Period object", "[Objects]") {
    Board board;
    Context context(board);

    ObjPeriodic periodic(context, 0, 600, 1, 300, 2);
    DateTime time(18, 04, 29, 0, 36, 00);
    periodic.start();
    periodic.getEvent(0ul);
    //REQUIRE(periodic.start() == 0);
}