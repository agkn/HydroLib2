//
// Created by Andrey on 29.04.2019.
//

#include "ObjPeriodic.h"

time_t ObjPeriodic::MyTask::getSleepTimeSec(const DateTime &aTime) {
    return mNext <= aTime.daySeconds() ? 0 : mNext - aTime.daySeconds();
}

event_id_t ObjPeriodic::MyTask::getEvent(const DateTime &aTime) {
    time_t time = aTime.daySeconds();
    if (mNext < time) {
        mNext = mOwner.getNextTime(time);
        return mOwner.getEvent(aTime.daySeconds());
    }
    return NOT_EVENT;
}

time_t ObjPeriodic::getNextTime(time_t aNow) {
    aNow += mTimeShift; // correct time on shift
    time_t alligned = (aNow / mPeriod) * mPeriod;
    if (aNow < alligned + mFirstRange) {
        return alligned + mFirstRange - mTimeShift;
    } else {
        return alligned + mPeriod - mTimeShift;
    }
}

event_id_t ObjPeriodic::getEvent(time_t aNow) {
    aNow += mTimeShift; // correct time on shift
    time_t inTime = aNow % mPeriod;
    return (inTime < mFirstRange) ? mFirstEvent : mSecondEvent;
}

ObjPeriodic::ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange,
                         event_id_t aSecondEvent) :
        HydroObject(aContext), mTimeShift() {
    mFirstEvent = aFirstEvent;
    mFirstRange = aFirstRange;
    mSecondEvent = aSecondEvent;
    mPeriod = aSecondRange + aFirstRange;
    while (aShift < 0) {
        aShift += mPeriod;
    }
    mTimeShift = static_cast<time_t>(aShift);
}
