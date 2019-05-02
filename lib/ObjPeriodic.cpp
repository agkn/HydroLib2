//
// Created by Andrey on 29.04.2019.
//

#include "ObjPeriodic.h"

time_t ObjPeriodic::MyTask::getSleepTimeSec() {
/*
    return mNext <= aTime.daySeconds() ? 0 : mNext - aTime.daySeconds();
*/
    return 0;
}

event_id_t ObjPeriodic::MyTask::getEvent() {
/*
    time_t time = aTime.daySeconds();
    if (mNext < time) {
        mNext = mOwner.getNextTime(time);
        return mOwner.getEvent(aTime.daySeconds());
    }
*/
    return NOT_EVENT;
}

time_t ObjPeriodic::getNextTime() {
/*
    aSecondsOfDay += DateTime::SEC_IN_DAY + mTimeShift; // correct time on shift
    time_t alligned = (aSecondsOfDay / mPeriod) * mPeriod;
    time_t res = (aSecondsOfDay < alligned + mFirstRange)
            ? alligned + mFirstRange - mTimeShift
            : alligned + mPeriod - mTimeShift;
    return res % DateTime::SEC_IN_DAY;
*/
    return DateTime::SEC_IN_DAY;
}

event_id_t ObjPeriodic::getEvent() {
/*
    aNow += mTimeShift; // correct time on shift
    time_t inTime = aNow % mPeriod;
    return (inTime < mFirstRange) ? mFirstEvent : mSecondEvent;
*/
    return 0;
}

ObjPeriodic::ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange,
                         event_id_t aSecondEvent) :
        HydroObject(aContext), mTimeShift() {
    mFirstEvent = aFirstEvent;
    mFirstRange = aFirstRange;
    mSecondEvent = aSecondEvent;
    mPeriod = aSecondRange + aFirstRange;
    mTimeShift = aShift;
}
