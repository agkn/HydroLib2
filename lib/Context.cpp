//
// Created by Andrey on 14.04.2019.
//

#include <cstring>
#include "Context.h"

Context::Context(const Board &aBoard, Scheduler *aScheduler) : mBoard(aBoard), mScheduler(aScheduler) {
    for (auto &_var : mVars) {
        _var = nullptr;
    }
    clearEvents();
}

void Context::clearEvents() {
    memset(mEvents, NOT_EVENT, sizeof(mEvents));
}

bool Context::isEventActive(event_id_t aEventId) {
    for (unsigned char _event : mEvents) {
        if (NOT_EVENT == _event) {
            return false;
        }
        if (aEventId == _event) {
            return true;
        }
    }
    return false;
}

event_id_t Context::anyEventActive() {
    for (unsigned char _event : mEvents) {
        if (NOT_EVENT != _event) {
            return _event;
        }
    }
    return NOT_EVENT;
}

bool Context::setEvent(event_id_t aEventId) {
    for (unsigned char &_event : mEvents) {
        if (NOT_EVENT == _event) {
            _event = aEventId;
            return true;
        }
    }

    return false;
}

void Context::begin() {
    clearEvents();
}

Context::~Context() {
    for (auto &_var : mVars) {
        delete _var;
    }
}

Value *Context::getValue(var_id_t aValueRef) const {
    return mVars[aValueRef];
}

Scheduler &Context::getScheduler() {
    return *mScheduler;
}

bool Context::setValue(var_id_t aValueRef, Value *aValue) {
    delete mVars[aValueRef];
    mVars[aValueRef] = aValue;
    return true;
}

//
//bool Context::setVar(int aVarId, Value *aValue) {
//    if (NULL == _vars[aVarId]) {
//        return false;
//    }
//    _vars[aVarId]->setup(*aValue);
//    return true;
//}
