//
// Created by Andrey on 16.05.2019.
//

#include "ObjDaily.h"

ObjDaily::ObjDaily(Context &aContext) : SimpleObject(aContext) {}

time_t ObjDaily::getNextTime(const DateTime &aNow) {
    if (nullptr == mTask) {
        // no started
        return NO_EVENT_GMS_TIME_SEC;
    }

    if (nullptr == mEvent) {
        // no events specified
        return NO_EVENT_GMS_TIME_SEC;
    }
    time_t secOfDay = aNow.daySeconds();
    for(Event * event = mEvent; nullptr != event; event = event->mNext) {
        if (secOfDay < event->mSecsOfDay) {
            return aNow.getUtc() + event->mSecsOfDay - secOfDay;
        }
    }
    // the next day first event
    return aNow.getUtc() - secOfDay + DateTime::SEC_IN_DAY + mEvent->mSecsOfDay;
}

uint8_t ObjDaily::getEvent(const DateTime &aNow) {
    if (nullptr == mTask) {
        // not started
        return NOT_EVENT;
    }

    if (nullptr == mEvent) {
        // not events specified
        return NOT_EVENT;
    }

    time_t secOfDay = aNow.daySeconds();
    for(Event * event = mEvent; nullptr != event; event = event->mNext) {
        if (secOfDay >= event->mSecsOfDay && (event->mNext == nullptr || event->mNext->mSecsOfDay > secOfDay)) {
            return event->mEvent;
        }
    }
    // should never be reached.
    return mEvent->mEvent;
}

ObjDaily::~ObjDaily() {
    for(Event *event = mEvent; event != nullptr;) {
        Event *tmp = event;
        event = event->mNext;
        delete tmp;
    }

}

void ObjDaily::start() {
    SimpleObject::start();
    mTask->setupNext(Clock::now());
}

ObjDaily::Event::Event(event_id_t aEvent, time_t aSecsOfDay, Event *aNextEvent)
        : mEvent(aEvent), mSecsOfDay(aSecsOfDay), mNext(aNextEvent) {}
