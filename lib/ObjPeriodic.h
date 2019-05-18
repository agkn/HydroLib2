//
// Created by Andrey on 29.04.2019.
//

#ifndef HYDROLIB2_OBJPERIODIC_H
#define HYDROLIB2_OBJPERIODIC_H

#include "HydroObject.h"
#include "Scheduler.h"
#include "hydro_types.h"

class ObjPeriodic: public HydroObject {
    class MyTask: public Task {
        time_t mNext{};
        ObjPeriodic *mOwner;
    public:
        explicit MyTask(ObjPeriodic *aObjPeriodic): mOwner(aObjPeriodic) {};
        time_t getSleepTimeSec() override;
        event_id_t getEvent() override;
    };

    struct Range {
        event_id_t mEvent;
        time_t mRange;
        Range * mNext{};

        Range(event_id_t event, time_t range);
        Range * addTo(Range *apNext);
    };

    MyTask *mTask{};
    time_t mPeriod;
    Range * mRange;
    Range * mLast;
    time_t mStartTicks;
    time_t mTimeShift;

public:
    ObjPeriodic(Context &aContext);
    ObjPeriodic(Context &aContext, int aShift, time_t aFirstRange, event_id_t aFirstEvent, time_t aSecondRange, event_id_t aSecondEvent);

    void add(time_t aRange, event_id_t aEvent);

    void start() override;

    void stop() override;

    time_t getNextTime(time_t aNow);
    event_id_t getEvent(time_t aNow);

    virtual ~ObjPeriodic();

};

#endif //HYDROLIB2_OBJPERIODIC_H
