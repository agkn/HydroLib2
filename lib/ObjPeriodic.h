//
// Created by Andrey on 29.04.2019.
//

#ifndef HYDROLIB2_OBJPERIODIC_H
#define HYDROLIB2_OBJPERIODIC_H

#include "HydroObject.h"

class ObjPeriodic: public HydroObject {
    class MyTask: public Task {
        time_t mNext{};
        ObjPeriodic &mOwner;
    public:
        explicit MyTask(ObjPeriodic &aObjPeriodic): mOwner(aObjPeriodic) {};
        time_t getSleepTimeSec() override;
        event_id_t getEvent() override;
    };

    event_id_t mFirstEvent;
    time_t mFirstRange;
    event_id_t mSecondEvent;
    time_t mPeriod;
    int mTimeShift;

public:
    ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange, event_id_t aSecondEvent);

    void start() override {

    }

    void stop() override {
    }

    time_t getNextTime();
    event_id_t getEvent();
};

#endif //HYDROLIB2_OBJPERIODIC_H
