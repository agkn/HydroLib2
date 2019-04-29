//
// Created by Andrey on 14.04.2019.
//

#include <cstring>
#include "Context.h"

Context::Context(const Board &aBoard, const Scheduler &aScheduler) : mBoard(aBoard), mScheduler(NULL) {
    for (auto &_var : mVars) {
        _var = NULL;
    }
    clearEvents();
}
Context::Context(const Board &aBoard) : mBoard(aBoard) {
    for (auto &_var : mVars) {
        _var = NULL;
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

const Scheduler &Context::getScheduler() const {
    return *mScheduler;
}



//
//bool Context::setVar(int aVarId, Value *aValue) {
//    if (NULL == _vars[aVarId]) {
//        return false;
//    }
//    _vars[aVarId]->setup(*aValue);
//    return true;
//}
