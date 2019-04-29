//
// Created by Andrey on 27.04.2019.
//

#ifndef HYDROLIB2_HYDROOBJECT_H
#define HYDROLIB2_HYDROOBJECT_H

#include "hydro_types.h"
#include "Context.h"
#include "Scheduler.h"

class HydroObject {
protected:
    Context &mContext;
public:
    HydroObject(Context &aContext): mContext(aContext) {};

    virtual void start() {};
    virtual void stop() {};
    virtual int getInt(var_id_t aVarId) { return 0; }
    virtual void setInt(var_id_t aVarId) {}
    virtual ~HydroObject() = default;
};

#endif //HYDROLIB2_HYDROOBJECT_H
