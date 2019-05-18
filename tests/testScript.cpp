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
    Context context(board, nullptr);
    Script script(context);

    // (12 + 8) / (7 - 2) * 10
    script.addInt(12);
    script.addInt(8);
    script.addOperation(Operation::OP_Plus);
    script.addInt(7);
    script.addInt(2);
    script.addOperation(Operation::OP_Minus);
    script.addOperation(Operation::OP_Div);
    script.addInt(10);
    script.addOperation(Operation::OP_Mul);
    script.endStatement();

    for(int i = 0; i < 10; i++) {
        script.execute();
        auto result = script.popResult<int>();
        REQUIRE(result == 40);
    }
}

TEST_CASE("Script context", "[Script]") {
    Board board;
    Context context(board, nullptr);
    Script script(context);

    // Var_1 = 10 , Var1 = Var1 + 1
    script.addInt(10);
    script.addSetInt(1);

    script.addGetInt(1);
    script.addInt(15);
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
    Context context(board, nullptr);
    Script script(context);

    script.addInt(0);
    script.addSetInt(1);
    script.endStatement();

    script.addIfEvent(0);
    script.addInt(10);
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

TEST_CASE("DateTime to seconds", "[DateTime]") {
    SECTION("Leap 1 of Mach - 1") {
        DateTime time(20, 02, 29, 23, 59, 59);
        // Sunday, March 1, 2020 12:00:00 AM
        REQUIRE(time.getUtc() == 1583020799);
    }
    SECTION("Simple") {
        DateTime time(19, 05, 1, 20, 04, 54);
        // Wednesday, May 1, 2019 8:04:54 PM 1556741094
        REQUIRE(time.getUtc() == 1556741094);
    }
    SECTION("Leap 1 of Mach") {
        DateTime time(20, 03, 1, 0, 00, 0);
        // Sunday, March 1, 2020 12:00:00 AM
        REQUIRE(time.getUtc() == 1583020800);
    }
}

TEST_CASE("Seconds to DateTime", "[DateTime]") {
    SECTION("Leap 1 of Jan") {
        DateTime time(20, 01, 1, 12, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Leap + 1, 1 of Jan") {
        DateTime time(21, 01, 1, 12, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Leap - 1, 1 of Jan") {
        DateTime time(19, 01, 1, 12, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Leap 1 of Mach") {
        DateTime time(20, 03, 1, 0, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Leap + 1, 1 of Jan") {
        DateTime time(21, 03, 1, 12, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Leap - 1, 1 of Jan") {
        DateTime time(19, 03, 1, 12, 0, 0);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
    SECTION("Simple") {
        DateTime time(19, 05, 1, 20, 04, 54);
        auto utc = time.getUtc();
        DateTime test = DateTime::createFromUtc(utc);
        REQUIRE(test.getUtc() == utc);
    }
}

TEST_CASE("Period object", "[Objects]") {
    Board board;
    Scheduler scheduler;
    Context context(board, &scheduler);
    const int shift = -100;
    const time_t P1 = 600;
    const time_t P2 = 300;

    event_id_t E1 = 1;
    event_id_t E2 = 2;
    ObjPeriodic periodic(context, shift, P1, E1, P2, E2);
    DateTime start(19, 05, 1, 00, 00, 0);
    Clock::setNow(start);
    periodic.start();

    SECTION("Immediately") {
        REQUIRE(periodic.getNextTime(start.getUtc()) - start.getUtc() == 100);
        REQUIRE(periodic.getEvent(start.getUtc()) == E2);
    }
    SECTION("Border 1") {
        DateTime now = DateTime::createFromUtc(start.getUtc() + 100);
        REQUIRE(periodic.getNextTime(now.getUtc()) - now.getUtc() == P1);
        REQUIRE(periodic.getEvent(now.getUtc()) == E1);
    }
    SECTION("Border 2") {
        DateTime now = DateTime::createFromUtc(start.getUtc() + 100 + P1);
        REQUIRE(periodic.getNextTime(now.getUtc()) - now.getUtc() == P2);
        REQUIRE(periodic.getEvent(now.getUtc()) == E2);
    }
    SECTION("Border 1 x 10") {
        DateTime now = DateTime::createFromUtc(start.getUtc() + 100 + (P1 + P2) * 10);
        REQUIRE(periodic.getNextTime(now.getUtc()) - now.getUtc() == P1);
        REQUIRE(periodic.getEvent(now.getUtc()) == E1);
    }
    SECTION("Border 2 x 10") {
        DateTime now = DateTime::createFromUtc(start.getUtc() + 100 + P1 + (P1 + P2) * 10);
        REQUIRE(periodic.getNextTime(now.getUtc()) - now.getUtc() == P2);
        REQUIRE(periodic.getEvent(now.getUtc()) == E2);
    }
}

TEST_CASE("Scheduler", "[Scheduler]") {
    Board board;
    Scheduler scheduler;
    Context context(board, &scheduler);

    const int shift = 0;
    const time_t P1 = 600;
    const time_t P2 = 300;

    event_id_t E1 = 1;
    event_id_t E2 = 2;
    ObjPeriodic periodic(context, shift, P1, E1, P2, E2);

    DateTime start(19, 05, 1, 00, 00, 0);
    Clock::setNow(start);

    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);

    periodic.start();
    // the ObjPeriodic sets an event with related to current period.
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(E1));
    REQUIRE(!context.isEventActive(E2));

    context.begin();
    Clock::setNow(DateTime::createFromUtc(start.getUtc() + 100));
    scheduler.setupEvents(context);
    REQUIRE(scheduler.getSleepTimeSec() == P1 - 100);
    REQUIRE(!context.isEventActive(E1));
    REQUIRE(!context.isEventActive(E2));

    context.begin();
    Clock::setNow(DateTime::createFromUtc(start.getUtc() + P1));
    scheduler.setupEvents(context);
    REQUIRE(!context.isEventActive(E1));
    REQUIRE(context.isEventActive(E2));
    REQUIRE(scheduler.getSleepTimeSec() == P2);
}

