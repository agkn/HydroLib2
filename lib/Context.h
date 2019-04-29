//
// Created by Andrey on 14.04.2019.
//

#ifndef HYDROLIB_CONTEXT_H
#define HYDROLIB_CONTEXT_H

#include "Board.h"
#include "hydro_types.h"
#include "Value.h"
#include "Scheduler.h"

#define CONTEXT_MAX_VARS 20
#define CONTEXT_MAX_EVENTS 4

const event_id_t NOT_EVENT = 0xff;

class Scheduler;
class Context {
    Board mBoard;
    Scheduler * mScheduler;
public:
    const Scheduler &getScheduler() const;

private:
    event_id_t mEvents[CONTEXT_MAX_EVENTS];
    Value * mVars[CONTEXT_MAX_VARS];
protected:
    void clearEvents();
public:
    Context(const Board &aBoard, const Scheduler &aScheduler);
    Context(const Board &aBoard);

    /**
     * Check if the event currently is active.
     *
     * @param aEventId An event id.
     * @return true if event is active and false otherwise.
     */
    bool isEventActive(event_id_t aEventId);

    /**
     * Flag an event.
     *
     * @param aEventId the event id to flag.
     * @return true if event was flagged and false if there is no space for event.
     */
    bool setEvent(event_id_t aEventId);

    bool setValue(var_id_t aValueRef, Value *aValue) {
        delete mVars[aValueRef];
        mVars[aValueRef] = aValue;
        return true;
    }

    Value * getValue(var_id_t aValueRef) const;

/*
    bool setVar(int aVarId, Value *aValue);
    Value *getVal(int aVarId);
*/

    /**
     * This function should be called at the begining of each  cycle to prepare the context
     * for the cycle processing.
     */
    virtual void begin();
    virtual ~Context();
};


#endif //HYDROLIB_CONTEXT_H
