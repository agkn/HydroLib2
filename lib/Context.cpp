//
// Created by Andrey on 14.04.2019.
//

#include <cstring>
#include "Context.h"

#define NOT_EVENT 255

Context::Context(const Board &board) : _board(board) {
    for (auto &_var : _vars) {
        _var = NULL;
    }
    clearEvents();
}

void Context::clearEvents() {
    memset(_events, NOT_EVENT, sizeof(_events));
}

bool Context::isEventActive(event_id_t aEventId) {
    for (unsigned char _event : _events) {
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
    for (unsigned char &_event : _events) {
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
    for (auto &_var : _vars) {
        delete _var;
    }
}



Value *Context::getValue(var_id_t aValueRef) {
    return _vars[aValueRef];
}


//
//bool Context::setVar(int aVarId, Value *aValue) {
//    if (NULL == _vars[aVarId]) {
//        return false;
//    }
//    _vars[aVarId]->setup(*aValue);
//    return true;
//}
