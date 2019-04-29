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

Context context(board);
Script s_init(context);
Script s_main(context);
Clock clock;

void sleep(time_t aSeconds) {
    std::cout << "Sleep: " << aSeconds << std::endl;
};

void setup() {
}

bool loop() {
    DateTime time(18, 04, 29, 0, 25, 0);
    scheduler.setupEvents(context, time);
    s_main.execute();
    sleep(scheduler.getSleepTimeSec(time));
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

