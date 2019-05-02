//
// Created by Andrey on 27.04.2019.
//

#include "Scheduler.h"

bool Scheduler::addTask(Task *aTask) {
    for (auto &mTask : mTasks) {
        if (!mTask) {
            mTask = aTask;
            return true;
        }
    }
    return false;
}

bool Scheduler::removeTask(Task *aTask) {
    for (auto &task : mTasks) {
        if (task == aTask) {
            task = NULL;
            return true;
        }
    }
    return false;
}

time_t Scheduler::getSleepTimeSec(const DateTime &aTime) {
    time_t sleep = MAX_SLEEP_TIME;
    for (auto &task : mTasks) {
        if (task) {
            time_t s = task->getSleepTimeSec();
            if (s < sleep) {
                sleep = s;
            }
        }
    }
    return sleep;
}

void Scheduler::setupEvents(Context &aContext, const DateTime &aTime) {
    for (auto &mTask : mTasks) {
        if (mTask) {
            event_id_t event = mTask->getEvent();
            if (NOT_EVENT != event) {
                aContext.setEvent(event);
            }
        }
    }
}
