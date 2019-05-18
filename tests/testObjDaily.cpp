//
// Created by Andrey on 18.05.2019.
//
#include "../catch/catch.hpp"
#include "../lib/Board.h"
#include "../lib/Scheduler.h"
#include "../lib/Context.h"
#include "../lib/ObjDaily.h"


TEST_CASE("ObjDaily", "[ObjDaily]") {
    Board board;
    Scheduler scheduler;
    Context context(board, &scheduler);

    ObjDaily daily(context);
    DateTime start(19, 05, 1, 06, 00, 0);
    Clock::setNow(start);
    daily.start();
    event_id_t event_1 = 1;

    // no active task
    REQUIRE(daily.getNextTime(start) == NO_EVENT_GMS_TIME_SEC);
    REQUIRE(daily.getEvent(start) == NOT_EVENT);

    // no events test
    daily.start();
    REQUIRE(daily.getNextTime(start) == NO_EVENT_GMS_TIME_SEC);
    REQUIRE(daily.getEvent(start) == NOT_EVENT);

    daily.stop();
    daily.addTime(event_1, 8, 0, 0);
    daily.start();
    REQUIRE(daily.getEvent(start) == event_1);
    REQUIRE(daily.getNextTime(start) == start.getUtc() + 2 * 3600);

    scheduler.setupEvents(context);
    REQUIRE(!context.isEventActive(event_1));
    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);

    Clock::setNow(DateTime(19, 05, 1, 7, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(!context.isEventActive(event_1));
    REQUIRE(scheduler.getSleepTimeSec() == 30 * 60);

    Clock::setNow(DateTime(19, 05, 1, 8, 0, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(event_1));
    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);

    Clock::setNow(DateTime(19, 05, 1, 8, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(!context.isEventActive(event_1));
    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);
}

TEST_CASE("ObjDaily several events", "[ObjDaily]") {
    Board board;
    Scheduler scheduler;
    Context context(board, &scheduler);

    ObjDaily daily(context);
    DateTime start(19, 05, 1, 06, 10, 0);
    Clock::setNow(start);
    enum {
        EVENT_1 = 1,
        EVENT_2,
        EVENT_3
    };
    daily.addTime(EVENT_1, 7, 0, 0);
    daily.addTime(EVENT_2, 8, 0, 0);
    daily.addTime(EVENT_3, 20, 0, 0);
    daily.start();

    // 06:00:00
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.anyEventActive() == NOT_EVENT);
    REQUIRE(scheduler.getSleepTimeSec() == 50 * 60);

    // 07:30:00
    Clock::setNow(DateTime(19, 05, 1, 7, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(EVENT_1));
    REQUIRE(scheduler.getSleepTimeSec() == 30 * 60);

    // 08:30:00
    Clock::setNow(DateTime(19, 05, 1, 8, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(EVENT_2));
    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);

    // 20:30:00
    Clock::setNow(DateTime(19, 05, 1, 19, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.anyEventActive() == NOT_EVENT);
    REQUIRE(scheduler.getSleepTimeSec() == 30 * 60);


    // 21:30:00
    Clock::setNow(DateTime(19, 05, 1, 21, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(EVENT_3));
    REQUIRE(scheduler.getSleepTimeSec() == MAX_SLEEP_TIME);

    // next day 07:30:00
    Clock::setNow(DateTime(19, 05, 2, 7, 30, 0));
    context.begin();
    scheduler.setupEvents(context);
    REQUIRE(context.isEventActive(EVENT_1));
    REQUIRE(scheduler.getSleepTimeSec() == 30 * 60);
}