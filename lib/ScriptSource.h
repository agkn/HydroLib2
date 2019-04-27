//
// Created by Andrey on 18.04.2019.
//

#ifndef HYDROLIB2_SCRIPTSOURCE_H
#define HYDROLIB2_SCRIPTSOURCE_H


#include "Operation.h"

class ScriptSource {
public:
    /**
     * Prepare script for execution. All pointers should be set up for beginning of execution.
     */
    virtual void reset() = 0;

    /**
     * Pointer to the next statement. This pointer can be used to skip execution to this statement.
     *
     * @return point to statement.
     */
    virtual bool prepare() = 0;

    /**
     * Cancel current execution and go to statement pointed by argument.
     */
    virtual void skip() = 0;

    /**
     * Read operation code.
     *
     * @return operation id.
     */
    virtual op_id_t getOperationCode() = 0;
    virtual int getInt() = 0;
    virtual int getInt8() = 0;
};


#endif //HYDROLIB2_SCRIPTSOURCE_H
