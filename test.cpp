//
// Created by Andrey on 17.04.2019.
//

#include <iostream>
#include "lib/Script.h"
#include "lib/Operation.h"
#include "lib/Scheduler.h"
#include "lib/Clock.h"


Board board;
Scheduler scheduler;

Context context(board, &scheduler);
Script s_init(context);
Script s_main(context);

void sleep(time_t aSeconds) {
    std::cout << "Sleep: " << aSeconds << std::endl;
};

enum Events {
    E_DAY = 1,
    E_NIGHT,
    E_DRAIN,
    E_FLOOD,
};
enum Vars {
    V_DailyEvents = 0,
    V_PeriodsDay,
    V_PeriodsNight,
};

void setup() {

    // v_dailyEvents = DailyEvents(E_DAY, 8:20, E_NIGHT, 20:00
    s_init.addUint8(8).addUint8(20); // 08:20
    s_init.addEvent(E_DAY); // event
    s_init.addUint8(20).addUint8(00); // 20:00
    s_init.addEvent(E_NIGHT); // event
    s_init.addUint8(2); // number of events
    s_init.addOperation(Operation::OP_DailyEvents);
    s_init.addSetObj(V_DailyEvents);
    s_init.endStatement();

    // V_PeriodsDay = periodic(300, 2 /*Drain*/, 300, 3 /* Flood */)
    s_init.addInt(300).addEvent(E_DRAIN);
    s_init.addInt(300).addEvent(E_FLOOD);
    s_init.addOperation(Operation::OP_Periodic);
    s_init.addSetObj(V_PeriodsDay);
    s_init.endStatement();

    // V_PeriodsNight = periodic(300, 2 /*Drain*/, 300, 3 /* Flood */)
    s_init.addInt(600).addEvent(E_DRAIN);
    s_init.addInt(300).addEvent(E_FLOOD);
    s_init.addOperation(Operation::OP_Periodic);
    s_init.addSetObj(V_PeriodsNight);
    s_init.endStatement();
}

bool loop() {
    DateTime time(18, 04, 29, 0, 25, 0);
    scheduler.setupEvents(context);
    s_main.execute();
    sleep(scheduler.getSleepTimeSec());
    return true;
}

int main() {
    setup();
    s_init.execute();

    int safe = 10; // limit the number of the cycle.
    while (loop() && safe--) {
        std::cout << "Loop: next iteration" << std::endl;
    }
}

