//
// Created by Andrey on 16.05.2019.
//

#ifndef HYDROLIB2_OBJDAILY_H
#define HYDROLIB2_OBJDAILY_H


#include "HydroObject.h"
#include "SimpleObject.h"
#include "hydro_types.h"

class ObjDaily : public SimpleObject<ObjDaily> {
    struct Event {
        event_id_t mEvent;
        time_t mSecsOfDay;
        Event *mNext;

        Event(event_id_t aEvent, time_t aSecsOfDay, Event *aNextEvent);
    };

    Event *mEvent;

public:
    explicit ObjDaily(Context &aContext);

    time_t getNextTime(const DateTime &aNow) override;

    uint8_t getEvent(const DateTime &aNow) override;

    void addTime(event_id_t aEvent, uint8_t aHour, uint8_t aMinute, uint8_t aSeconds) {
        time_t secs = aHour * 3600ul + aMinute * 60 + aSeconds;

        Event **pEvent = &mEvent;
        for (; nullptr != *pEvent; pEvent = &((*pEvent)->mNext)) {
            if ((*pEvent)->mSecsOfDay > secs) {
                break;
            }
        }
        *pEvent = new Event(aEvent, secs, *pEvent);
    }

    void start() override;

    virtual ~ObjDaily();
};


#endif //HYDROLIB2_OBJDAILY_H
