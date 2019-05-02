//
// Created by Andrey on 27.04.2019.
//

#ifndef HYDROLIB2_SCHEDULER_H
#define HYDROLIB2_SCHEDULER_H


#include "hydro_types.h"
#include "Context.h"
#include "Clock.h"

struct Task {
    /** Return sleep time until this task should be activated. */
    virtual time_t getSleepTimeSec() = 0;
    virtual event_id_t getEvent() = 0;
};

const int MAX_TASKS = 10;
const time_t MAX_SLEEP_TIME = 60;

class Context;
class Scheduler {
    Task *mTasks[MAX_TASKS] = {};
public:
    Scheduler(){

    }

    bool addTask(Task *aTask);

    bool removeTask(Task *aTask);

    time_t getSleepTimeSec(const DateTime &aTime);

    void setupEvents(Context &aContext, const DateTime &aTime);
};

#endif //HYDROLIB2_SCHEDULER_H
