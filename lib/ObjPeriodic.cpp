//
// Created by Andrey on 29.04.2019.
//

#include "ObjPeriodic.h"
#include "Log.h"

time_t ObjPeriodic::MyTask::getSleepTimeSec() {
    time_t now = Clock::now().getUtc();
    return mNext <= now ? 0 : mNext - now;
}

event_id_t ObjPeriodic::MyTask::getEvent() {
    time_t now = Clock::now().getUtc();
    if (mNext <= now) {
        mNext = mOwner->getNextTime(now);
        return mOwner->getEvent(now);
    }
    return NOT_EVENT;
}

time_t ObjPeriodic::getNextTime(time_t aNow) {
    if (!mPeriod) {
        LOGE("Period is empty");
        return MAX_SLEEP_TIME;
    }

    // time from start of the periods
    time_t relative = aNow - mStartTicks + mTimeShift;
    // inside of a period
    time_t in =  relative  % mPeriod;
    for(Range *r = mRange ; r != nullptr; r = r->mNext) {
        if (in < r->mRange) {
            return relative + r->mRange - in + mStartTicks - mTimeShift;
        }
        in -= r->mRange;
    }
    return 0;
}

event_id_t ObjPeriodic::getEvent(time_t aNow) {
    if (!mPeriod) {
        LOGE("Period is empty");
        return NOT_EVENT;
    }

    time_t relative = aNow - mStartTicks + mTimeShift;
    time_t in =  relative  % mPeriod;
    for(Range *r = mRange ; r != nullptr; r = r->mNext) {
        if (in < r->mRange) {
            return r->mEvent;
        }
        in -= r->mRange;
    }
    return NOT_EVENT;
}

ObjPeriodic::ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange,
                         event_id_t aSecondEvent) :
        HydroObject(aContext), mTimeShift(), mPeriod{0}, mRange{nullptr}, mLast{nullptr} {
    add(aFirstRange, aFirstEvent);
    add(aSecondRange, aSecondEvent);
    while(aShift < 0) {
        aShift += mPeriod;
    }
    mTimeShift = aShift % static_cast<int>(mPeriod);
}

/**
 * Activates Periodic.
 * It registers an task in the scheduler to generate periodic events.
 * Just after start it will generate the event related to current period.
 * After it it will repeat events according the periods.
 */
void ObjPeriodic::start() {
    if (mTask != nullptr) {
        LOGD("Start has been called twice.");
        return;
    }
    mTask = new MyTask(this);
    mStartTicks = Clock::now().getUtc();
    mContext->getScheduler().addTask(mTask);
}

void ObjPeriodic::stop() {
    if (nullptr != mTask) {
        mContext->getScheduler().removeTask(mTask);
        delete mTask;
        mTask = nullptr;
    }
}

void ObjPeriodic::add(time_t aRange, event_id_t aEvent) {
    auto *range = new Range(aEvent, aRange);
    mPeriod += aRange;
    if (mLast == nullptr) {
        mRange = mLast = range;
    } else {
        mLast = range->addTo(mLast);
    }
}

ObjPeriodic::~ObjPeriodic() {
    for(Range *r = mRange; r != nullptr;) {
        Range *tmp = r;
        r = r->mNext;
        delete tmp;
    }
    mLast = mRange = nullptr;
}

ObjPeriodic::ObjPeriodic(Context &aContext) : HydroObject(aContext), mPeriod{0}, mRange{nullptr}, mLast{nullptr} {}

ObjPeriodic::Range::Range(event_id_t event, time_t range) : mEvent(event), mRange(range) {}

ObjPeriodic::Range *ObjPeriodic::Range::addTo(Range *apNext) {
    mNext = apNext->mNext;
    apNext->mNext = this;
    return this;
}
