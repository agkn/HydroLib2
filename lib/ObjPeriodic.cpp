//
// Created by Andrey on 29.04.2019.
//

#include "ObjPeriodic.h"

time_t ObjPeriodic::MyTask::getSleepTimeSec() {
    time_t now = Clock::now().getUtc();
    return mNext <= now ? 0 : mNext - now;
}

event_id_t ObjPeriodic::MyTask::getEvent() {
    time_t now = Clock::now().getUtc();
    if (mNext < now) {
        mNext = mOwner.getNextTime(now);
        return mOwner.getEvent(now);
    }
    return NOT_EVENT;
}

time_t ObjPeriodic::getNextTime(time_t aNow) {
    time_t relative = aNow - mStartTicks + mTimeShift;
    time_t alligned = (relative / mPeriod) * mPeriod;
    return (relative < alligned + mFirstRange)
           ? mStartTicks + alligned + mFirstRange - mTimeShift
           : mStartTicks + alligned + mPeriod - mTimeShift;
}

event_id_t ObjPeriodic::getEvent(time_t aNow) {
    time_t relative = aNow - mStartTicks + mTimeShift;
    time_t inTime = relative % mPeriod;
    return (inTime < mFirstRange) ? mFirstEvent : mSecondEvent;
}

ObjPeriodic::ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange,
                         event_id_t aSecondEvent) :
        HydroObject(aContext), mTimeShift() {
    mFirstEvent = aFirstEvent;
    mFirstRange = aFirstRange;
    mSecondEvent = aSecondEvent;
    mPeriod = aSecondRange + aFirstRange;
    while(aShift < 0) {
        aShift += mPeriod;
    }
    mTimeShift = aShift % static_cast<int>(mPeriod);
}

void ObjPeriodic::start() {
    mStartTicks = Clock::now().getUtc();
}
