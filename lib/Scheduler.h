//
// Created by Andrey on 27.04.2019.
//

#ifndef HYDROLIB2_SCHEDULER_H
#define HYDROLIB2_SCHEDULER_H


#include "hydro_types.h"
#include "Context.h"
#include "Clock.h"

/**
 * Entities should add their tasks to scheduler in order to have a change to fire an event in time.
 */
struct Task {
    /**
     * Return sleep time until this task should be activated.
     *
     * @return amount of time to sleep.
     */
    virtual time_t getSleepTimeSec() = 0;

    /**
     * Evemt to fire if any. If there si no event in this time the NO_EVENT value should be returned.
     *
     * @return Event if there is an event to fire or NO_EVENT otherwise.
     */
    virtual event_id_t getEvent() = 0;
};

const int MAX_TASKS = 10;
const time_t MAX_SLEEP_TIME = 3600;

class Context;

/**
 * Should be returned by task if there no evetn expected
 */
const time_t NO_EVENT_SLEEP_TIME_SEC = 60;

/**
 * Should be returned by task if there no evetn expected
 */
const time_t NO_EVENT_GMS_TIME_SEC = 0;

class Scheduler {
    Task *mTasks[MAX_TASKS] = {};
public:

    Scheduler() {

    }

    bool addTask(Task *aTask);

    bool removeTask(Task *aTask);

    time_t getSleepTimeSec();

    void setupEvents(Context &aContext);
};

#endif //HYDROLIB2_SCHEDULER_H
