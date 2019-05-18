//
// Created by Andrey on 16.05.2019.
//

#ifndef HYDROLIB2_SIMPLETASK_H
#define HYDROLIB2_SIMPLETASK_H

#include "Scheduler.h"
#include "Log.h"

template<class B>
struct SimpleTask : public Task {
    B *mOwner;
    time_t mNextUtc;
    time_t mStartTicks;

    explicit SimpleTask(B *aOwner, const DateTime &aNow) : mOwner(aOwner), mStartTicks(aNow.getUtc()),
                                                           mNextUtc(NO_EVENT_GMS_TIME_SEC) {
    };

    /**
     * cancel immediate event after start task. The event will be scheduled to the next time.
     *
     * @param aNow the current time.
     */
    void setupNext(const DateTime &aNow) {
        mNextUtc = mOwner->getNextTime(aNow);
    }

    time_t getSleepTimeSec() override {
        const DateTime &now = Clock::now();
        return mNextUtc <= now.getUtc() ? 0 : mNextUtc - now.getUtc();
    };

    event_id_t getEvent() override {
        const DateTime &now = Clock::now();
        if (mNextUtc <= now.getUtc()) {
            mNextUtc = mOwner->getNextTime(now);
            return mOwner->getEvent(now);
        }
        return NOT_EVENT;
    };
};

template<class B>
class SimpleObject : public HydroObject {
protected:
    SimpleTask<B> *mTask;
public:
    explicit SimpleObject(Context &aContext) : HydroObject(aContext), mTask() {}

    void start() override {
        if (mTask != nullptr) {
            LOGD("Start has been called twice.");
            return;
        }
        mTask = new SimpleTask<B>((B *) this, Clock::now());
        mContext->getScheduler().addTask(mTask);
    }

    void stop() override {
        if (nullptr != mTask) {
            mContext->getScheduler().removeTask(mTask);
            delete mTask;
            mTask = nullptr;
        }
    }

    /**
     * Called from task when need to calculate the next event time.
     * SimpleTask will remember the next time and will not call this function again until time reached that value.
     *
     * @param aNow The current time.
     * @return  UTC time of the next event or 0 if event should be now.
     */
    virtual time_t getNextTime(const DateTime &aNow) = 0;

    /**
     * Called from a task when it needs to know current event.
     *
     * @param aNow The current time.
     * @return Event or NO_EVENT if there is no event.
     */
    virtual event_id_t getEvent(const DateTime &aNow) = 0;

    ~SimpleObject() override {
        if (nullptr != mTask) {
            mContext->getScheduler().removeTask(mTask);
            delete mTask;
        }
    }
};

#endif //HYDROLIB2_SIMPLETASK_H
